/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/operator/project_operator.h"
#include "sql/parser/parse_defs.h"
#include "storage/record/record.h"
#include "storage/common/table.h"
#include "util/util.h"
#include <algorithm>

class TupleComparator {
public:
  TupleComparator(const std::vector<Expression *> &order_exprs, const std::vector<OrderPolicy> &policies):
    order_exprs_(order_exprs), order_policies_(policies)
  {}
  int compare_one(Expression *order_expr, const Tuple* lhs, const Tuple* rhs) const
  {
    TupleCell left_cell, right_cell;
    order_expr->get_value(*lhs, left_cell);
    order_expr->get_value(*rhs, right_cell);
    if (left_cell.attr_type() == NULLS && right_cell.attr_type() != NULLS) {
      return -1;
    } else if (left_cell.attr_type() == NULLS && right_cell.attr_type() == NULLS) {
      return 0;
    } else if (left_cell.attr_type() != NULLS && right_cell.attr_type() == NULLS) {
      return 1;
    }
    int compare = left_cell.compare(right_cell);
    return compare;
  }

  bool operator()(const Tuple *lhs, const Tuple *rhs) const
  {
    for (size_t i = 0; i < order_exprs_.size(); i++) {
      Expression *expr = order_exprs_[i];
      OrderPolicy policy = order_policies_[i];
      int compare = compare_one(expr, lhs, rhs);
      if (policy == OrderPolicy::ORDER_ASC) {
        if (compare < 0) {
          return true;
        } else if (compare > 0) {
          return false;
        }
      } else {
        if (compare > 0) {
          return true;
        } else if (compare < 0) {
          return false;
        }
      }
    }
    return true;
  }

private:
  std::vector<Expression *> order_exprs_;
  std::vector<OrderPolicy> order_policies_;
};

RC ProjectOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("project operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  if (order_exprs_.size() > 0) {
    RC rc;
    while ((rc = children_[0]->next()) == RC::SUCCESS) {
      tuple_.set_tuple(children_[0]->current_tuple()->copy());
      sorted_tuples_.push_back(static_cast<ProjectTuple *>(tuple_.copy()));
    }
    std::sort(sorted_tuples_.begin(), sorted_tuples_.end(), TupleComparator(order_exprs_, order_policies_));
  }

  return RC::SUCCESS;
}

RC ProjectOperator::next()
{
  if (order_exprs_.size() == 0) {
    return children_[0]->next();
  } else {
    if (next_idx_ >= sorted_tuples_.size()) {
      return RC::RECORD_EOF;
    }
    tuple_.set_tuple(sorted_tuples_[next_idx_++]);
    return RC::SUCCESS;
  }
}

RC ProjectOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}
Tuple *ProjectOperator::current_tuple()
{
  if (order_exprs_.size() == 0) {
    tuple_.set_tuple(children_[0]->current_tuple());
  } else {
  }
  return &tuple_;
}

void ProjectOperator::add_projection(Expression *expr, bool is_multi_table, const NameMap &table_alias, const char *alias)
{
  TupleCellSpec *spec = nullptr;
  std::string show_name;
  if (expr->type() == ExprType::FIELD) {
    FieldExpr *field_expr = static_cast<FieldExpr *>(expr);
    Field &field = field_expr->field();
    const Table *table = field.table();
    const FieldMeta *field_meta = field.meta();
    if (is_multi_table) {
      show_name = "";
      if (table_alias.count(table->name())) {
        show_name += table_alias.at(table->name());
      } else {
        show_name += table->name();
      }
      show_name = show_name + "." + std::string(field_meta->name());
    } else {
      show_name = std::string(field_meta->name());
    }
    spec = new TupleCellSpec(expr);
    spec->set_alias(show_name);
  } else if (expr->type() == ExprType::VALUE) {
    spec = new TupleCellSpec(expr);
    ValueExpr *value_expr = static_cast<ValueExpr *>(expr);
    show_name = value_expr->to_string();
  } else if (expr->type() == ExprType::COMPOUND) {
    CompoundExpr *compound_expr = static_cast<CompoundExpr *>(expr);
    spec = new TupleCellSpec(expr);
    show_name = compound_expr->get_show_name();
  } else if (expr->type() == ExprType::FUNC) {
    spec = new TupleCellSpec(expr);
    show_name = expr_to_string(expr, is_multi_table);
  }
  if (alias) {
    spec->set_alias(std::string(alias));
  } else {
    spec->set_alias(show_name);
  }
  tuple_.add_cell_spec(spec);
}

RC ProjectOperator::tuple_cell_spec_at(int index, const TupleCellSpec *&spec) const
{
  return tuple_.cell_spec_at(index, spec);
}
