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
// Created by WangYunlai on 2021/6/7.
//

#pragma once

#include "sql/operator/operator.h"
#include "storage/record/record_manager.h"
#include "rc.h"

class Table;

class TableScanOperator : public Operator
{
public:
  TableScanOperator(Table *table, Tuple *outer_tuple=nullptr)
    : table_(table), outer_tuple_(outer_tuple)
  {}

  virtual ~TableScanOperator();

  RC open() override;
  RC next() override;
  RC close() override;
  Tuple * current_tuple() override;
  OperatorType type() override
  {
    return OperatorType::TABLE_SCAN;
  }

  Tuple * current_tuple_copy();

  // int tuple_cell_num() const override
  // {
  //   return tuple_.cell_num();
  // }

  // RC tuple_cell_spec_at(int index, TupleCellSpec &spec) const override;
private:
  Table *table_ = nullptr;
  Tuple *outer_tuple_;
  RecordFileScanner record_scanner_;
  Record current_record_;
  RowTuple tuple_;
  CartesianTuple cart_tuple_;
  std::vector<Tuple *> tuple_copies_;
  std::vector<Record *> record_copies;
};
