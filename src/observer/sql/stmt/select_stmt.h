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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <unordered_map>
#include <vector>

#include "rc.h"
#include "sql/expr/expression.h"
#include "sql/stmt/stmt.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

using Tables = std::vector<Table *>;
using TableMap = std::unordered_map<std::string, Table *>;

struct JoinStmt {
  Table *join_table;
  FilterStmt *filter_stmt;
};

class SelectStmt : public Stmt {
public:
  SelectStmt() = default;
  ~SelectStmt();

  StmtType type() const override
  {
    return StmtType::SELECT;
  }

public:
  static RC create(Db *db, Selects &select_sql, Stmt *&stmt);

public:
  const std::vector<Table *> &tables() const
  {
    return tables_;
  }
  const std::vector<JoinStmt> &join_stmts() const
  {
    return join_stmts_;
  }
  const std::vector<Expression *> &exprs() const
  {
    return exprs_;
  }
  FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }
  bool select_attributes() const
  {
    return select_attributes_;
  }
  void Print() const;

private:
  bool select_attributes_{true};
  std::vector<Expression *> exprs_;
  std::vector<JoinStmt> join_stmts_;
  Tables tables_;
  FilterStmt *filter_stmt_ = nullptr;
};

