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
// Created by Meiyi 
//

#include <cassert>
#include <mutex>
#include "sql/parser/parse.h"
#include "rc.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"

RC parse(char *st, Query *sqln);

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

ast *new_value_node(Value *value)
{
  ast *n = (ast *)malloc(sizeof(ast));
  n->nodetype = VALN;
  n->val = *value;
  n->l_brace = 0;
  n->r_brace = 0;
  return n;
}

ast *new_attr_node(RelAttr *attr)
{
  ast *n = (ast *)malloc(sizeof(ast));
  n->nodetype = ATTRN;
  n->attr = *attr;
  n->l_brace = 0;
  n->r_brace = 0;
  return n;
}

ast *new_aggr_node(Aggregate *aggr)
{
  ast *n = (ast *)malloc(sizeof(ast));
  n->nodetype = AGGRN;
  n->aggr = *aggr;
  n->l_brace = 0;
  n->r_brace = 0;
  return n;
}

ast *new_op_node(MathOp mathop, ast *l, ast *r)
{
  ast *n = (ast *)malloc(sizeof(ast));
  n->nodetype = OPN;
  n->op.left = l;
  n->op.right = r;
  n->op.mathop = mathop;
  n->l_brace = 0;
  n->r_brace = 0;
  return n;
}

void node_destroy(ast *n)
{
  if (n == nullptr) {
    return;
  }
  switch (n->nodetype) {
    case OPN:
      node_destroy(n->op.left);
      node_destroy(n->op.right);
      break;
    case VALN:
      value_destroy(&n->val);
      break;
    case ATTRN:
      relation_attr_destroy(&n->attr);
      break;
    case AGGRN:
      aggregate_destroy(&n->aggr);
      break;
    default:
      assert(0);
  }
}

void condition_init(Condition *condition, CompOp comp, ast *l, ast *r)
{
  condition->comp = comp;
  condition->left_ast = l;
  condition->right_ast = r;
}

void condition_destroy(Condition *condition)
{
  assert(condition->left_ast && condition->right_ast);
  node_destroy(condition->left_ast);
  node_destroy(condition->right_ast);
  condition->left_ast = NULL;
  condition->right_ast = NULL;
}

void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name)
{
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
}

void relation_attr_destroy(RelAttr *relation_attr)
{
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
}

void value_init_integer(Value *value, int v)
{
  value->type = INTS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_float(Value *value, float v)
{
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_string(Value *value, const char *v)
{
  value->type = CHARS;
  value->data = strdup(v);
}
void value_init_date(Value *value, int32_t v)
{
  value->type = DATES;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_destroy(Value *value)
{
  value->type = UNDEFINED;
  free(value->data);
  value->data = nullptr;
}


void join_init(Join *join, const char *join_table, Condition conditions[], size_t condition_num) {
  for(size_t i = 0; i < condition_num; i++) {
    join->conditions[i] = conditions[i];
  }
  join->condition_num = condition_num;
  join->join_table_name = strdup(join_table);
}

void join_destroy(Join *join) {
  for(size_t i = 0; i < join->condition_num; i++) {
    condition_destroy(&(join->conditions[i]));
  }
  free(join->join_table_name);
  join->join_table_name = nullptr;
}

void aggregate_init(Aggregate *aggr, AggrType aggr_type, int is_attr, RelAttr *attr, Value *value)
{
  aggr->aggr_type = aggr_type;
  aggr->is_attr = is_attr;
  if (is_attr) {
    aggr->attr = *attr;
  } else {
    aggr->value = *value;
  }
}

void aggregate_destroy(Aggregate *aggr)
{
  if (aggr->is_attr) {
    relation_attr_destroy(&aggr->attr);
  } else {
    value_destroy(&aggr->value);
  }
}

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length)
{
  attr_info->name = strdup(name);
  attr_info->type = type;
  attr_info->length = length;
}
void attr_info_destroy(AttrInfo *attr_info)
{
  free(attr_info->name);
  attr_info->name = nullptr;
}

void selects_init(Selects *selects, ...);

void select_append_exprs(Selects *selects, ast* exprs[], size_t expr_num)
{
  assert(expr_num <= MAX_NUM);
  for (size_t i = 0; i < expr_num; i++) {
    selects->exprs[i] = exprs[i];
  }
  selects->expr_num = expr_num;
}

void selects_append_relation(Selects *selects, const char *relation_name)
{
  selects->relations[selects->relation_num++] = strdup(relation_name);
}

void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(selects->conditions) / sizeof(selects->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    selects->conditions[i] = conditions[i];
  }
  selects->condition_num = condition_num;
}

void select_append_joins(Selects *selects, Join joins[], size_t join_num)
{
  assert(join_num < sizeof(selects->joins) / sizeof(selects->joins[0]));
  for (size_t i = 0; i < join_num; i++) {
    selects->joins[i] = joins[i];
  }
  selects->join_num = join_num;
}

void selects_destroy(Selects *selects)
{
  for (size_t i = 0; i < selects->relation_num; i++) {
    free(selects->relations[i]);
    selects->relations[i] = NULL;
  }
  selects->relation_num = 0;

  for (size_t i = 0; i < selects->condition_num; i++) {
    condition_destroy(&selects->conditions[i]);
  }
  selects->condition_num = 0;

  for (size_t i = 0; i < selects->join_num; i++) {
    join_destroy(&selects->joins[i]);
  }
  selects->join_num = 0;

  for (size_t i = 0; i < selects->expr_num; i++) {
    node_destroy(selects->exprs[i]);
  }
}

void inserts_init(Inserts *inserts, const char *relation_name)
{
  inserts->relation_name = strdup(relation_name);
}
void insert_append_exprs(Inserts *inserts, ast* exprs[], size_t expr_num)
{
  assert(expr_num <= MAX_NUM);

  for (size_t i = 0; i < expr_num; i++) {
    inserts->pairs[inserts->pair_num].exprs[i] = exprs[i];
  }
  inserts->pairs[inserts->pair_num].expr_num = expr_num;
  inserts->pair_num++;
}
void inserts_destroy(Inserts *inserts)
{
  free(inserts->relation_name);
  inserts->relation_name = nullptr;

  for (size_t i = 0; i < inserts->pair_num; i++) {
    for (size_t j = 0; j < inserts->pairs[i].expr_num; j++) {
      node_destroy(inserts->pairs[i].exprs[j]);
    }
    inserts->pairs[i].expr_num = 0;
  }
  inserts->pair_num = 0;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name)
{
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(deletes->conditions) / sizeof(deletes->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    deletes->conditions[i] = conditions[i];
  }
  deletes->condition_num = condition_num;
}
void deletes_destroy(Deletes *deletes)
{
  for (size_t i = 0; i < deletes->condition_num; i++) {
    condition_destroy(&deletes->conditions[i]);
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, ast *expr,
    Condition conditions[], size_t condition_num)
{
  updates->relation_name = strdup(relation_name);
  updates->attribute_name = strdup(attribute_name);
  updates->expr = expr;

  assert(condition_num <= sizeof(updates->conditions) / sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}

void updates_destroy(Updates *updates)
{
  free(updates->relation_name);
  free(updates->attribute_name);
  updates->relation_name = nullptr;
  updates->attribute_name = nullptr;

  node_destroy(updates->expr);

  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
}

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info)
{
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}

void create_table_init_name(CreateTable *create_table, const char *relation_name)
{
  create_table->relation_name = strdup(relation_name);
}

void create_table_destroy(CreateTable *create_table)
{
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name)
{
  drop_table->relation_name = strdup(relation_name);
}

void drop_table_destroy(DropTable *drop_table)
{
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

void create_index_init(
    CreateIndex *create_index, const char *index_name, const char *relation_name, const char *attr_name)
{
  create_index->index_name = strdup(index_name);
  create_index->relation_name = strdup(relation_name);
  create_index->attribute_name = strdup(attr_name);
}

void create_index_destroy(CreateIndex *create_index)
{
  free(create_index->index_name);
  free(create_index->relation_name);
  free(create_index->attribute_name);

  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;
  create_index->attribute_name = nullptr;
}

void show_index_init(ShowIndex *show_index, const char *relation_name) {
  show_index->relation_name = strdup(relation_name);
}

void show_index_destroy(ShowIndex *show_index) {
  free(show_index->relation_name);

  show_index->relation_name = nullptr;
}

void drop_index_init(DropIndex *drop_index, const char *index_name)
{
  drop_index->index_name = strdup(index_name);
}

void drop_index_destroy(DropIndex *drop_index)
{
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void desc_table_init(DescTable *desc_table, const char *relation_name)
{
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table)
{
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name)
{
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void load_data_destroy(LoadData *load_data)
{
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

void query_init(Query *query)
{
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create()
{
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

void query_reset(Query *query)
{
  switch (query->flag) {
    case SCF_SELECT: {
      selects_destroy(&query->sstr.selection);
    } break;
    case SCF_INSERT: {
      inserts_destroy(&query->sstr.insertion);
    } break;
    case SCF_DELETE: {
      deletes_destroy(&query->sstr.deletion);
    } break;
    case SCF_UPDATE: {
      updates_destroy(&query->sstr.update);
    } break;
    case SCF_CREATE_TABLE: {
      create_table_destroy(&query->sstr.create_table);
    } break;
    case SCF_DROP_TABLE: {
      drop_table_destroy(&query->sstr.drop_table);
    } break;
    case SCF_CREATE_INDEX: {
      create_index_destroy(&query->sstr.create_index);
    } break;
    case SCF_DROP_INDEX: {
      drop_index_destroy(&query->sstr.drop_index);
    } break;
    case SCF_SHOW_INDEX: {
      show_index_destroy(&query->sstr.show_index);
    }
    case SCF_SYNC: {

    } break;
    case SCF_SHOW_TABLES:
      break;

    case SCF_DESC_TABLE: {
      desc_table_destroy(&query->sstr.desc_table);
    } break;

    case SCF_LOAD_DATA: {
      load_data_destroy(&query->sstr.load_data);
    } break;
    case SCF_CLOG_SYNC:
    case SCF_BEGIN:
    case SCF_COMMIT:
    case SCF_ROLLBACK:
    case SCF_HELP:
    case SCF_EXIT:
    case SCF_ERROR:
      break;
  }
}

void query_destroy(Query *query)
{
  query_reset(query);
  free(query);
}
#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern "C" int sql_parse(const char *st, Query *sqls);

RC parse(const char *st, Query *sqln)
{
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}
