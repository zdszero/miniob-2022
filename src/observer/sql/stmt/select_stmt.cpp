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
#include <sstream>

void print_expr(Expression *expr)
{
  if (expr->type() == ExprType::FIELD) {
    FieldExpr *field_expr = static_cast<FieldExpr *>(expr);
    printf("field: %s:%s\n", field_expr->field().table_name(), field_expr->field_name());
  } else if (expr->type() == ExprType::VALUE) {
    std::stringstream ss;
    ValueExpr *val_expr = static_cast<ValueExpr *>(expr);
    TupleCell cell;
    val_expr->get_tuple_cell(cell);
    cell.to_string(ss);
    std::cout << ss.str() << std::endl;
  }
}

inline bool is_star(const char *name)
{
  return std::strcmp("*", name) == 0;
}

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

static RC collect_tables(Db *db, Selects &select_sql, Tables &tables, TableMap &table_map)
{
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
  return RC::SUCCESS;
}

static RC collect_join_stmts(Db *db, Selects &select_sql, Table *default_table, std::vector<JoinStmt> &join_stmts)
{
  TableMap join_table_map;
  if (default_table != nullptr) {
    join_table_map.insert({default_table->name(), default_table});
  }

  for (size_t i = 0; i < select_sql.join_num; i++) {
    Join &join = select_sql.joins[i];
    JoinStmt join_stmt;
    Table *join_table = db->find_table(join.join_table_name);
    if (join_table == nullptr) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }
    join_table_map.insert({join_table->name(), join_table});
    join_stmt.join_table = join_table;

    FilterStmt *join_filter;
    RC rc = FilterStmt::create(db, default_table, &join_table_map, join.conditions, join.condition_num, join_filter);
    if (rc != RC::SUCCESS) {
      LOG_WARN("fail to create filter for join on table %s\n", join.join_table_name);
      return rc;
    }
    join_stmt.filter_stmt = join_filter;

    join_stmts.push_back(join_stmt);
  }
  return RC::SUCCESS;
}

static RC collect_query_fields(
    Db *db, Selects &select_sql, const Tables &tables, const TableMap &table_map, std::vector<Field> &query_fields)
{
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
  return RC::SUCCESS;
}

static RC collect_aggr_fields(
    Db *db, Selects &select_sql, const Tables &tables, const TableMap &table_map, std::vector<AggrField> &aggr_fields)
{
  if (select_sql.aggr_num > 0 && select_sql.attr_num > 0) {
    LOG_WARN("cannot select aggregation with attribute together\n");
    return RC::SQL_SYNTAX;
  }
  for (size_t i = 0; i < select_sql.aggr_num; i++) {
    Aggregate &aggr = select_sql.aggrs[i];
    if (aggr.is_attr) {
      const char *table_name = aggr.attr.relation_name;
      const char *field_name = aggr.attr.attribute_name;
      if (is_star(field_name) && aggr.aggr_type != AggrType::COUNTS) {
        LOG_WARN("aggregate * with invalid aggregate function\n");
        return RC::SQL_SYNTAX;
      }
      Table *table = nullptr;
      const FieldMeta *field_meta = nullptr;
      if (!common::is_blank(table_name)) {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        table = iter->second;
      } else {
        if (tables.size() != 1) {
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        table = tables[0];
      }
      if (!is_star(field_name)) {
        field_meta = table->table_meta().field(field_name);
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
      }
      aggr_fields.push_back(AggrField(aggr.aggr_type, table, field_meta));
    } else {
      LOG_ERROR("aggregate on value is not implemented yet\n");
      return RC::UNIMPLENMENT;
    }
  }
  return RC::SUCCESS;
}

RC SelectStmt::create(Db *db, Selects &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }
  printf("------------------\n");

  // collect tables in `from` statement
  Tables tables;
  TableMap table_map;
  RC rc = collect_tables(db, select_sql, tables, table_map);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // setting default table
  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create join stmts
  if (select_sql.join_num > 0 && tables.size() > 1) {
    LOG_ERROR("join with more than one select table is not implemented yet");
    return RC::UNIMPLENMENT;
  }

  std::vector<JoinStmt> join_stmts;
  rc = collect_join_stmts(db, select_sql, default_table, join_stmts);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // add join tables into tables for projection
  for (JoinStmt &join : join_stmts) {
    tables.push_back(join.join_table);
    table_map.insert({join.join_table->name(), join.join_table});
  }

  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  rc = collect_query_fields(db, select_sql, tables, table_map, query_fields);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // collect aggreagtion fields
  std::vector<AggrField> aggr_fields;
  rc = collect_aggr_fields(db, select_sql, tables, table_map, aggr_fields);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  rc = FilterStmt::create(db, default_table, &table_map, select_sql.conditions, select_sql.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  for (Table *t : tables) {
    printf("table name: %s\n", t->name());
  }
  for (const JoinStmt &join : join_stmts) {
    printf("join on table: %s\n", join.join_table->name());
    for (FilterUnit *unit : join.filter_stmt->filter_units()) {
      printf("comp: %d\n", unit->comp());
      print_expr(unit->left());
      print_expr(unit->right());
    }
  }
  for (const AggrField &aggr : aggr_fields) {
    printf("%s:%s with %d\n",
        aggr.field().table_name(),
        aggr.is_wildcard() ? "*" : aggr.field().field_name(),
        aggr.aggr_type());
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->join_stmts_.swap(join_stmts);
  select_stmt->filter_stmt_ = filter_stmt;
  stmt = select_stmt;
  return RC::SUCCESS;
}
