
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CUR_SEL CONTEXT->select_length-1

typedef struct ParserContext {
  Query * ssql;

  size_t from_length[MAX_NUM];
	char id[MAX_NUM];

  size_t select_length;
	Selects selects[MAX_NUM];
	Selects left_sub_select;
	Selects right_sub_select;
	Selects update_select;
	Selects sub_select;
	size_t order_attr_length[MAX_NUM];
	ast *order_attrs[MAX_NUM][MAX_NUM];
	OrderPolicy orders[MAX_NUM][MAX_NUM];
	size_t group_by_length[MAX_NUM];
	ast *group_bys[MAX_NUM][MAX_NUM];

	// conditions
  size_t condition_length[MAX_NUM];
  Condition conditions[MAX_NUM][MAX_NUM];
	size_t condition_op_length[MAX_NUM];
	ConditionOp condition_ops[MAX_NUM][MAX_NUM];

	// join
	size_t join_condition_length[MAX];
	Condition join_conditions[MAX_NUM][MAX_NUM];
	size_t join_condition_op_length[MAX_NUM];
	ConditionOp join_condition_ops[MAX_NUM][MAX_NUM];
	size_t join_length[MAX_NUM];
	Join joins[MAX_NUM][MAX_NUM];

	// expressions
	size_t expr_length[MAX_NUM];
	ast* exprs[MAX_NUM][MAX_NUM];
	char *expr_alias[MAX_NUM][MAX_NUM];
	AggrType aggr_type[MAX_NUM];

	size_t in_expr_length[MAX_NUM];
	ast *in_exprs[MAX_NUM][MAX_NUM];

  CompOp comp[MAX_NUM];
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length[0] = 0;
	context->join_condition_length[0] = 0;
	context->join_length[0] = 0;
	context->expr_length[0] = 0;
  context->from_length[0] = 0;
  context->select_length = 0;
  context->ssql->sstr.insertion.pair_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

void clear_selection(ParserContext *context, size_t select_idx)
{
	memset((void *)&context->selects[select_idx], 0, sizeof(Selects));
	context->join_length[select_idx] = 0;
	context->join_condition_length[select_idx] = 0;
	context->condition_length[select_idx] = 0;
	context->expr_length[select_idx] = 0;
}

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

// keywords
%token  CREATE DROP TABLE TABLES INDEX SELECT DESC SHOW SYNC INSERT DELETE
				UPDATE TRX_BEGIN TRX_COMMIT TRX_ROLLBACK HELP EXIT INTO VALUES FROM
				WHERE AND OR SET ON LOAD DATA INFILE INNER JOIN UNIQUE ORDER BY ASC
				GROUP HAVING AS LENGTH ROUND DATE_FORMAT
// punctuations
%token SEMICOLON DOT COMMA LBRACE RBRACE
// types
%token INT_T STRING_T FLOAT_T DATE_T TEXT_T NULL_T NULLABLE
// comps
%token EQ LT GT LE GE NE LIKE NOT ISS EXISTSS INS
// aggregation functions
%token MAX MIN AVG SUM COUNT
// math operator
%token SLASH PLUS MINUS


%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
	struct ast *ast1;
  char *string;
  int number;
  float floats;
	char *position;
	int order_policy1;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V

// nonterminals
%type <number> type;
%type <condition1> condition;
%type <number> number;
%type <ast1> value;
%type <ast1> exp;
%type <ast1> aggr_func;
%type <ast1> func;
%type <number> nullable;
%type <number> is_exist;
%type <number> is_in;
%type <order_policy1> order_policy;
%type <string> as_alias;

// operator precedence
%left PLUS MINUS
%left STAR SLASH

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index	
	| drop_index
	| show_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
      CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
      CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:
    CREATE INDEX ID ON ID LBRACE index_id id_list RBRACE SEMICOLON {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5, 0);
		}
		| CREATE UNIQUE INDEX ID ON ID LBRACE index_id id_list RBRACE SEMICOLON {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6, 1);
		}
    ;

index_id:
		ID {
			create_index_append_attributes(&CONTEXT->ssql->sstr.create_index, $1);
		}
		;

id_list:
		/* empty */
		| COMMA index_id id_list
		;

drop_index:
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
show_index:
		SHOW INDEX FROM ID SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, $4);
		}
		;
create_table:
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list
    ;
    
attr_def:
    ID_get type nullable LBRACE number RBRACE 
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $5, $3);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
    |ID_get type nullable
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, $3);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
    ;
nullable:
		/* empty */ {
			$$ = 0;
		}
		| NULLABLE {
			$$ = 1;
		}
		| NOT NULL_T {
			$$ = 0;
		}
		;
number:
		NUMBER {$$ = $1;}
		;
type:
		INT_T      { $$=INTS;   }
		| STRING_T { $$=CHARS;  }
		| FLOAT_T  { $$=FLOATS; }
		| DATE_T   { $$=DATES;  }
		| TEXT_T   { $$=TEXTS;  }
		;
ID_get:
		ID {
			char *temp=$1; 
			snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
		}
		;

	
insert:
    INSERT INTO ID VALUES insert_pair insert_pair_list SEMICOLON {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, $3);
    }

insert_pair:
		LBRACE insert_expr insert_expr_list RBRACE {
			insert_append_exprs(&CONTEXT->ssql->sstr.insertion, CONTEXT->exprs[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
			CONTEXT->expr_length[CUR_SEL] = 0;
		}
		;

insert_expr:
		exp {
			CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = $1;
		}
		;

insert_expr_list:
    /* empty */
    | COMMA insert_expr insert_expr_list
    ;

insert_pair_list:
		/* empty */
		| COMMA insert_pair insert_pair_list
		;
value:
    NUMBER {
			Value value;
			value_init_integer(&value, $1);
			$$ = new_value_node(&value);
		}
    |FLOAT {
			Value value;
			value_init_float(&value, $1);
			$$ = new_value_node(&value);
		}
    |SSS {
			Value value;
			$1 = substr($1,1,strlen($1)-2);
  		value_init_string(&value, $1);
			$$ = new_value_node(&value);
		}
		|NULL_T {
			Value value;
			value_init_null(&value);
			$$ = new_value_node(&value);
		}
    ;
    
delete:
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			deletes_set_condition_ops(&CONTEXT->ssql->sstr.deletion, CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			CONTEXT->condition_length[CUR_SEL] = 0;	
    }
    ;

update:
    UPDATE ID SET update_pair update_pair_list where SEMICOLON {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, $2, CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			updates_set_condition_ops(&CONTEXT->ssql->sstr.update, CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			CONTEXT->condition_length[CUR_SEL] = 0;
		}
    ;

update_pair:
		ID EQ exp {
			UpdatePair pair;
			update_pair_init(&pair, $1, 0, NULL, $3);
			update_append_pair(&CONTEXT->ssql->sstr.update, &pair);
		}
		| ID EQ update_select {
			UpdatePair pair;
			update_pair_init(&pair, $1, 1, &CONTEXT->update_select, NULL);
			update_append_pair(&CONTEXT->ssql->sstr.update, &pair);
		}
		;

update_pair_list:
		/* empty */
		| COMMA update_pair update_pair_list
		;


select:
		select_body SEMICOLON {
			CONTEXT->ssql->sstr.selection = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
		;

select_body:
  begin_select select_expr select_exprs {
		CONTEXT->ssql->flag=SCF_SELECT;//"select";

		selects_append_exprs(&CONTEXT->selects[CUR_SEL], CONTEXT->exprs[CUR_SEL], CONTEXT->expr_alias[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
	}
  | begin_select select_expr select_exprs FROM rel rel_list inner_join_list where group_by having order_by
		{
			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			selects_append_conditions(&CONTEXT->selects[CUR_SEL], CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			selects_set_condition_ops(&CONTEXT->selects[CUR_SEL], CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			selects_append_joins(&CONTEXT->selects[CUR_SEL], CONTEXT->joins[CUR_SEL], CONTEXT->join_length[CUR_SEL]);
			selects_append_exprs(&CONTEXT->selects[CUR_SEL], CONTEXT->exprs[CUR_SEL], CONTEXT->expr_alias[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
			selects_set_order_info(&CONTEXT->selects[CUR_SEL], CONTEXT->orders[CUR_SEL], CONTEXT->order_attrs[CUR_SEL], CONTEXT->order_attr_length[CUR_SEL]);
			selects_set_group_by(&CONTEXT->selects[CUR_SEL], CONTEXT->group_bys[CUR_SEL], CONTEXT->group_by_length[CUR_SEL]);
	}
	;

having:
	/* empty */
	| HAVING exp comOp exp {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, $2, NULL, 0, $4, NULL);
		selects_set_having(&CONTEXT->selects[CUR_SEL], &condition);
	}
	;

group_by:
		/* empty */
		| GROUP BY group_by_expr group_by_expr_list
		;

group_by_expr:
		exp {
			CONTEXT->group_bys[CUR_SEL][CONTEXT->group_by_length[CUR_SEL]++] = $1;
		}
		;

group_by_expr_list:
		/* empty */
		| COMMA group_by_expr group_by_expr_list
		;

order_by:
		/* empty */
		| ORDER BY order_attr order_attr_list
		;

order_attr:
		exp order_policy {
			CONTEXT->order_attrs[CUR_SEL][CONTEXT->order_attr_length[CUR_SEL]] = $1;
			CONTEXT->orders[CUR_SEL][CONTEXT->order_attr_length[CUR_SEL]] = $2;
			CONTEXT->order_attr_length[CUR_SEL]++;
		}
		;

order_attr_list:
		/* empty */
		| COMMA order_attr order_attr_list
		;

order_policy:
		/* empty */ {
			$$ = ORDER_ASC;
		}
		| ASC {
			$$ = ORDER_ASC;
		}
		| DESC {
			$$ = ORDER_DESC;
		}
		;

begin_select:
		SELECT {
			CONTEXT->select_length++;
		}
		;

select_expr:
	STAR {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = new_attr_node(&attr);
	}
	| ID DOT STAR {
		RelAttr attr;
		relation_attr_init(&attr, $1, "*");
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = new_attr_node(&attr);
	}
	| exp as_alias {
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]] = $1;
		CONTEXT->expr_alias[CUR_SEL][CONTEXT->expr_length[CUR_SEL]] = $2;
		CONTEXT->expr_length[CUR_SEL]++;
	}
	;

func:
	LENGTH LBRACE exp RBRACE {
		$$ = new_func_node(LENGTHF, $3, NULL);
	}
	| ROUND LBRACE exp RBRACE {
		$$ = new_func_node(ROUNDF, $3, NULL);
	}
	| ROUND LBRACE exp COMMA exp RBRACE {
		$$ = new_func_node(ROUNDF, $3, $5);
	}
	| DATE_FORMAT LBRACE exp COMMA exp RBRACE {
		$$ = new_func_node(DATE_FORMATF, $3, $5);
	}
	;


as_alias:
		/* empty */ {
			$$ = NULL;
		}
		|
		ID {
			$$ = strdup($1);
		}
		| AS ID {
			$$ = strdup($2);
		}
		;

select_exprs:
	/* empty */
	| COMMA select_expr select_exprs
	;

aggr_func:
		aggr_type LBRACE ID RBRACE {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $3);
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			$$ = new_aggr_node(&aggr);
		}
		| aggr_type LBRACE ID DOT ID RBRACE {
			RelAttr attr;
			relation_attr_init(&attr, $3, $5);
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			$$ = new_aggr_node(&aggr);
		}
		| aggr_type LBRACE STAR RBRACE {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			$$ = new_aggr_node(&aggr);
		}
		;

aggr_type:
		MAX     { CONTEXT->aggr_type[CUR_SEL] = MAXS; }
		| MIN   { CONTEXT->aggr_type[CUR_SEL] = MINS; }
		| AVG   { CONTEXT->aggr_type[CUR_SEL] = AVGS; }
		| SUM   { CONTEXT->aggr_type[CUR_SEL] = SUMS; }
		| COUNT { CONTEXT->aggr_type[CUR_SEL] = COUNTS; }
		;

rel:
		ID as_alias {
			selects_append_relation(&CONTEXT->selects[CUR_SEL], $1, $2);
		}
		;

rel_list:
    /* empty */
    | COMMA rel rel_list
    ;

inner_join_list:
		/* empty */
		| inner_join inner_join_list
		;

inner_join:
		INNER JOIN ID ON join_condition join_condition_list {
			Join join;
			join_init(&join, $3, CONTEXT->join_conditions[CUR_SEL], CONTEXT->join_condition_length[CUR_SEL]);
			CONTEXT->joins[CUR_SEL][CONTEXT->join_length[CUR_SEL]++] = join;
			CONTEXT->join_condition_length[CUR_SEL] = 0;
		}
		;

join_condition_list:
		/* empty */
		| join_condition_op join_condition join_condition_list
		;

join_condition_op:
		AND {
			CONTEXT->join_condition_ops[CUR_SEL][CONTEXT->join_condition_op_length[CUR_SEL]++] = COND_AND;
		}
		| OR {
			CONTEXT->join_condition_ops[CUR_SEL][CONTEXT->join_condition_op_length[CUR_SEL]++] = COND_OR;
		}
		;

join_condition:
		exp comOp exp {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, $1, NULL, 0, $3, NULL);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->join_condition_length[CUR_SEL]++] = condition;
		}
		| exp comOp right_sub_select {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, $1, NULL, 0, NULL, &CONTEXT->right_sub_select);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
		| left_sub_select comOp exp {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, NULL, &CONTEXT->left_sub_select, 0, $3, NULL);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
		| left_sub_select comOp right_sub_select {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, NULL, &CONTEXT->left_sub_select, 0, NULL, &CONTEXT->right_sub_select);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
		;

where:
    /* empty */ 
    | WHERE condition condition_list
    ;
condition_list:
    /* empty */
    | condition_op condition condition_list
    ;
condition_op:
		AND {
			CONTEXT->condition_ops[CUR_SEL][CONTEXT->condition_op_length[CUR_SEL]++] = COND_AND;
		}
		| OR {
			CONTEXT->condition_ops[CUR_SEL][CONTEXT->condition_op_length[CUR_SEL]++] = COND_OR;
		}
		;
condition:
		exp comOp exp {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, $1, NULL, 0, $3, NULL);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
		| exp comOp right_sub_select {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, $1, NULL, 1, NULL, &CONTEXT->right_sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
		| left_sub_select comOp exp {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 1, NULL, &CONTEXT->left_sub_select, 0, $3, NULL);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
		| left_sub_select comOp right_sub_select {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 1, NULL, &CONTEXT->left_sub_select, 1, NULL, &CONTEXT->right_sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
		| is_exist sub_select {
			Condition condition;
			condition_init_exists(&condition, $1, &CONTEXT->sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
		| exp is_in sub_select {
			Condition condition;
			condition_init_in(&condition, $2, $1, &CONTEXT->sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
		| exp is_in in_pair {
			Condition condition;
			condition_init_in_exprs(&condition, $2, $1, CONTEXT->in_exprs[CUR_SEL], CONTEXT->in_expr_length[CUR_SEL]);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
			CONTEXT->in_expr_length[CUR_SEL] = 0;
		}
		;


in_pair:
		LBRACE in_expr in_expr_list RBRACE
    ;

in_expr:
		exp {
			CONTEXT->in_exprs[CUR_SEL][CONTEXT->in_expr_length[CUR_SEL]++] = $1;
		}
		;

in_expr_list:
		/* empty */
		| COMMA in_expr in_expr_list;
		;

is_exist:
		EXISTSS {
			$$ = 1;
		}
		| NOT EXISTSS {
			$$ = 0;
		}

is_in:
		INS {
			$$ = 1;
		}
		| NOT INS {
			$$ = 0;
		}
		;

update_select:
		LBRACE select_body RBRACE {
			CONTEXT->update_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
		;

sub_select:
		LBRACE select_body RBRACE {
			CONTEXT->sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
		;

left_sub_select:
		LBRACE select_body RBRACE {
			CONTEXT->left_sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
		;

right_sub_select:
		LBRACE select_body RBRACE {
			CONTEXT->right_sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
		;

exp :
		MINUS exp {
			$$ = new_op_node(MATH_SUB, NULL, $2);
		}
		| exp PLUS exp {
			$$ = new_op_node(MATH_ADD, $1, $3);
		}
		| exp MINUS exp {
			$$ = new_op_node(MATH_SUB, $1, $3);
		}
		| exp STAR exp {
			$$ = new_op_node(MATH_MUL, $1, $3);
		}
		| exp SLASH exp {
			$$ = new_op_node(MATH_DIV, $1, $3);
		}
		| LBRACE exp RBRACE {
			$$ = $2;
			$$->l_brace++;
			$$->r_brace++;
		}
		| value {
			$$ = $1;
		}
		| ID {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			$$ = new_attr_node(&attr);
		}
		| ID DOT ID {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			$$ = new_attr_node(&attr);
		}
		| aggr_func {
			$$ = $1;
		}
		| func {
			$$ = $1;
		}
		;

comOp:
  	  EQ { CONTEXT->comp[CUR_SEL] = EQUAL_TO; }
    | LT { CONTEXT->comp[CUR_SEL] = LESS_THAN; }
    | GT { CONTEXT->comp[CUR_SEL] = GREAT_THAN; }
    | LE { CONTEXT->comp[CUR_SEL] = LESS_EQUAL; }
    | GE { CONTEXT->comp[CUR_SEL] = GREAT_EQUAL; }
    | NE { CONTEXT->comp[CUR_SEL] = NOT_EQUAL; }
		| LIKE { CONTEXT->comp[CUR_SEL] = STR_LIKE; }
		| NOT LIKE { CONTEXT->comp[CUR_SEL] = STR_NOT_LIKE; }
		| ISS { CONTEXT->comp[CUR_SEL] = IS; }
		| ISS NOT { CONTEXT->comp[CUR_SEL] = IS_NOT; }
    ;

load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
