/* Copyright (c) 2021T FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
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

RC FilterStmt::create(ExprContext &ctx, Condition *conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit(ctx, conditions[i], filter_unit);
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

RC FilterStmt::create_filter_unit(ExprContext &ctx, Condition &condition, FilterUnit *&filter_unit)
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

  Expression *left = ExprFactory::create(condition.left_ast, ctx);
  Expression *right = ExprFactory::create(condition.right_ast, ctx);

  rc = check_date_valid(left, right);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  filter_unit = new FilterUnit;
  filter_unit->set_comp(comp);
  filter_unit->set_left(left);
  filter_unit->set_right(right);

  return rc;
}
