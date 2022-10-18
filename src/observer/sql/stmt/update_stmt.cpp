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

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "storage/common/db.h"

UpdateStmt::~UpdateStmt() {
  if (filter_stmt_) {
    delete(filter_stmt_);
  }
}

RC UpdateStmt::create(Db *db, Updates &updates_sql, Stmt *&stmt)
{
  // UPDATE field = value ON table WHERE filter
  const char *table_name = updates_sql.relation_name;
  if (nullptr == db || table_name == nullptr) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // table
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  // field
  const char *attr_name = updates_sql.attribute_name;
  const FieldMeta *field_meta = table->table_meta().field(attr_name);
  if (field_meta == nullptr) {
    LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), attr_name);
    return RC::SCHEMA_FIELD_MISSING;
  }
  // filter
  std::unordered_map<std::string, Table *> table_map;
  FilterStmt *filter_stmt = nullptr;
  table_map.emplace(std::pair<std::string, Table *>(table_name, table));
  RC rc = FilterStmt::create(db, table, &table_map, updates_sql.conditions, updates_sql.condition_num, filter_stmt);
  if (rc < 0) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // everything alright
  UpdateStmt *update_stmt = new UpdateStmt();
  update_stmt->table_ = table;
  update_stmt->update_field_meta_ = field_meta;
  update_stmt->filter_stmt_ = filter_stmt;
  update_stmt->update_value_ = updates_sql.value;
  stmt = update_stmt;
  return RC::SUCCESS;
}
