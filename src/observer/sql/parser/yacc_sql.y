
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t from_length;
	char id[MAX_NUM];

	// conditions
  size_t condition_length;
  Condition conditions[MAX_NUM];

	// join
	size_t join_condition_length;
	Condition join_conditions[MAX_NUM];
	size_t join_length;
	Join joins[MAX_NUM];

	// expressions
	size_t expr_length;
	ast* exprs[MAX_NUM];
	AggrType aggr_type;

  CompOp comp;
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
  context->condition_length = 0;
	context->join_condition_length = 0;
	context->join_length = 0;
	context->expr_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->ssql->sstr.insertion.pair_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

// keywords
%token  CREATE DROP TABLE TABLES INDEX SELECT DESC SHOW SYNC INSERT DELETE
				UPDATE TRX_BEGIN TRX_COMMIT TRX_ROLLBACK HELP EXIT INTO VALUES FROM
				WHERE AND SET ON LOAD DATA INFILE INNER JOIN UNIQUE
// punctuations
%token SEMICOLON DOT COMMA LBRACE RBRACE
// types
%token INT_T STRING_T FLOAT_T DATE_T
// comps
%token EQ LT GT LE GE NE LIKE NOT
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
%type <value1> value;
%type <number> number;
%type <ast1> exp;
%type <ast1> aggr_func;

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
		| CREATE UNIQUE INDEX ID ON ID LBRACE index_id RBRACE SEMICOLON {
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
    ID_get type LBRACE number RBRACE 
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
    |ID_get type
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
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
			insert_append_exprs(&CONTEXT->ssql->sstr.insertion, CONTEXT->exprs, CONTEXT->expr_length);
			CONTEXT->expr_length = 0;
		}
		;

insert_expr:
		exp {
			CONTEXT->exprs[CONTEXT->expr_length++] = $1;
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
    ;
    
delete:
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
    ;
update:
    UPDATE ID SET ID EQ value where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, $2, $4, $6, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
    ;
select:
    SELECT select_expr select_exprs FROM ID rel_list inner_join_list where SEMICOLON
		{
			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			selects_append_relation(&CONTEXT->ssql->sstr.selection, $5);
			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
			select_append_joins(&CONTEXT->ssql->sstr.selection, CONTEXT->joins, CONTEXT->join_length);
			select_append_exprs(&CONTEXT->ssql->sstr.selection, CONTEXT->exprs, CONTEXT->expr_length);

			CONTEXT->condition_length=0;
			CONTEXT->join_condition_length=0;
			CONTEXT->join_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->expr_length=0;
	}
	;

select_expr:
	STAR {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		CONTEXT->exprs[CONTEXT->expr_length++] = new_attr_node(&attr);
	}
	| exp {
		CONTEXT->exprs[CONTEXT->expr_length++] = $1;
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
			aggregate_init(&aggr, CONTEXT->aggr_type, 1, &attr, NULL);
			$$ = new_aggr_node(&aggr);
		}
		| aggr_type LBRACE ID DOT ID RBRACE {
			RelAttr attr;
			relation_attr_init(&attr, $3, $5);
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type, 1, &attr, NULL);
			$$ = new_aggr_node(&aggr);
		}
		| aggr_type LBRACE STAR RBRACE {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type, 1, &attr, NULL);
			$$ = new_aggr_node(&aggr);
		}
		;

aggr_type:
		MAX     { CONTEXT->aggr_type = MAXS; }
		| MIN   { CONTEXT->aggr_type = MINS; }
		| AVG   { CONTEXT->aggr_type = AVGS; }
		| SUM   { CONTEXT->aggr_type = SUMS; }
		| COUNT { CONTEXT->aggr_type = COUNTS; }
		;

rel_list:
    /* empty */
    | COMMA ID rel_list {	
			selects_append_relation(&CONTEXT->ssql->sstr.selection, $2);
		}
    ;

inner_join_list:
		/* empty */
		| inner_join inner_join_list
		;

inner_join:
		INNER JOIN ID ON join_condition join_condition_list {
			Join join;
			join_init(&join, $3, CONTEXT->join_conditions, CONTEXT->join_condition_length);
			CONTEXT->joins[CONTEXT->join_length++] = join;
			CONTEXT->join_condition_length = 0;
		}
		;

join_condition_list:
		/* empty */
		| AND join_condition join_condition_list
		;

join_condition:
		exp comOp exp {
			Condition condition;
			condition_init(&condition, CONTEXT->comp, $1, $3);
			CONTEXT->join_conditions[CONTEXT->join_condition_length++] = condition;
		}
		;

where:
    /* empty */ 
    | WHERE condition condition_list
    ;
condition_list:
    /* empty */
    | AND condition condition_list
    ;
condition:
		exp comOp exp {
			Condition condition;
			condition_init(&condition, CONTEXT->comp, $1, $3);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
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
		;

comOp:
  	  EQ { CONTEXT->comp = EQUAL_TO; }
    | LT { CONTEXT->comp = LESS_THAN; }
    | GT { CONTEXT->comp = GREAT_THAN; }
    | LE { CONTEXT->comp = LESS_EQUAL; }
    | GE { CONTEXT->comp = GREAT_EQUAL; }
    | NE { CONTEXT->comp = NOT_EQUAL; }
		| LIKE { CONTEXT->comp = STR_LIKE; }
		| NOT LIKE { CONTEXT->comp = STR_NOT_LIKE; }
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
