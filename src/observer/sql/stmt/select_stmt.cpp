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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

RC SelectStmt::create(Db *db, Selects &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  for (int i = select_sql.relation_num - 1; i >= 0; i--) {
    const char *table_name = select_sql.relations[i];
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // create join units
  std::vector<JoinUnit> join_units;
  for (size_t i = 0; i < select_sql.join_condition_num; i++) {
    JoinCondition &join_condition = select_sql.join_conditions[i];
    JoinUnit join_unit;

    const char *join_table_name = join_condition.join_table_name;
    const char *left_table_name = join_condition.left_attr.relation_name;
    const char *left_field_name = join_condition.left_attr.attribute_name;
    const char *right_table_name = join_condition.right_attr.relation_name;
    const char *right_field_name = join_condition.right_attr.attribute_name;

    if (strcmp(join_table_name, left_table_name) != 0 && strcmp(join_table_name, right_table_name) != 0) {
      LOG_WARN("condition table name does not match on table name");
      return RC::JOIN_TABLE_MISMATCH;
    }

    Table *join_table = db->find_table(join_table_name);
    if (nullptr == join_table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), join_table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    join_unit.join_table = join_table;

    Table *left_table = db->find_table(left_table_name);
    if (nullptr == left_table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), left_table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    Table *right_table = db->find_table(right_table_name);
    if (nullptr == right_table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), right_table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    const FieldMeta *left_field_meta = left_table->table_meta().field(left_field_name);
    if (nullptr == left_field_meta) {
      LOG_WARN("no such field. field=%s.%s.%s", db->name(), left_table->name(), left_field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    const FieldMeta *right_field_meta = right_table->table_meta().field(right_field_name);
    if (nullptr == right_field_meta) {
      LOG_WARN("no such field. field=%s.%s.%s", db->name(), right_table->name(), right_field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }

    if (strcmp(join_table_name, right_table_name) == 0) {
      join_unit.left = FieldExpr(left_table, left_field_meta);
      join_unit.right = FieldExpr(right_table, right_field_meta);
    } else {
      join_unit.left = FieldExpr(right_table, right_field_meta);
      join_unit.right = FieldExpr(left_table, left_field_meta);
    }

    join_units.push_back(join_unit);
  }

  // add extra tables
  for (JoinUnit &unit : join_units) {
    tables.push_back(unit.join_table);
    table_map.insert({unit.join_table->name(), unit.join_table});
  }

  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  for (int i = select_sql.attr_num - 1; i >= 0; i--) {
    const RelAttr &relation_attr = select_sql.attributes[i];

    if (common::is_blank(relation_attr.relation_name) && 0 == strcmp(relation_attr.attribute_name, "*")) {
      // *
      for (Table *table : tables) {
        wildcard_fields(table, query_fields);
      }

    } else if (!common::is_blank(relation_attr.relation_name)) {  // TODO
      // something.something
      const char *table_name = relation_attr.relation_name;
      const char *field_name = relation_attr.attribute_name;

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          // *.id
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        // *.*
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          // tbl.*
          wildcard_fields(table, query_fields);
        } else {
          // tbl.field
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta));
        }
      }
    } else {
      // no relation, only attributes
      // field
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name);
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta));
    }
  }
  // for (Field field : query_fields) {
  //   printf("%s: %s\n", field.table_name(), field.field_name());
  // }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc =
      FilterStmt::create(db, default_table, &table_map, select_sql.conditions, select_sql.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // for (Table *t : tables) {
  //   printf("table name: %s\n", t->name());
  // }
  // for (const JoinUnit &unit : join_units) {
  //   printf("join %s with %s.%s %s.%s\n",
  //       unit.join_table->name(),
  //       unit.left.table_name(),
  //       unit.left.field_name(),
  //       unit.right.table_name(),
  //       unit.right.field_name());
  // }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->join_units_.swap(join_units);
  select_stmt->filter_stmt_ = filter_stmt;
  stmt = select_stmt;
  return RC::SUCCESS;
}
