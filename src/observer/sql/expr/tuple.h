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
// Created by Wangyunlai on 2021/5/14.
//

#pragma once

#include <memory>
#include <vector>

#include "common/log/log.h"
#include "sql/parser/parse.h"
#include "sql/expr/tuple_cell.h"
#include "sql/expr/expression.h"
#include "storage/common/limits.h"
#include "storage/record/record.h"

class Table;

class TupleCellSpec {
public:
  TupleCellSpec() = default;
  TupleCellSpec(Expression *expr) : expression_(expr)
  {}

  // association, not composition
  ~TupleCellSpec() = default;

  void set_alias(const std::string &alias)
  {
    this->alias_ = alias;
  }
  const char *alias() const
  {
    return alias_.c_str();
  }

  Expression *expression() const
  {
    return expression_;
  }

private:
  std::string alias_;
  Expression *expression_ = nullptr;
};

class Tuple {
public:
  Tuple() = default;
  virtual ~Tuple() = default;

  virtual int cell_num() const = 0;
  virtual RC cell_at(int index, TupleCell &cell) const = 0;
  virtual RC find_cell(const Field &field, TupleCell &cell) const = 0;

  virtual RC cell_spec_at(int index, const TupleCellSpec *&spec) const = 0;
  virtual Tuple *copy() const = 0;
};

class RowTuple : public Tuple {
public:
  RowTuple() = default;
  virtual ~RowTuple()
  {
    if (!is_copy_) {
      for (TupleCellSpec *spec : speces_) {
        delete spec->expression();
        delete spec;
      }
      speces_.clear();
    }
  }

  void set_record(Record *record)
  {
    this->record_ = record;
  }

  void set_schema(const Table *table, const std::vector<FieldMeta> *fields)
  {
    table_ = table;
    this->speces_.reserve(fields->size());
    for (const FieldMeta &field : *fields) {
      speces_.push_back(new TupleCellSpec(new FieldExpr(table, &field)));
    }
  }

  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    const TupleCellSpec *spec = speces_[index];
    FieldExpr *field_expr = (FieldExpr *)spec->expression();
    const FieldMeta *field_meta = field_expr->field().meta();
    const char *data = this->record_->data() + field_meta->offset();
    int len = field_meta->len();
    AttrType type = field_meta->type();
    if (is_mem_null((void *)data, type, len)) {
      cell.set_type(NULLS);
      return RC::SUCCESS;
    }
    cell.set_type(field_meta->type());
    cell.set_data(this->record_->data() + field_meta->offset());
    cell.set_length(field_meta->len());
    return RC::SUCCESS;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    const char *table_name = field.table_name();
    if (0 != strcmp(table_name, table_->name())) {
      return RC::NOTFOUND;
    }

    const char *field_name = field.field_name();
    for (size_t i = 0; i < speces_.size(); ++i) {
      const FieldExpr *field_expr = (const FieldExpr *)speces_[i]->expression();
      const Field &field = field_expr->field();
      if (0 == strcmp(field_name, field.field_name())) {
        return cell_at(i, cell);
      }
    }
    return RC::NOTFOUND;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

  Record &record()
  {
    return *record_;
  }

  const Record &record() const
  {
    return *record_;
  }
  Tuple *copy() const override
  {
    RowTuple *new_tuple = new RowTuple();
    new_tuple->record_ = record_;
    new_tuple->table_ = table_;
    new_tuple->speces_ = speces_;
    new_tuple->is_copy_ = true;
    return new_tuple;
  }

private:
  Record *record_ = nullptr;
  const Table *table_ = nullptr;
  std::vector<TupleCellSpec *> speces_;
  bool is_copy_{false};
};

/*
class CompositeTuple : public Tuple
{
public:
  int cell_num() const override;
  RC  cell_at(int index, TupleCell &cell) const = 0;
private:
  int cell_num_ = 0;
  std::vector<Tuple *> tuples_;
};
*/

class ProjectTuple : public Tuple {
public:
  ProjectTuple() = default;
  virtual ~ProjectTuple()
  {
    if (!is_copy_) {
      for (TupleCellSpec *spec : speces_) {
        delete spec;
      }
      speces_.clear();
    }
  }

  Tuple *tuple() const
  {
    return tuple_;
  }
  void set_tuple(Tuple *tuple)
  {
    this->tuple_ = tuple;
  }

  void add_cell_spec(TupleCellSpec *spec)
  {
    speces_.push_back(spec);
  }
  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::GENERIC_ERROR;
    }
    if (tuple_ == nullptr) {
      return RC::GENERIC_ERROR;
    }

    const TupleCellSpec *spec = speces_[index];
    return spec->expression()->get_value(*tuple_, cell);
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    return tuple_->find_cell(field, cell);
  }
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }
  Tuple *copy() const override
  {
    ProjectTuple *new_tuple = new ProjectTuple();
    new_tuple->speces_ = speces_;
    new_tuple->tuple_ = tuple_;
    new_tuple->is_copy_ = true;
    return new_tuple;
  }

private:
  std::vector<TupleCellSpec *> speces_;
  Tuple *tuple_ = nullptr;
  bool is_copy_{false};
};

class CartesianTuple : public Tuple {
public:
  CartesianTuple() = default;
  CartesianTuple(Tuple *t) : tuples_(std::vector<Tuple *>{t})
  {}
  CartesianTuple(const std::vector<Tuple *> &tuples) : tuples_(tuples)
  {}
  virtual ~CartesianTuple() = default;

  void set_tuples(const std::vector<Tuple *> &tuples)
  {
    tuples_ = tuples;
  }

  void add_tuple(Tuple *t)
  {
    tuples_.push_back(t);
  }

  int cell_num() const override
  {
    int cell_num = 0;
    for (Tuple *t : tuples_) {
      cell_num += t->cell_num();
    }
    return cell_num;
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= cell_num()) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    int cur_index = 0;
    for (Tuple *t : tuples_) {
      if (index < cur_index + t->cell_num()) {
        int rel_index = index - cur_index;
        return t->cell_at(rel_index, cell);
      }
      cur_index += t->cell_num();
    }
    LOG_ERROR("CartesianTuple::cell_at() logic error");
    return RC::INTERNAL;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    RC rc = RC::SUCCESS;
    for (Tuple *t : tuples_) {
      rc = t->find_cell(field, cell);
      if (rc == RC::SUCCESS) {
        break;
      }
    }
    return rc;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= cell_num()) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    int cur_index = 0;
    for (Tuple *t : tuples_) {
      if (index < cur_index + t->cell_num()) {
        int rel_index = index - cur_index;
        return t->cell_spec_at(rel_index, spec);
      }
      cur_index += t->cell_num();
    }
    LOG_ERROR("CartesianTuple::cell_at() logic error");
    return RC::INTERNAL;
  }
  Tuple *copy() const override
  {
    CartesianTuple *new_tuple = new CartesianTuple();
    new_tuple->tuples_ = tuples_;
    return new_tuple;
  }

private:
  std::vector<Tuple *> tuples_;
};
