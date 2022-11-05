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

#pragma once

#include <cassert>
#include <string.h>
#include <unordered_map>
#include "storage/common/field.h"
#include "sql/expr/tuple_cell.h"

class Tuple;

enum class ExprType {
  NONE,
  FIELD,
  AGGREGATE,
  VALUE,
  COMPOUND,
  FUNC,
};

class Expression {
public:
  Expression() = default;
  virtual ~Expression() = default;

  virtual RC get_value(const Tuple &tuple, TupleCell &cell) = 0;
  virtual ExprType type() const = 0;
};

class FieldExpr : public Expression {
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field)
  {}

  virtual ~FieldExpr() = default;

  ExprType type() const override
  {
    return ExprType::FIELD;
  }

  Field &field()
  {
    return field_;
  }

  const Field &field() const
  {
    return field_;
  }

  const char *table_name() const
  {
    return field_.table_name();
  }

  const char *field_name() const
  {
    return field_.field_name();
  }

  RC get_value(const Tuple &tuple, TupleCell &cell) override;

private:
  Field field_;
};

class AggregateExpr : public Expression {
public:
  AggregateExpr() = default;
  AggregateExpr(AggrType aggr_type, const Table *table, const FieldMeta *field)
      : aggr_type_(aggr_type), field_(table, field)
  {}

  virtual ~AggregateExpr() = default;

  AggrType aggr_type() const
  {
    return aggr_type_;
  }

  ExprType type() const override
  {
    return ExprType::AGGREGATE;
  }

  Field &field()
  {
    return field_;
  }

  const Field &field() const
  {
    return field_;
  }

  const char *table_name() const
  {
    return field_.table_name();
  }

  const char *field_name() const
  {
    if (is_star()) {
      return "*";
    }
    return field_.field_name();
  }

  bool is_star() const
  {
    return field_.meta() ==  nullptr;
  }
  void set_cell(const TupleCell &cell)
  {
    cell_ = cell;
  }

  RC get_value(const Tuple &tuple, TupleCell &cell) override;

private:
  AggrType aggr_type_;
  Field field_;
  TupleCell cell_;
};

class ValueExpr : public Expression {
public:
  ValueExpr() = default;
  ValueExpr(const Value &value) : tuple_cell_(value)
  {
    if (value.type == CHARS) {
      tuple_cell_.set_length(strlen((const char *)value.data));
    }
  }

  virtual ~ValueExpr() = default;

  RC get_value(const Tuple &tuple, TupleCell &cell) override;
  ExprType type() const override
  {
    return ExprType::VALUE;
  }

  void get_tuple_cell(TupleCell &cell) const
  {
    cell = tuple_cell_;
  }

  std::string to_string() const;

private:
  TupleCell tuple_cell_;
};

class CompoundExpr : public Expression {
public:
  CompoundExpr(Expression *left, Expression *right, MathOp mathop) : left_(left), right_(right), mathop_(mathop)
  {
    // avoid value_destroy free dangling pointer
    value_init_null(&result_);
  }
  virtual ~CompoundExpr()
  {
    value_destroy(&result_);
    if (left_) {
      delete left_;
    }
    if (right_) {
      delete right_;
    }
  }
  RC get_value(const Tuple &tuple, TupleCell &cell) override;
  ExprType type() const override
  {
    return ExprType::COMPOUND;
  }
  MathOp get_mathop() const
  {
    return mathop_;
  }
  Expression *get_left_expr() const
  {
    return left_;
  }
  Expression *get_right_expr() const
  {
    return right_;
  }
  std::string get_show_name() const
  {
    return show_name_;
  }
  void set_show_name(const std::string &name)
  {
    show_name_ = name;
  }
  

private:
  Expression *left_;
  Expression *right_;
  MathOp mathop_;
  Value result_;
  std::string show_name_;
};

class FuncExpr : public Expression {
public:
  FuncExpr(FuncType functype, Expression *left, Expression *right):
    functype_(functype), left_(left), right_(right)
  {
    value_init_null(&val_);
  }
  ~FuncExpr() {
    delete left_;
    left_ = nullptr;
    delete right_;
    right_ = nullptr;
    value_destroy(&val_);
  }

  RC get_value(const Tuple &tuple, TupleCell &cell) override;
  ExprType type() const override { return ExprType::FUNC; }
  FuncType functype() const { return functype_; }
  Expression *left() const { return left_; }
  Expression *right() const { return right_; }

private:
  FuncType functype_;
  Expression *left_{nullptr};
  Expression *right_{nullptr};
  Value val_;
};

class ExprContext {
public:
  ExprContext() = default;
  ExprContext(Table *default_table) : default_table_(default_table)
  {
    tables_.push_back(default_table);
    table_map_.insert({default_table->name(), default_table});
  }
  ExprContext(const std::vector<Table *> &tables): tables_(tables)
  {
    default_table_ = tables[0];
    for (Table *tbl : tables) {
      table_map_.insert({tbl->name(), tbl});
    }
  }
  Table* GetDefaultTable() const;
  const std::vector<Table *> &GetTables() const;
  Table *GetTable(const RelAttr &attr) const;
  Table *GetTable(const char *table_name) const;
  bool HasTable(const char *table_name) const;
  const std::unordered_map<std::string, std::string> &GetAlias() const;
  size_t GetTableSize() const;
  const FieldMeta *GetFieldMeta(const RelAttr &attr) const;
  void AddTable(Table *tbl);
  void SetAlias(const char *table_name, const char *alias);
  void AddFieldMeta(const RelAttr &attr, const FieldMeta *meta);
  void ClearFieldMeta();
  void SetCorrelation(const ExprContext &ctx);

private:
  Table *default_table_{nullptr};
  std::vector<Table *> tables_;
  // alias -> table name
  std::unordered_map<std::string, std::string> alias_map_;
  // relation name -> table
  std::unordered_map<std::string, Table *> table_map_;
  // relation.field -> field meta
  std::unordered_map<std::string, const FieldMeta *> field_map_;

  std::string construct_field_key(const RelAttr &attr) const;
};

class ExprFactory {
public:
  static Expression *create(ast *t, const ExprContext &ctx);
};
