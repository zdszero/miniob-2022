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
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
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
  for (Expression * order_expr : order_exprs_) {
    delete order_expr;
  }
  for (Expression * group_by : group_bys_) {
    delete group_by;
  }
}

void SelectStmt::Print() const
{
  printf("------------------\n");
  auto print_units = [](const std::vector<FilterUnit *> &units) {
    for (FilterUnit *unit : units) {
      if (unit->condition_type() == ConditionType::COND_COMPARE) {
        printf("comp: %s\n", comp_to_string(unit->comp()).c_str());
        print_expr(unit->left());
        print_expr(unit->right());
      } else if (unit->condition_type() == ConditionType::COND_EXISTS) {
        printf("exists\n");
      } else {
        print_expr(unit->left());
        printf("in subquery\n");
      }
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
  std::vector<ast *> attr_nodes;
  std::vector<ast *> aggr_nodes;
  for (size_t i = 0; i < select_sql.group_by_length; i++) {
    ast *group_by = select_sql.group_bys[i];
    if (group_by->nodetype != NodeType::ATTRN) {
      LOG_WARN("using other expressions other than attributes in group by");
      return RC::SQL_SYNTAX;
    }
  }
  for (size_t i = 0; i < select_sql.expr_num; i++) {
    size_t cur_attr_cnt = 0;
    size_t cur_aggr_cnt = 0;
    ast *t = select_sql.exprs[i];
    RC rc = check_leaf_node(t, ctx, cur_attr_cnt, cur_aggr_cnt);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    if (cur_attr_cnt > 0) {
      attr_nodes.push_back(select_sql.exprs[i]);
    }
    if (cur_aggr_cnt > 0) {
      aggr_nodes.push_back(select_sql.exprs[i]);
    }
    attr_cnt += cur_attr_cnt;
    aggr_cnt += cur_aggr_cnt;
  }
  if (aggr_cnt > 0 && attr_cnt > 0) {
    // check if all attrbutes are in group by
    for (ast *t : attr_nodes) {
      bool found = false;
      for (size_t i = 0; i < select_sql.group_by_length; i++) {
        ast *group_by = select_sql.group_bys[i];
        if (strcmp(group_by->attr.attribute_name, t->attr.attribute_name) == 0) {
          found = true;
          break;
        }
      }
      if (found == false) {
        LOG_WARN("attributes (not in group by) cannot be selected with aggregate together");
        return RC::SQL_SYNTAX;
      }
    }
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
    // std::cout << ast_to_string(t) << std::endl;
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
    RC rc = FilterStmt::create(db, join_ctx, join.conditions, join.condition_num, join_filter);
    if (rc != RC::SUCCESS) {
      LOG_WARN("fail to create filter for join on table %s\n", join.join_table_name);
      return rc;
    }
    join_stmt.filter_stmt = join_filter;

    join_stmts.push_back(join_stmt);
  }
  return RC::SUCCESS;
}

static RC check_only_attr(ast *t, ExprContext &ctx)
{
  size_t attr_cnt = 0;
  size_t aggr_cnt = 0;
  RC rc = check_leaf_node(t, ctx, attr_cnt, aggr_cnt);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  if (aggr_cnt > 0) {
    LOG_WARN("Cannot use aggregate in order by or group by");
    return RC::SQL_SYNTAX;
  }
  return RC::SUCCESS;
}

static RC check_having(Condition *condition)
{
  NodeType ltype = condition->left_ast->nodetype;
  NodeType rtype = condition->right_ast->nodetype;
  if (ltype != NodeType::AGGRN && rtype != NodeType::AGGRN) {
    LOG_WARN("having must have aggregate");
    return RC::SQL_SYNTAX;
  }
  return RC::SUCCESS;
}

RC SelectStmt::create_with_context(Db *db, Selects &select_sql, Stmt *&stmt, ExprContext &select_ctx)
{
  size_t outer_table_size = select_ctx.GetTableSize();
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement and set default table
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
  if (aggr_cnt > 0) {
    select_attributes = false;
  } else {
    assert(attr_cnt > 0);
    select_attributes = true;
  }

  // collect exprs
  std::vector<Expression *> exprs;
  collect_exprs(select_sql, select_ctx, exprs);

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  rc = FilterStmt::create(db, select_ctx, select_sql.conditions, select_sql.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // collect order by info
  for (size_t i = 0; i < select_sql.order_attr_length; i++) {
    rc = check_only_attr(select_sql.order_attr[i], select_ctx);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  std::vector<Expression *> order_exprs;
  std::vector<OrderPolicy> order_policies;
  for (size_t i = 0; i < select_sql.order_attr_length; i++) {
    order_exprs.push_back(ExprFactory::create(select_sql.order_attr[i], select_ctx));
    order_policies.push_back(select_sql.order_policy[i]);
  }

  // collect group by info
  for (size_t i = 0; i < select_sql.group_by_length; i++) {
    rc = check_only_attr(select_sql.group_bys[i], select_ctx);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  std::vector<Expression *> group_bys;
  for (size_t i = 0; i < select_sql.group_by_length; i++) {
    group_bys.push_back(ExprFactory::create(select_sql.group_bys[i], select_ctx));
  }

  // having
  FilterUnit *having = nullptr;
  if (select_sql.is_having) {
    RC rc = check_having(&select_sql.having);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    rc = FilterStmt::create_filter_unit(db, select_ctx, select_sql.having, having, true);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  // don't adding outer table into correlated subquery
  std::vector<Table *> tables;
  for (size_t i = outer_table_size; i < select_ctx.GetTableSize(); i++) {
    tables.push_back(select_ctx.GetTables()[i]);
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->tables_.swap(tables);
  select_stmt->join_stmts_.swap(join_stmts);
  select_stmt->exprs_.swap(exprs);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->select_attributes_ = select_attributes;
  select_stmt->order_exprs_ = order_exprs;
  select_stmt->order_policies_ = order_policies;
  select_stmt->group_bys_ = group_bys;
  select_stmt->having_ = having;
  stmt = select_stmt;

  select_stmt->Print();
  return RC::SUCCESS;
}

RC SelectStmt::create(Db *db, Selects &select_sql, Stmt *&stmt)
{
  ExprContext select_ctx;
  return create_with_context(db, select_sql, stmt, select_ctx);
}
