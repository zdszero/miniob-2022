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
#include "util/date.h"
#include <cmath>

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
  cell = cell_;
  return RC::SUCCESS;
}

RC CompoundExpr::get_value(const Tuple &tuple, TupleCell &cell)
{
  float left_val, right_val;
  TupleCell left_cell, right_cell;
  if (left_) {
    left_->get_value(tuple, left_cell);
    if (left_cell.attr_type() == NULLS) {
      goto set_null;
    }
    left_val = left_cell.cast_to_number();
  } else {
    left_val = 0;
  }
  right_->get_value(tuple, right_cell);
  if (right_cell.attr_type() == NULLS) {
    goto set_null;
  }
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
      if (right_val == 0) {
        goto set_null;
      }
      res = left_val / right_val;
      break;
    default:
      assert(false);
  }
  cell.set_type(FLOATS);
  value_init_float(&result_, res);
  cell.set_data((char *)result_.data);
  if (false) {
  set_null:
    cell.set_type(NULLS);
    value_init_null(&result_);
    return RC::SUCCESS;
  }
  return RC::SUCCESS;
}

static int pow10(int n)
{
  if (n == 0) {
    return 1;
  }
  if (n % 2 == 1) {
    return 10 * pow10(n-1);
  }
  int half = pow10(n / 2);
  return half * half;
}

RC FuncExpr::get_value(const Tuple &tuple, TupleCell &cell)
{
  if (functype_ == LENGTHF) {
    TupleCell left_cell;
    left_->get_value(tuple, left_cell);
    if (left_cell.attr_type() != CHARS) {
      LOG_WARN("length() can only be used on chars");
      return RC::MISMATCH;
    }
    size_t length = strlen(left_cell.data());
    value_destroy(&val_);
    value_init_integer(&val_, length);
  } else if (functype_ == ROUNDF) {
    TupleCell left_cell, right_cell;
    left_->get_value(tuple, left_cell);
    if (left_cell.attr_type() != FLOATS) {
      LOG_WARN("round() can only be used on floats");
      return RC::MISMATCH;
    }
    float v = *(float *)(left_cell.data());
    int n;
    if (right_) {
      right_->get_value(tuple, right_cell);
      n = *(int *)(right_cell.data());
    } else {
      n = 0;
    }
    float pow = pow10(n);
    v = std::round(v * pow) / pow;
    value_destroy(&val_);
    value_init_float(&val_, v);
  } else if (functype_ == DATE_FORMATF) {
    TupleCell left_cell, right_cell;
    left_->get_value(tuple, left_cell);
    right_->get_value(tuple, right_cell);
    int32_t date;
    if (left_cell.attr_type() == CHARS) {
      RC rc = string_to_date(left_cell.data(), date);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } else if (left_cell.attr_type() == DATES) {
      date = *(int32_t *)left_cell.data();
    } else {
      LOG_WARN("date_format() can only be used on date");
      return RC::MISMATCH;
    }
    const char *format = right_cell.data();
    value_destroy(&val_);
    value_init_string(&val_, format_date(date, format).c_str());
  }
  cell = TupleCell(val_);
  return RC::SUCCESS;
}

Table *ExprContext::GetDefaultTable() const
{
  return default_table_;
}
const std::vector<Table *> &ExprContext::GetTables() const
{
  return tables_;
}
Table *ExprContext::GetTable(const RelAttr &attr) const
{
  if (attr.relation_name == nullptr) {
    return default_table_;
  }
  std::string search_name;
  if (alias_map_.count(attr.relation_name)) {
    search_name = alias_map_.at(attr.relation_name);
  } else {
    search_name = attr.relation_name;
  }
  auto iter = table_map_.find(search_name);
  if (iter == table_map_.end()) {
    return default_table_;
  }
  return iter->second;
}
Table *ExprContext::GetTable(const char *table_name) const
{
  std::string search_name;
  if (alias_map_.count(table_name)) {
    search_name = alias_map_.at(table_name);
  } else {
    search_name = table_name;
  }
  auto iter = table_map_.find(table_name);
  if (iter == table_map_.end()) {
    return nullptr;
  }
  return iter->second;
}
bool ExprContext::HasTable(const char *table_name) const
{
  return alias_map_.count(table_name) || table_map_.count(table_name);
}
const std::unordered_map<std::string, std::string> &ExprContext::GetAlias() const
{
  return alias_map_;
}
size_t ExprContext::GetTableSize() const
{
  return table_map_.size();
}
const FieldMeta *ExprContext::GetFieldMeta(const RelAttr &attr) const
{
  return field_map_.at(construct_field_key(attr));
}
void ExprContext::AddTable(Table *tbl)
{
  if (default_table_ == nullptr) {
    default_table_ = tbl;
  }
  tables_.push_back(tbl);
  table_map_[tbl->name()] = tbl;
}
void ExprContext::SetAlias(const char *table_name, const char *alias)
{
  alias_map_[alias] = table_name;
}
void ExprContext::AddFieldMeta(const RelAttr &attr, const FieldMeta *meta)
{
  field_map_[construct_field_key(attr)] = meta;
}
void ExprContext::ClearFieldMeta()
{
  field_map_.clear();
}
std::string ExprContext::construct_field_key(const RelAttr &attr) const
{
  // field key: origin_table.attr
  std::string field_key = "";
  if (attr.relation_name) {
    std::string table_name;
    if (alias_map_.count(attr.relation_name)) {
      table_name = alias_map_.at(attr.relation_name);
    } else {
      table_name = attr.relation_name;
    }
    field_key += table_name;
    field_key += ".";
  }
  field_key += attr.attribute_name;
  return field_key;
}
void ExprContext::SetCorrelation(const ExprContext &ctx)
{
  this->tables_ = ctx.tables_;
  this->table_map_ = ctx.table_map_;
  this->alias_map_ = ctx.alias_map_;
}

Expression *ExprFactory::create(ast *t, const ExprContext &ctx)
{
  if (t == nullptr) {
    return nullptr;
  }
  assert(t->nodetype != NodeType::UNDEFINEDN);
  if (t->nodetype == NodeType::ATTRN) {
    assert(strcmp("*", t->attr.attribute_name) != 0);
    Table *tbl = ctx.GetTable(t->attr);
    const FieldMeta *field_meta = ctx.GetFieldMeta(t->attr);
    return new FieldExpr(tbl, field_meta);
  } else if (t->nodetype == NodeType::AGGRN) {
    if (t->aggr.is_attr) {
      const FieldMeta *field_meta;
      if (strcmp(t->aggr.attr.attribute_name, "*") == 0) {
        field_meta = nullptr;
      } else {
        field_meta = ctx.GetFieldMeta(t->aggr.attr);
      }
      return new AggregateExpr(t->aggr.aggr_type, ctx.GetTable(t->aggr.attr), field_meta);
    } else {
      return new ValueExpr(t->aggr.value);
    }
  } else if (t->nodetype == NodeType::VALN) {
    return new ValueExpr(t->val);
  } else if (t->nodetype == NodeType::OPN) {
    Expression *left_expr = create(t->op.left, ctx);
    Expression *right_expr = create(t->op.right, ctx);
    CompoundExpr *ret = new CompoundExpr(left_expr, right_expr, t->op.mathop);
    ret->set_show_name(ast_to_string(t));
    return ret;
  } else {
    assert(t->nodetype == NodeType::FUNCN);
    Expression *left_expr = create(t->func.left, ctx);
    Expression *right_expr = create(t->func.right, ctx);
    FuncExpr *ret = new FuncExpr(t->func.functype, left_expr, right_expr);
    return ret;
  }
}
