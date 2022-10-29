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

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "util/date.h"
#include "util/util.h"
#include "util/ast_util.h"
#include <cassert>

RC InsertStmt::create(Db *db, Inserts &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name;
  if (nullptr == db || nullptr == table_name || inserts.pair_num <= 0) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, pair_num=%d", 
             db, table_name, inserts.pair_num);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  for (size_t i = 0; i < inserts.pair_num; i++) {
    // check the fields number
    const int expr_num = inserts.pairs[i].expr_num;
    const TableMeta &table_meta = table->table_meta();
    const int field_num = table_meta.field_num() - table_meta.sys_field_num();
    if (field_num != expr_num) {
      LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", expr_num, field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }
    for (size_t j = 0; j < inserts.pairs[i].expr_num; j++) {
      // check if expression is valid
      if (!evaluate(inserts.pairs[i].exprs[j])) {
        LOG_WARN("cannot evalute expression in insert stmt");
        return RC::SQL_SYNTAX;
      }
    }
  }

  // do typecast
  for (size_t i = 0; i < inserts.pair_num; i++) {
    const int expr_num = inserts.pairs[i].expr_num;
    const TableMeta &table_meta = table->table_meta();
    // check fields type
    const int sys_field_num = table_meta.sys_field_num();
    for (int j = 0; j < expr_num; j++) {
      const FieldMeta *field_meta = table_meta.field(j + sys_field_num);
      const AttrType field_type = field_meta->type();
      bool nullable = field_meta->nullable();
      Value &value = inserts.pairs[i].exprs[j]->val;
      assert(value.type != DATES);
      assert(field_type != UNDEFINED);
      RC rc;
      if ((rc = try_to_cast_value(field_type, nullable, value)) != RC::SUCCESS) {
        return rc;
      }
    }
  }

  size_t expr_num = inserts.pairs[0].expr_num;
  // create values
  std::vector<std::vector<Value>> value_pairs;
  value_pairs.resize(inserts.pair_num, std::vector<Value>{});
  for (size_t i = 0; i < inserts.pair_num; i++) {
    value_pairs[i].reserve(expr_num);
    for (size_t j = 0; j < expr_num; j++) {
      value_pairs[i].push_back(inserts.pairs[i].exprs[j]->val);
    }
  }

  // everything alright
  stmt = new InsertStmt(table, value_pairs, expr_num);
  return RC::SUCCESS;
}
