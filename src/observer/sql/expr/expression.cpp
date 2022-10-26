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
// Created by Wangyunlai on 2022/07/05.
//

#include "common/lang/string.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "util/ast_util.h"
#include <sstream>


RC FieldExpr::get_value(const Tuple &tuple, TupleCell &cell)
{
  return tuple.find_cell(field_, cell);
}

RC ValueExpr::get_value(const Tuple &tuple, TupleCell &cell)
{
  cell = tuple_cell_;
  return RC::SUCCESS;
}

std::string ValueExpr::to_string() const
{
  std::stringstream ss;
  tuple_cell_.to_string(ss);
  return ss.str();
}

RC AggregateExpr::get_value(const Tuple &tuple, TupleCell &cell)
{
  return tuple.find_cell(field_, cell);
}

RC CompoundExpr::get_value(const Tuple &tuple, TupleCell &cell)
{
  float left_val, right_val;
  TupleCell left_cell, right_cell;
  if (left_) {
    left_->get_value(tuple, left_cell);
    left_val = left_cell.cast_to_number();
  } else {
    left_val = 0;
  }
  right_->get_value(tuple, right_cell);
  right_val = right_cell.cast_to_number();
  float res;
  switch (mathop_) {
    case MATH_ADD:
      res = left_val + right_val;
      break;
    case MATH_SUB:
      res = left_val - right_val;
      break;
    case MATH_MUL:
      res = left_val * right_val;
      break;
    case MATH_DIV:
      res = left_val / right_val;
      break;
    default:
      assert(false);
  }
  cell.set_type(FLOATS);
  value_init_float(&result_, res);
  cell.set_data((char *)result_.data);
  return RC::SUCCESS;
}

Expression *ExprFactory::create(ast *t, const ExprContext &ctx)
{
  if (t == nullptr) {
    return nullptr;
  }
  assert(t->nodetype != NodeType::UNDEFINEDN);
  if (t->nodetype == NodeType::ATTRN) {
    assert(strcmp("*", t->attr.attribute_name) != 0);
    return new FieldExpr(ctx.GetTable(t->attr), ctx.GetFieldMeta(t->attr));
  } else if (t->nodetype == NodeType::AGGRN) {
    if (t->aggr.is_attr) {
      return new AggregateExpr(t->aggr.aggr_type, ctx.GetTable(t->aggr.attr), ctx.GetFieldMeta(t->aggr.attr));
    } else {
      return new ValueExpr(t->aggr.value);
    }
  } else if (t->nodetype == NodeType::VALN) {
    return new ValueExpr(t->val);
  } else {
    assert(t->nodetype == NodeType::OPN);
    Expression *left_expr = create(t->op.left, ctx);
    Expression *right_expr = create(t->op.right, ctx);
    CompoundExpr *ret = new CompoundExpr(left_expr, right_expr, t->op.mathop);
    ret->set_show_name(ast_to_string(t));
    return ret;
  }
}
