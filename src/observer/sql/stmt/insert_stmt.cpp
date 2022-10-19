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
#include <cassert>

InsertStmt::InsertStmt(Table *table, const Value *values, int value_amount)
  : table_ (table), values_(values), value_amount_(value_amount)
{}

RC InsertStmt::create(Db *db, Inserts &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name;
  if (nullptr == db || nullptr == table_name || inserts.value_num <= 0) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d", 
             db, table_name, inserts.value_num);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  Value *values = inserts.values;
  const int value_num = inserts.value_num;
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.sys_field_num();
  if (field_num != value_num) {
    LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
    return RC::SCHEMA_FIELD_MISSING;
  }

  // check fields type
  const int sys_field_num = table_meta.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i + sys_field_num);
    const AttrType field_type = field_meta->type();
    Value &value = values[i];
    assert(value.type != DATES);
    assert(field_type != UNDEFINED);
    if (field_type != value.type) {
      switch (field_type) {
        case INTS:
          if (value.type == FLOATS) {
            int int_val = static_cast<int>(*(float *)value.data+0.5);
            value_destroy(&value);
            value_init_integer(&value, int_val);
          } else {
            assert(value.type == CHARS);
            int int_val = std::atoi((char *)value.data);
            value_destroy(&value);
            value_init_integer(&value, int_val);
          }
          break;
        case FLOATS:
          if (value.type == INTS) {
            float float_val = static_cast<float>(*(int *)value.data);
            value_destroy(&value);
            value_init_float(&value, float_val);
          } else {
            assert(value.type == CHARS);
            float float_val = std::atof((char *)value.data);
            value_destroy(&value);
            value_init_float(&value, float_val);
          }
          break;
        case CHARS:
          if (value.type == INTS) {
            std::string s = std::to_string(*(int *)value.data);
            value_destroy(&value);
            value_init_string(&value, s.c_str());
          } else {
            assert(value.type == FLOATS);
            std::string s = double2string(*(float *)value.data);
            value_destroy(&value);
            value_init_string(&value, s.c_str());
          }
          break;
        case DATES:
          if (value.type == CHARS) {
            int32_t date = -1;
            RC rc = string_to_date((char *)value.data, date);
            if (rc != RC::SUCCESS) {
              LOG_WARN("invalid date format\n");
              return rc;
            }
            value_destroy(&value);
            value_init_date(&value, date);
          } else {
            LOG_WARN("field type is not compatible. table=%s, field=%s, field type=%d, value.type=%d", 
                     table_name, field_meta->name(), field_type, value.type);
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          break;
        default:
          LOG_ERROR("unknown field type: %d\n", field_type);
          return RC::INTERNAL;
      }
    }
  }

  // everything alright
  stmt = new InsertStmt(table, values, value_num);
  return RC::SUCCESS;
}
