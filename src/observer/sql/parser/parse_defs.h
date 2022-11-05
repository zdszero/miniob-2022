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

#ifndef __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
#define __OBSERVER_SQL_PARSER_PARSE_DEFS_H__

#include <stdint.h>
#include <stddef.h>

#define MAX_NUM 20
#define MAX_REL_NAME 20
#define MAX_ATTR_NAME 20
#define MAX_ERROR_MESSAGE 20
#define MAX_DATA 50

//属性结构体
typedef struct {
  char *relation_name;   // relation name (may be NULL) 表名
  char *attribute_name;  // attribute name              属性名
} RelAttr;

typedef enum {
  EQUAL_TO,     //"="     0
  LESS_EQUAL,   //"<="    1
  NOT_EQUAL,    //"<>"    2
  LESS_THAN,    //"<"     3
  GREAT_EQUAL,  //">="    4
  GREAT_THAN,   //">"     5
  STR_LIKE,
  STR_NOT_LIKE,
  IS,
  IS_NOT,
  EXISTS,
  NOT_EXISTS,
  IN,
  NOT_IN,
  NO_OP,
} CompOp;

typedef enum { MATH_ADD, MATH_SUB, MATH_MUL, MATH_DIV } MathOp;

//属性值类型
typedef enum {
  UNDEFINED,
  CHARS,
  TEXTS,
  INTS,
  DATES,
  FLOATS,
  NULLS,
} AttrType;

typedef enum {
  UNDEFINEDAGG,
  MAXS,
  MINS,
  AVGS,
  SUMS,
  COUNTS,
} AggrType;

typedef enum {
  NO_ORDER,
  ORDER_ASC,
  ORDER_DESC,
} OrderPolicy;

typedef enum {
  UNDEFINEDN,
  OPN,
  VALN,
  ATTRN,
  AGGRN,
  FUNCN,
} NodeType;

typedef enum {
  UNDEFINEDT,
  ATTRT,
  VALUET,
  NODET,
} FieldType;

typedef enum {
  LENGTHF,
  ROUNDF,
  DATE_FORMATF,
} FuncType;

//属性值
typedef struct _Value {
  AttrType type;  // type of value
  void *data;     // value
} Value;

typedef struct _Aggregate {
  AggrType aggr_type;
  int is_attr;
  Value value;
  RelAttr attr;
} Aggregate;

typedef struct ast {
  NodeType nodetype;
  union {
    RelAttr attr;
    Value val;
    Aggregate aggr;
    struct {
      MathOp mathop;
      struct ast *left;
      struct ast *right;
    } op;
    struct {
      FuncType functype;
      struct ast *left;
      struct ast *right;
    } func;
  };
  int l_brace;
  int r_brace;
} ast;

struct _Selects;

typedef enum {
  COND_COMPARE,
  COND_EXISTS,
  COND_IN,
} ConditionType;

typedef enum {
  COND_AND,
  COND_OR,
  COND_END,
} ConditionOp;

typedef struct _Condition {
  ConditionType condition_type;
  ConditionOp condop;
  CompOp comp;
  ast *left_ast;
  ast *right_ast;
  int left_is_select;
  int right_is_select;
  struct _Selects *left_select;
  struct _Selects *right_select;
  size_t expr_num;
  ast *exprs[MAX_NUM];
} Condition;

typedef struct _JoinConditon {
  char *join_table_name;
  size_t condition_num;
  Condition conditions[MAX_NUM];
} Join;

// struct of select
typedef struct _Selects {
  size_t relation_num;            // Length of relations in Fro clause
  char *relations[MAX_NUM];       // relations in From clause
  char *relation_alias[MAX_NUM];
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
  size_t join_num;
  Join joins[MAX_NUM];
  size_t expr_num;
  ast *exprs[MAX_NUM];
  char *expr_alias[MAX_NUM];
  size_t order_attr_length;
  ast *order_attr[MAX_NUM];
  OrderPolicy order_policy[MAX_NUM];
  ast *group_bys[MAX_NUM];
  size_t group_by_length;
  int is_having;
  Condition having;
} Selects;

typedef struct {
  size_t expr_num;      // Length of values
  ast *exprs[MAX_NUM];  // values to insert
} InsertPair;

// struct of insert
typedef struct {
  char *relation_name;  // Relation to insert into
  size_t pair_num;
  InsertPair pairs[MAX_NUM];
} Inserts;

// struct of delete
typedef struct {
  char *relation_name;            // Relation to delete from
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Deletes;

typedef struct {
  char *attribute_name;  // Attribute to update
  int is_select;
  struct _Selects *select;
  ast *expr;
} UpdatePair;

// struct of update
typedef struct {
  char *relation_name;   // Relation to update
  size_t condition_num;           // Length of conditions in Where clause
  size_t update_pair_num;
  UpdatePair update_pairs[MAX_NUM];
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Updates;

typedef struct {
  char *name;     // Attribute name
  AttrType type;  // Type of attribute
  size_t length;  // Length of attribute
  int nullable;
} AttrInfo;

// struct of craete_table
typedef struct {
  char *relation_name;           // Relation name
  size_t attribute_count;        // Length of attribute
  AttrInfo attributes[MAX_NUM];  // attributes
} CreateTable;

// struct of drop_table
typedef struct {
  char *relation_name;  // Relation name
} DropTable;

// struct of create_index
typedef struct {
  char *index_name;     // Index name
  char *relation_name;  // Relation name
  int attribute_num;
  int unique;
  char *attribute_names[MAX_NUM];  // Attribute name
} CreateIndex;

typedef struct {
  char *relation_name;
} ShowIndex;

// struct of  drop_index
typedef struct {
  const char *index_name;  // Index name
} DropIndex;

typedef struct {
  const char *relation_name;
} DescTable;

typedef struct {
  const char *relation_name;
  const char *file_name;
} LoadData;

union Queries {
  Selects selection;
  Inserts insertion;
  Deletes deletion;
  Updates update;
  CreateTable create_table;
  DropTable drop_table;
  CreateIndex create_index;
  DropIndex drop_index;
  DescTable desc_table;
  LoadData load_data;
  ShowIndex show_index;
  char *errors;
};

// 修改yacc中相关数字编码为宏定义
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SHOW_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT
};
// struct of flag and sql_struct
typedef struct Query {
  enum SqlCommandFlag flag;
  union Queries sstr;
} Query;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

ast *new_value_node(Value *value);
ast *new_attr_node(RelAttr *attr);
ast *new_aggr_node(Aggregate *aggr);
ast *new_op_node(MathOp mathop, ast *l, ast *r);
ast *new_func_node(FuncType functype, ast *l, ast *r);
void node_destroy(ast *n);

void condition_init(Condition *condition, CompOp comp, int left_is_select, ast *l, Selects *left_select,
    int right_is_select, ast *r, Selects *right_select);
void condition_init_exists(Condition *condition, int exists, Selects *sub_select);
void condition_init_in(Condition *condition, int in, ast *expr, Selects *sub_select);
void condition_init_in_exprs(Condition *condition, int in, ast *in_attr, ast *expr[], int expr_num);
void condition_destroy(Condition *condition);

void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name);
void relation_attr_destroy(RelAttr *relation_attr);

void value_init_integer(Value *value, int v);
void value_init_float(Value *value, float v);
void value_init_string(Value *value, const char *v);
void value_init_date(Value *value, int32_t v);
void value_init_null(Value *value);
void value_destroy(Value *value);

void join_init(Join *join, const char *join_table, Condition conditions[], size_t condition_num);
void join_set_condition_ops(Join *join, ConditionOp condops[], size_t op_num);
void join_destroy(Join *join);

void aggregate_init(Aggregate *aggr, AggrType aggr_type, int is_attr, RelAttr *attr, Value *value);
void aggregate_destroy(Aggregate *aggr);

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, int nullable);
void attr_info_destroy(AttrInfo *attr_info);

void selects_init(Selects *selects, ...);
void selects_append_exprs(Selects *selects, ast *exprs[], char *expr_alias[], size_t expr_num);
void selects_append_relation(Selects *selects, const char *relation_name, char *relation_alias);
void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num);
void selects_set_condition_ops(Selects *selects, ConditionOp condops[], size_t op_num);
void selects_append_joins(Selects *selects, Join joins[], size_t join_num);
void selects_destroy(Selects *selects);
void selects_set_order_info(Selects *selects, OrderPolicy policies[], ast *order_attr[], size_t order_attr_num);
void selects_set_group_by(Selects *selects, ast *group_bys[], size_t group_by_num);
void selects_set_having(Selects *selects, Condition *condition);

void insert_append_exprs(Inserts *inserts, ast *exprs[], size_t expr_num);
void inserts_init(Inserts *inserts, const char *relation_name);
void inserts_destroy(Inserts *inserts);

void deletes_init_relation(Deletes *deletes, const char *relation_name);
void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num);
void deletes_set_condition_ops(Deletes *deletes, ConditionOp condops[], size_t op_num);
void deletes_destroy(Deletes *deletes);

void update_pair_init(UpdatePair *update_pair, const char *attribute_name, int is_select, Selects *select, ast *expr);
void update_pair_destroy(UpdatePair *update_pair);
void updates_init(Updates *updates, const char *relation_name, Condition conditions[], size_t condition_num);
void updates_set_condition_ops(Updates *updates, ConditionOp condops[], size_t op_num);
void update_append_pair(Updates *updates, UpdatePair *update_pair);
void updates_destroy(Updates *updates);

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info);
void create_table_init_name(CreateTable *create_table, const char *relation_name);
void create_table_destroy(CreateTable *create_table);

void drop_table_init(DropTable *drop_table, const char *relation_name);
void drop_table_destroy(DropTable *drop_table);

void create_index_init(CreateIndex *create_index, const char *index_name, const char *relation_name, int unique);
void create_index_append_attributes(CreateIndex *create_index, const char *attr_name);
void create_index_destroy(CreateIndex *create_index);

void show_index_init(ShowIndex *show_index, const char *relation_name);
void show_index_destroy(ShowIndex *show_index);

void drop_index_init(DropIndex *drop_index, const char *index_name);
void drop_index_destroy(DropIndex *drop_index);

void desc_table_init(DescTable *desc_table, const char *relation_name);
void desc_table_destroy(DescTable *desc_table);

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name);
void load_data_destroy(LoadData *load_data);

void query_init(Query *query);
Query *query_create();  // create and init
void query_reset(Query *query);
void query_destroy(Query *query);  // reset and delete

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
