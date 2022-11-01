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
// Created by WangYunlai on 2022/6/27.
//

#include "common/lang/defer.h"
#include "common/log/log.h"
#include "sql/operator/predicate_operator.h"
#include "sql/operator/subselect_operator.h"
#include "sql/operator/table_scan_operator.h"
#include "storage/record/record.h"
#include "storage/common/field.h"

RC PredicateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open();
}

RC PredicateOperator::next()
{
  RC rc = RC::SUCCESS;
  Operator *oper = children_[0];

  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    if (do_predicate(*tuple)) {
      return rc;
    }
  }
  return rc;
}

RC PredicateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *PredicateOperator::current_tuple()
{
  return children_[0]->current_tuple();
}

bool PredicateOperator::do_compare_unit(Tuple &tuple, const FilterUnit *filter_unit)
{
  CompOp comp = filter_unit->comp();
  TupleCell left_cell;
  TupleCell right_cell;
  RC rc;

  assert(filter_unit->left() && filter_unit->right());
  rc = filter_unit->left()->get_value(tuple, left_cell);
  assert(rc == RC::SUCCESS);
  rc = filter_unit->right()->get_value(tuple, right_cell);
  assert(rc == RC::SUCCESS);

  if (comp == IS) {
    return left_cell.attr_type() == NULLS;
  }
  if (comp == IS_NOT) {
    return left_cell.attr_type() != NULLS;
  }
  if (left_cell.attr_type() == NULLS || right_cell.attr_type() == NULLS) {
    return false;
  }

  if (comp == STR_LIKE || comp == STR_NOT_LIKE) {
    return left_cell.wildcard_compare(right_cell, comp == STR_NOT_LIKE);
  }

  bool filter_result = false;
  if (left_cell.attr_type() == NULLS || right_cell.attr_type() == NULLS) {
    return false;
  }
  const int compare = left_cell.compare(right_cell);
  switch (comp) {
    case EQUAL_TO: {
      filter_result = (0 == compare);
    } break;
    case LESS_EQUAL: {
      filter_result = (compare <= 0);
    } break;
    case NOT_EQUAL: {
      filter_result = (compare != 0);
    } break;
    case LESS_THAN: {
      filter_result = (compare < 0);
    } break;
    case GREAT_EQUAL: {
      filter_result = (compare >= 0);
    } break;
    case GREAT_THAN: {
      filter_result = (compare > 0);
    } break;
    default: {
      LOG_WARN("invalid compare type: %d", comp);
    } break;
  }
  return filter_result;
}

bool PredicateOperator::do_exists_unit(Tuple &tuple, const FilterUnit *filter_unit)
{
  CompOp comp = filter_unit->comp();
  assert(comp == EXISTS || comp == NOT_EXISTS);
  bool ret = false;
  if (filter_unit->is_correlated()) {
    // which table is inner table ?
    assert(filter_unit->sub_select()->tables().size() == 1);
    Table *table = filter_unit->sub_select()->tables()[0];
    TableScanOperator scan_oper(table);
    PredicateOperator pred_oper(filter_unit->sub_select()->filter_stmt());
    RC rc;
    rc = scan_oper.open();
    assert(rc == RC::SUCCESS);
    while ((rc = scan_oper.next()) == RC::SUCCESS) {
      CartesianTuple cartesian_t;
      Tuple *t = scan_oper.current_tuple();
      cartesian_t.add_tuple(&tuple);
      cartesian_t.add_tuple(t);
      if (pred_oper.do_predicate(cartesian_t)) {
        ret = true;
        break;
      }
    }
  } else {
    ret = filter_unit->exists();
  }
  if (comp == EXISTS) {
    return ret;
  } else {
    return !ret;
  }
}

bool PredicateOperator::do_in_unit(Tuple &tuple, const FilterUnit *filter_unit)
{
  CompOp comp = filter_unit->comp();
  assert(comp == IN || comp == NOT_IN);
  TupleCell cell;
  RC rc = filter_unit->left()->get_value(tuple, cell);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get value in predicate in");
    return false;
  }
  if (cell.attr_type() == NULLS) {
    return false;
  }
  std::vector<TupleCell> target_cells;
  if (filter_unit->is_correlated()) {
    SelectStmt *sub_select = filter_unit->sub_select();
    assert(sub_select->tables().size() == 1);
    assert(sub_select->exprs().size() == 1);
    Table *table = sub_select->tables()[0];
    Expression *expr = sub_select->exprs()[0];
    TableScanOperator scan_oper(table);
    PredicateOperator pred_oper(filter_unit->sub_select()->filter_stmt());
    RC rc;
    rc = scan_oper.open();
    assert(rc == RC::SUCCESS);
    while ((rc = scan_oper.next()) == RC::SUCCESS) {
      CartesianTuple cartesian_t;
      Tuple *t = scan_oper.current_tuple();
      cartesian_t.add_tuple(&tuple);
      cartesian_t.add_tuple(t);
      if (pred_oper.do_predicate(cartesian_t)) {
        TupleCell cell;
        expr->get_value(*t, cell);
        target_cells.push_back(cell);
      }
    }
  } else {
    target_cells = filter_unit->in_cells();
  }
  bool has_null = false;
  for (const TupleCell &c : target_cells) {
    if (c.attr_type() == NULLS) {
      has_null = true;
      break;
    }
  }
  if (has_null && comp == NOT_IN) {
    return false;
  }
  bool ret  = false;
  for (const TupleCell &c : target_cells) {
    if (c == cell) {
      ret = true;
      break;
    }
  }
  if (comp == IN) {
    return ret;
  } else {
    return !ret;
  }
}

bool PredicateOperator::do_filter_unit(Tuple &tuple, const FilterUnit *filter_unit)
{
  ConditionType cond = filter_unit->condition_type();
  if (cond == ConditionType::COND_COMPARE) {
    return do_compare_unit(tuple, filter_unit);
  } else if (cond == ConditionType::COND_EXISTS) {
    return do_exists_unit(tuple, filter_unit);
  } else {
    return do_in_unit(tuple, filter_unit);
  }
}

bool PredicateOperator::do_predicate(Tuple &tuple)
{
  if (filter_stmt_ == nullptr || filter_stmt_->filter_units().empty()) {
    return true;
  }

  for (const FilterUnit *filter_unit : filter_stmt_->filter_units()) {
    if (do_filter_unit(tuple, filter_unit) == false) {
      return false;
    }
  }
  return true;
}

// int PredicateOperator::tuple_cell_num() const
// {
//   return children_[0]->tuple_cell_num();
// }
// RC PredicateOperator::tuple_cell_spec_at(int index, TupleCellSpec &spec) const
// {
//   return children_[0]->tuple_cell_spec_at(index, spec);
// }
