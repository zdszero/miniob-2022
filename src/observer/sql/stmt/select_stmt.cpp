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
#include "util/util.h"
#include "util/ast_util.h"
#include "util/check.h"

SelectStmt::~SelectStmt()
{
  for (Expression *expr : exprs_) {
    delete expr;
  }
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

void SelectStmt::Print() const
{
  auto print_units = [](const std::vector<FilterUnit *> &units) {
    for (FilterUnit *unit : units) {
      printf("comp: %s\n", comp_to_string(unit->comp()).c_str());
      print_expr(unit->left());
      print_expr(unit->right());
    }
  };
  printf("--- table info ---\n");
  for (Table *t : tables_) {
    printf("name: %s\n", t->name());
  }
  printf("--- join info  ---\n");
  for (const JoinStmt &join : join_stmts_) {
    printf("join on table: %s\n", join.join_table->name());
    print_units(join.filter_stmt->filter_units());
  }
  if (filter_stmt_ != nullptr) {
    printf("--- cond info  ---\n");
    print_units(filter_stmt_->filter_units());
  }
  printf("--- exprs info ---\n");
  for (Expression *expr : exprs_) {
    print_expr(expr);
  }
}

static RC check_selects(Selects &select_sql, size_t &attr_cnt, size_t &aggr_cnt, ExprContext &ctx)
{
  attr_cnt = 0;
  aggr_cnt = 0;
  for (size_t i = 0; i < select_sql.expr_num; i++) {
    ast *t = select_sql.exprs[i];
    RC rc = check_leaf_node(t, ctx, attr_cnt, aggr_cnt);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  if (aggr_cnt > 0 && attr_cnt > 0) {
    LOG_WARN("attribute and aggregate cannot be selected together\n");
    return RC::SQL_SYNTAX;
  }
  return RC::SUCCESS;
}

static void wildcard_fields(Table *table, std::vector<Expression *> &exprs)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    exprs.push_back(new FieldExpr(table, table_meta.field(i)));
  }
}

static void collect_attr_expr(ast *t, const ExprContext &ctx, std::vector<Expression *> &exprs)
{
  assert(t->nodetype == NodeType::ATTRN);
  const RelAttr &attr = t->attr;
  if (strcmp(attr.attribute_name, "*") == 0) {
    if (common::is_blank(attr.relation_name) || strcmp(attr.relation_name, "*") == 0){
      for (Table *t : ctx.GetTables()) {
        wildcard_fields(t, exprs);
      }
    } else {
      Table *t = ctx.GetTable(attr);
      wildcard_fields(t, exprs);
    }
  } else {
    exprs.push_back(ExprFactory::create(t, ctx));
  }
}

static void collect_exprs(Selects &select_sql, const ExprContext &ctx, std::vector<Expression *> &exprs)
{
  for (size_t i = 0; i < select_sql.expr_num; i++) {
    ast *t = select_sql.exprs[i];
    std::cout << ast_to_string(t) << std::endl;
    assert(t->nodetype != NodeType::UNDEFINEDN);
    if (t->nodetype == NodeType::ATTRN) {
      collect_attr_expr(t, ctx, exprs);
    } else {
      exprs.push_back(ExprFactory::create(t, ctx));
    }
  }
}

static RC collect_tables(Db *db, Selects &select_sql, ExprContext &ctx)
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

    ctx.AddTable(table);
  }
  return RC::SUCCESS;
}

static RC collect_join_stmts(Db *db, Selects &select_sql, Table *default_table, std::vector<JoinStmt> &join_stmts)
{
  ExprContext join_ctx(default_table);

  for (size_t i = 0; i < select_sql.join_num; i++) {
    Join &join = select_sql.joins[i];
    JoinStmt join_stmt;
    Table *join_table = db->find_table(join.join_table_name);
    if (join_table == nullptr) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }
    join_ctx.AddTable(join_table);
    join_stmt.join_table = join_table;

    FilterStmt *join_filter;
    // RC rc = FilterStmt::create(db, default_table, &join_table_map, join.conditions, join.condition_num, join_filter);
    RC rc = FilterStmt::create(join_ctx, join.conditions, join.condition_num, join_filter);
    if (rc != RC::SUCCESS) {
      LOG_WARN("fail to create filter for join on table %s\n", join.join_table_name);
      return rc;
    }
    join_stmt.filter_stmt = join_filter;

    join_stmts.push_back(join_stmt);
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

  // collect tables in `from` statement and set default table
  ExprContext select_ctx;
  RC rc = collect_tables(db, select_sql, select_ctx);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  assert(select_ctx.GetTableSize() > 0);

  // check all join conditions, create join stmts
  if (select_sql.join_num > 0 && select_ctx.GetTableSize() > 1) {
    LOG_ERROR("join with more than one select table is not implemented yet");
    return RC::UNIMPLENMENT;
  }
  std::vector<JoinStmt> join_stmts;
  rc = collect_join_stmts(db, select_sql, select_ctx.GetDefaultTable(), join_stmts);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // add join tables into tables for projection
  for (JoinStmt &join : join_stmts) {
    select_ctx.AddTable(join.join_table);
  }

  // check expressions and build context
  size_t attr_cnt = 0;
  size_t aggr_cnt = 0;
  rc = check_selects(select_sql, attr_cnt, aggr_cnt, select_ctx);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  bool select_attributes;
  if (attr_cnt > 0) {
    select_attributes = true;
  }
  if (aggr_cnt > 0) {
    select_attributes = false;
  }

  // collect exprs
  std::vector<Expression *> exprs;
  collect_exprs(select_sql, select_ctx, exprs);

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  rc = FilterStmt::create(select_ctx, select_sql.conditions, select_sql.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  auto tables = select_ctx.GetTables();
  select_stmt->tables_.swap(tables);
  select_stmt->join_stmts_.swap(join_stmts);
  select_stmt->exprs_.swap(exprs);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->select_attributes_ = select_attributes;
  stmt = select_stmt;

  select_stmt->Print();
  return RC::SUCCESS;
}
