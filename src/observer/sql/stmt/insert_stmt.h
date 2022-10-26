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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include "rc.h"
#include "sql/stmt/stmt.h"
#include <vector>

class Table;
class Db;

class InsertStmt : public Stmt
{
public:

  InsertStmt(Table *table, const std::vector<std::vector<Value>> &value_pairs, int value_amount):
    table_(table), value_pairs_(value_pairs), value_amount_(value_amount)
  {}

  StmtType type() const override {
    return StmtType::INSERT;
  }
public:
  static RC create(Db *db, Inserts &insert_sql, Stmt *&stmt);

public:
  Table *table() const {return table_;}
  const std::vector<std::vector<Value>> value_pairs() const { return value_pairs_; }
  int value_amount() const { return value_amount_; }

private:
  Table *table_ = nullptr;
  std::vector<std::vector<Value>> value_pairs_;
  int value_amount_ = 0;
};

