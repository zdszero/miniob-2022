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

#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"

class Table;

struct UpdateUnit {
  const FieldMeta* update_field_meta{nullptr};
  Expression *update_expr{nullptr};
  SelectStmt *select_stmt{nullptr};
  bool is_select{false};
};

class UpdateStmt : public Stmt
{
public:

  UpdateStmt() = default;
  ~UpdateStmt() override;

  StmtType type() const override { return StmtType::UPDATE; }

public:
  static RC create(Db *db, Updates &update_sql, Stmt *&stmt);
  Table *table() const { return table_; }
  FilterStmt *filter_stmt() const { return filter_stmt_; }
  const std::vector<UpdateUnit> &units() const { return units_; }

private:
  Table *table_ = nullptr;
  FilterStmt *filter_stmt_ = nullptr;
  std::vector<UpdateUnit> units_;
};

