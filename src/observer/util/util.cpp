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
// Created by wangyunlai on 2022/9/28
//

#include <cstdio>
#include <string.h>
#include <sstream>
#include "util/util.h"

std::string double2string(double v)
{
  char buf[256];
  snprintf(buf, sizeof(buf), "%.2f", v);
  size_t len = strlen(buf);
  while (buf[len - 1] == '0') {
    len--;
  }
  if (buf[len - 1] == '.') {
    len--;
  }

  return std::string(buf, len);
}

bool is_numeric_type(AttrType type)
{
  return type == INTS || type == FLOATS;
}

std::string value2string(const Value &value)
{
  if (value.type == INTS) {
    return std::to_string(*(int *)value.data);
  } else if (value.type == FLOATS) {
    return double2string(static_cast<double>(*(float *)value.data));
  } else if (value.type == CHARS) {
    return (char *)value.data;
  }
  return "";
}

std::string mathop_to_string(MathOp mathop)
{
  switch (mathop) {
    case MATH_ADD:
      return "+";
    case MATH_SUB:
      return "-";
    case MATH_MUL:
      return "*";
    case MATH_DIV:
      return "/";
    default:
      break;
  }
  return "";
}

std::string comp_to_string(CompOp comp)
{
  switch (comp) {
    case EQUAL_TO:
      return "=";
    case LESS_EQUAL:
      return "<=";
    case NOT_EQUAL:
      return "!=";
    case LESS_THAN:
      return "<";
    case GREAT_EQUAL:
      return ">=";
    case GREAT_THAN:
      return ">";
    case STR_LIKE:
      return "like";
    case STR_NOT_LIKE:
      return "not like";
    default:
      break;
  }
  return "";
}

std::string aggregate_func_string(AggrType aggr_type)
{
  switch (aggr_type) {
    case MAXS:
      return "max";
    case MINS:
      return "min";
    case AVGS:
      return "avg";
    case SUMS:
      return "sum";
    case COUNTS:
      return "count";
    default:
      break;
  }
  return "";
}

std::string expr_to_string(Expression *expr, bool is_multi_table)
{
  if (expr == nullptr) {
    return "";
  }
  std::stringstream ss;
  if (expr->type() == ExprType::FIELD) {
    FieldExpr *field_expr = static_cast<FieldExpr *>(expr);
    if (is_multi_table) {
      ss << field_expr->table_name() << ".";
    }
    ss << field_expr->field_name();
  } else if (expr->type() == ExprType::VALUE) {
    ValueExpr *val_expr = static_cast<ValueExpr *>(expr);
    TupleCell cell;
    val_expr->get_tuple_cell(cell);
    cell.to_string(ss);
  } else if (expr->type() == ExprType::AGGREGATE) {
    AggregateExpr *aggr_expr = static_cast<AggregateExpr *>(expr);
    ss << aggregate_func_string(aggr_expr->aggr_type()) << "(";
    if (is_multi_table) {
      ss << aggr_expr->table_name() << ".";
    }
    ss << aggr_expr->field_name() << ")";
  } else if (expr->type() == ExprType::COMPOUND) {
    CompoundExpr *compound_expr = static_cast<CompoundExpr *>(expr);
    ss << compound_expr->get_show_name();
  }
  return ss.str();
}

void print_expr(Expression *expr, int level)
{
  if (expr == nullptr) {
    return;
  }
  for (int i = 0; i < level; i++) {
    std::cout << "  ";
  }
  if (expr->type() == ExprType::FIELD) {
    FieldExpr *field_expr = static_cast<FieldExpr *>(expr);
    printf("field: %s:%s\n", field_expr->field().table_name(), field_expr->field_name());
  } else if (expr->type() == ExprType::VALUE) {
    std::stringstream ss;
    ValueExpr *val_expr = static_cast<ValueExpr *>(expr);
    TupleCell cell;
    val_expr->get_tuple_cell(cell);
    cell.to_string(ss);
    std::cout << ss.str() << std::endl;
  } else if (expr->type() == ExprType::AGGREGATE) {
    AggregateExpr *aggr_expr = static_cast<AggregateExpr *>(expr);
    std::cout << aggregate_func_string(aggr_expr->aggr_type()) << "("
            << aggr_expr->field_name() << ")" << std::endl;
  } else if (expr->type() == ExprType::COMPOUND) {
    CompoundExpr *compound_expr = static_cast<CompoundExpr *>(expr);
    std::cout << mathop_to_string(compound_expr->get_mathop()) << std::endl;
    print_expr(compound_expr->get_left_expr(), level + 1);
    print_expr(compound_expr->get_right_expr(), level + 1);
  }
}
