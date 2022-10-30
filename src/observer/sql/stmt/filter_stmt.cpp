/* Copyright (c) 2021T FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "common/lang/defer.h"
#include "rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/subselect_operator.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "util/ast_util.h"
#include "util/date.h"
#include "util/check.h"
#include <cassert>

static RC check_condition(Condition &condition, ExprContext &ctx)
{
  CompOp comp = condition.comp;
  if (comp == IS || comp == IS_NOT) {
    if (condition.right_is_select) {
      return RC::SQL_SYNTAX;
    }
    if (condition.right_ast->nodetype != NodeType::VALN) {
      return RC::SQL_SYNTAX;
    }
    if (condition.right_ast->val.type != AttrType::NULLS) {
      return RC::SQL_SYNTAX;
    }
  }
  size_t attr_cnt = 0;
  size_t aggr_cnt = 0;
  ast *lt = condition.left_ast;
  ast *rt = condition.right_ast;
  RC rc = check_leaf_node(lt, ctx, attr_cnt, aggr_cnt);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = check_leaf_node(rt, ctx, attr_cnt, aggr_cnt);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  if (aggr_cnt > 0) {
    LOG_WARN("cannot use aggregation in condition\n");
    return RC::SQL_SYNTAX;
  }
  return RC::SUCCESS;
}

// SELECT * FROM date_table WHERE u_date='2017-2-29';
// FAILURE
static RC check_date_valid(Expression *left, Expression *right)
{
  if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
    Expression *tmp = left;
    left = right;
    right = tmp;
  }
  if (left->type() == ExprType::FIELD && right->type() == ExprType::VALUE) {
    FieldExpr *left_field = static_cast<FieldExpr *>(left);
    ValueExpr *right_value = static_cast<ValueExpr *>(right);
    if (left_field->field().attr_type() == DATES) {
      RowTuple unused;
      TupleCell cell;
      right_value->get_value(unused, cell);
      int32_t date;
      RC rc;
      if (cell.attr_type() == CHARS && (rc = string_to_date(cell.data(), date)) != RC::SUCCESS) {
        return rc;
      }
    }
  }
  return RC::SUCCESS;
}

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, ExprContext &ctx, Condition *conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit(db, ctx, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC FilterStmt::create_filter_unit(Db *db, ExprContext &ctx, Condition &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  rc = check_condition(condition, ctx);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (condition.condition_type == COND_COMPARE) {

    Expression *left = nullptr;
    Expression *right = nullptr;

    if (condition.left_is_select) {
      Stmt *left_select = nullptr;
      DEFER([left_select]() { delete left_select; });
      rc = SelectStmt::create(db, *condition.left_select, left_select);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      SubSelectOperator oper(static_cast<SelectStmt *>(left_select), nullptr);
      TupleCell left_cell;
      rc = oper.GetOneResult(left_cell);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      left = new ValueExpr(left_cell.to_value()); // free?
    } else {
      left = ExprFactory::create(condition.left_ast, ctx);
    }
    if (condition.right_is_select) {
      Stmt *right_select = nullptr;
      DEFER([right_select]() { delete right_select; });
      rc = SelectStmt::create(db, *condition.right_select, right_select);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      SubSelectOperator oper(static_cast<SelectStmt *>(right_select), nullptr);
      TupleCell right_cell;
      rc = oper.GetOneResult(right_cell);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      right = new ValueExpr(right_cell.to_value());
    } else {
      right = ExprFactory::create(condition.right_ast, ctx);
    }

    if (left && right) {
      rc = check_date_valid(left, right);
      if (rc != RC::SUCCESS) {
        delete left;
        delete right;
        return rc;
      }
    }

    filter_unit = new FilterUnit();
    filter_unit->set_left(left);
    filter_unit->set_right(right);
  } else if (condition.condition_type == ConditionType::COND_IN) {
    assert(condition.left_ast != nullptr && condition.left_select != nullptr);
    Stmt *sub_select_stmt = nullptr;
    DEFER([sub_select_stmt]() { delete sub_select_stmt; });
    rc = SelectStmt::create(db, *condition.left_select, sub_select_stmt);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    SubSelectOperator oper(static_cast<SelectStmt *>(sub_select_stmt), nullptr);
    std::vector<TupleCell> cells;
    rc = oper.GetResultList(cells);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    std::vector<Value> new_vals;
    new_vals.reserve(cells.size());
    for (const TupleCell &cell : cells) {
      Value value = cell.to_value();
      new_vals.push_back(value);
    }
    filter_unit = new FilterUnit();
    filter_unit->set_cells(new_vals);
    filter_unit->set_left(ExprFactory::create(condition.left_ast, ctx));
  } else {
    assert(condition.left_select != nullptr);
    Stmt *sub_select_stmt = nullptr;
    DEFER([sub_select_stmt]() { delete sub_select_stmt; });
    rc = SelectStmt::create(db, *condition.left_select, sub_select_stmt);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    SubSelectOperator oper(static_cast<SelectStmt *>(sub_select_stmt), nullptr);
    std::vector<TupleCell> cells;
    bool exists;
    rc = oper.HasResult(exists);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    filter_unit = new FilterUnit();
    filter_unit->set_exists(exists);
  }
  filter_unit->set_comp(condition.comp);
  filter_unit->set_condition_type(condition.condition_type);

  return rc;
}
