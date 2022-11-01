/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 167 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CREATE = 3,                     /* CREATE  */
  YYSYMBOL_DROP = 4,                       /* DROP  */
  YYSYMBOL_TABLE = 5,                      /* TABLE  */
  YYSYMBOL_TABLES = 6,                     /* TABLES  */
  YYSYMBOL_INDEX = 7,                      /* INDEX  */
  YYSYMBOL_SELECT = 8,                     /* SELECT  */
  YYSYMBOL_DESC = 9,                       /* DESC  */
  YYSYMBOL_SHOW = 10,                      /* SHOW  */
  YYSYMBOL_SYNC = 11,                      /* SYNC  */
  YYSYMBOL_INSERT = 12,                    /* INSERT  */
  YYSYMBOL_DELETE = 13,                    /* DELETE  */
  YYSYMBOL_UPDATE = 14,                    /* UPDATE  */
  YYSYMBOL_TRX_BEGIN = 15,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 16,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 17,              /* TRX_ROLLBACK  */
  YYSYMBOL_HELP = 18,                      /* HELP  */
  YYSYMBOL_EXIT = 19,                      /* EXIT  */
  YYSYMBOL_INTO = 20,                      /* INTO  */
  YYSYMBOL_VALUES = 21,                    /* VALUES  */
  YYSYMBOL_FROM = 22,                      /* FROM  */
  YYSYMBOL_WHERE = 23,                     /* WHERE  */
  YYSYMBOL_AND = 24,                       /* AND  */
  YYSYMBOL_OR = 25,                        /* OR  */
  YYSYMBOL_SET = 26,                       /* SET  */
  YYSYMBOL_ON = 27,                        /* ON  */
  YYSYMBOL_LOAD = 28,                      /* LOAD  */
  YYSYMBOL_DATA = 29,                      /* DATA  */
  YYSYMBOL_INFILE = 30,                    /* INFILE  */
  YYSYMBOL_INNER = 31,                     /* INNER  */
  YYSYMBOL_JOIN = 32,                      /* JOIN  */
  YYSYMBOL_UNIQUE = 33,                    /* UNIQUE  */
  YYSYMBOL_SEMICOLON = 34,                 /* SEMICOLON  */
  YYSYMBOL_DOT = 35,                       /* DOT  */
  YYSYMBOL_COMMA = 36,                     /* COMMA  */
  YYSYMBOL_LBRACE = 37,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 38,                    /* RBRACE  */
  YYSYMBOL_INT_T = 39,                     /* INT_T  */
  YYSYMBOL_STRING_T = 40,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 41,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 42,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 43,                    /* TEXT_T  */
  YYSYMBOL_NULL_T = 44,                    /* NULL_T  */
  YYSYMBOL_NULLABLE = 45,                  /* NULLABLE  */
  YYSYMBOL_EQ = 46,                        /* EQ  */
  YYSYMBOL_LT = 47,                        /* LT  */
  YYSYMBOL_GT = 48,                        /* GT  */
  YYSYMBOL_LE = 49,                        /* LE  */
  YYSYMBOL_GE = 50,                        /* GE  */
  YYSYMBOL_NE = 51,                        /* NE  */
  YYSYMBOL_LIKE = 52,                      /* LIKE  */
  YYSYMBOL_NOT = 53,                       /* NOT  */
  YYSYMBOL_ISS = 54,                       /* ISS  */
  YYSYMBOL_EXISTSS = 55,                   /* EXISTSS  */
  YYSYMBOL_INS = 56,                       /* INS  */
  YYSYMBOL_MAX = 57,                       /* MAX  */
  YYSYMBOL_MIN = 58,                       /* MIN  */
  YYSYMBOL_AVG = 59,                       /* AVG  */
  YYSYMBOL_SUM = 60,                       /* SUM  */
  YYSYMBOL_COUNT = 61,                     /* COUNT  */
  YYSYMBOL_SLASH = 62,                     /* SLASH  */
  YYSYMBOL_PLUS = 63,                      /* PLUS  */
  YYSYMBOL_MINUS = 64,                     /* MINUS  */
  YYSYMBOL_NUMBER = 65,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 66,                     /* FLOAT  */
  YYSYMBOL_ID = 67,                        /* ID  */
  YYSYMBOL_PATH = 68,                      /* PATH  */
  YYSYMBOL_SSS = 69,                       /* SSS  */
  YYSYMBOL_STAR = 70,                      /* STAR  */
  YYSYMBOL_STRING_V = 71,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 72,                  /* $accept  */
  YYSYMBOL_commands = 73,                  /* commands  */
  YYSYMBOL_command = 74,                   /* command  */
  YYSYMBOL_exit = 75,                      /* exit  */
  YYSYMBOL_help = 76,                      /* help  */
  YYSYMBOL_sync = 77,                      /* sync  */
  YYSYMBOL_begin = 78,                     /* begin  */
  YYSYMBOL_commit = 79,                    /* commit  */
  YYSYMBOL_rollback = 80,                  /* rollback  */
  YYSYMBOL_drop_table = 81,                /* drop_table  */
  YYSYMBOL_show_tables = 82,               /* show_tables  */
  YYSYMBOL_desc_table = 83,                /* desc_table  */
  YYSYMBOL_create_index = 84,              /* create_index  */
  YYSYMBOL_index_id = 85,                  /* index_id  */
  YYSYMBOL_id_list = 86,                   /* id_list  */
  YYSYMBOL_drop_index = 87,                /* drop_index  */
  YYSYMBOL_show_index = 88,                /* show_index  */
  YYSYMBOL_create_table = 89,              /* create_table  */
  YYSYMBOL_attr_def_list = 90,             /* attr_def_list  */
  YYSYMBOL_attr_def = 91,                  /* attr_def  */
  YYSYMBOL_nullable = 92,                  /* nullable  */
  YYSYMBOL_number = 93,                    /* number  */
  YYSYMBOL_type = 94,                      /* type  */
  YYSYMBOL_ID_get = 95,                    /* ID_get  */
  YYSYMBOL_insert = 96,                    /* insert  */
  YYSYMBOL_insert_pair = 97,               /* insert_pair  */
  YYSYMBOL_insert_expr = 98,               /* insert_expr  */
  YYSYMBOL_insert_expr_list = 99,          /* insert_expr_list  */
  YYSYMBOL_insert_pair_list = 100,         /* insert_pair_list  */
  YYSYMBOL_value = 101,                    /* value  */
  YYSYMBOL_delete = 102,                   /* delete  */
  YYSYMBOL_update = 103,                   /* update  */
  YYSYMBOL_update_pair = 104,              /* update_pair  */
  YYSYMBOL_update_pair_list = 105,         /* update_pair_list  */
  YYSYMBOL_select = 106,                   /* select  */
  YYSYMBOL_select_body = 107,              /* select_body  */
  YYSYMBOL_begin_select = 108,             /* begin_select  */
  YYSYMBOL_select_expr = 109,              /* select_expr  */
  YYSYMBOL_select_exprs = 110,             /* select_exprs  */
  YYSYMBOL_aggr_func = 111,                /* aggr_func  */
  YYSYMBOL_aggr_type = 112,                /* aggr_type  */
  YYSYMBOL_rel_list = 113,                 /* rel_list  */
  YYSYMBOL_inner_join_list = 114,          /* inner_join_list  */
  YYSYMBOL_inner_join = 115,               /* inner_join  */
  YYSYMBOL_join_condition_list = 116,      /* join_condition_list  */
  YYSYMBOL_join_condition_op = 117,        /* join_condition_op  */
  YYSYMBOL_join_condition = 118,           /* join_condition  */
  YYSYMBOL_where = 119,                    /* where  */
  YYSYMBOL_condition_list = 120,           /* condition_list  */
  YYSYMBOL_condition_op = 121,             /* condition_op  */
  YYSYMBOL_condition = 122,                /* condition  */
  YYSYMBOL_in_pair = 123,                  /* in_pair  */
  YYSYMBOL_in_expr = 124,                  /* in_expr  */
  YYSYMBOL_in_expr_list = 125,             /* in_expr_list  */
  YYSYMBOL_is_exist = 126,                 /* is_exist  */
  YYSYMBOL_is_in = 127,                    /* is_in  */
  YYSYMBOL_update_select = 128,            /* update_select  */
  YYSYMBOL_sub_select = 129,               /* sub_select  */
  YYSYMBOL_left_sub_select = 130,          /* left_sub_select  */
  YYSYMBOL_right_sub_select = 131,         /* right_sub_select  */
  YYSYMBOL_exp = 132,                      /* exp  */
  YYSYMBOL_comOp = 133,                    /* comOp  */
  YYSYMBOL_load_data = 134                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   326

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  143
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  280

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   326


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   154,   154,   156,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   181,   186,   191,   197,   203,   209,   215,   221,
     227,   234,   238,   245,   250,   252,   256,   263,   270,   276,
     278,   282,   288,   296,   299,   302,   307,   310,   311,   312,
     313,   314,   317,   325,   331,   338,   343,   345,   348,   350,
     353,   358,   363,   369,   377,   389,   398,   403,   410,   412,
     417,   425,   438,   444,   449,   454,   456,   460,   467,   474,
     484,   485,   486,   487,   488,   491,   493,   498,   500,   504,
     512,   514,   518,   521,   527,   532,   537,   542,   549,   551,
     553,   555,   558,   561,   566,   571,   576,   581,   586,   591,
     596,   606,   610,   615,   617,   621,   624,   629,   632,   638,
     646,   654,   662,   670,   673,   676,   679,   682,   685,   690,
     693,   698,   703,   709,   710,   711,   712,   713,   714,   715,
     716,   717,   718,   722
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CREATE", "DROP",
  "TABLE", "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "HELP",
  "EXIT", "INTO", "VALUES", "FROM", "WHERE", "AND", "OR", "SET", "ON",
  "LOAD", "DATA", "INFILE", "INNER", "JOIN", "UNIQUE", "SEMICOLON", "DOT",
  "COMMA", "LBRACE", "RBRACE", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "TEXT_T", "NULL_T", "NULLABLE", "EQ", "LT", "GT", "LE", "GE", "NE",
  "LIKE", "NOT", "ISS", "EXISTSS", "INS", "MAX", "MIN", "AVG", "SUM",
  "COUNT", "SLASH", "PLUS", "MINUS", "NUMBER", "FLOAT", "ID", "PATH",
  "SSS", "STAR", "STRING_V", "$accept", "commands", "command", "exit",
  "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "desc_table", "create_index", "index_id", "id_list",
  "drop_index", "show_index", "create_table", "attr_def_list", "attr_def",
  "nullable", "number", "type", "ID_get", "insert", "insert_pair",
  "insert_expr", "insert_expr_list", "insert_pair_list", "value", "delete",
  "update", "update_pair", "update_pair_list", "select", "select_body",
  "begin_select", "select_expr", "select_exprs", "aggr_func", "aggr_type",
  "rel_list", "inner_join_list", "inner_join", "join_condition_list",
  "join_condition_op", "join_condition", "where", "condition_list",
  "condition_op", "condition", "in_pair", "in_expr", "in_expr_list",
  "is_exist", "is_in", "update_select", "sub_select", "left_sub_select",
  "right_sub_select", "exp", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-256)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -256,   229,  -256,     3,    45,  -256,   -48,     8,    -9,     9,
      39,     6,    -4,    33,    56,    58,    60,    72,  -256,  -256,
    -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,
    -256,  -256,  -256,  -256,  -256,  -256,    69,   -26,  -256,    42,
      43,   108,    55,    59,    89,    91,   107,  -256,    63,    65,
     110,  -256,  -256,  -256,  -256,  -256,   103,  -256,    87,  -256,
    -256,  -256,  -256,  -256,  -256,    87,  -256,  -256,   102,  -256,
    -256,  -256,   104,  -256,   101,    23,   105,   114,    82,   116,
     123,  -256,  -256,    92,   137,   140,    93,    95,   -17,   -53,
      98,   -26,   144,   -43,    87,    87,    87,    87,   100,   119,
     141,  -256,  -256,   135,   133,    47,   138,   125,   152,   169,
    -256,  -256,   104,   132,    13,   166,  -256,   -53,   -53,  -256,
    -256,   156,    78,   153,   139,  -256,    87,   172,     5,   155,
    -256,    31,   180,    29,   212,  -256,   118,    93,   140,   204,
    -256,   186,   157,  -256,  -256,   100,   188,  -256,  -256,  -256,
    -256,  -256,   -33,   160,   191,   194,    23,   133,   197,   211,
    -256,  -256,  -256,  -256,    47,   242,  -256,  -256,  -256,  -256,
    -256,  -256,  -256,  -256,   199,   200,   136,   -30,  -256,   215,
     136,     5,  -256,    23,   152,   220,   189,   202,   224,   232,
     156,   233,  -256,   227,   235,  -256,   241,   160,    87,   240,
     172,  -256,  -256,    31,   243,  -256,  -256,     5,  -256,    23,
    -256,     5,  -256,  -256,  -256,    23,   254,  -256,  -256,   239,
     186,   247,   140,   224,  -256,  -256,  -256,  -256,   228,   160,
     256,   241,   194,  -256,  -256,  -256,  -256,   257,   244,    23,
    -256,  -256,  -256,   230,  -256,  -256,  -256,   258,   241,   264,
     265,  -256,  -256,    87,   266,   275,  -256,  -256,  -256,   271,
     244,  -256,   154,  -256,  -256,    73,    29,   237,  -256,  -256,
    -256,   154,   136,   136,    73,  -256,    23,  -256,    23,  -256
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    72,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,     0,     0,    19,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,    25,    26,    27,    23,    22,     0,    70,     0,    63,
      80,    81,    82,    83,    84,     0,    60,    61,   130,    62,
      73,   129,    75,   132,     0,    74,     0,     0,     0,     0,
       0,    30,    29,     0,     0,    98,     0,     0,     0,   123,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    36,     0,     0,     0,     0,     0,    68,     0,
     128,   131,    75,     0,     0,     0,   127,   124,   125,   126,
      52,    39,     0,     0,     0,    37,     0,    58,     0,     0,
     115,   100,     0,     0,     0,    64,     0,     0,    98,     0,
      76,    85,     0,    77,    79,     0,     0,    47,    48,    49,
      50,    51,    43,     0,     0,    56,    55,     0,     0,     0,
     116,   102,   103,    99,     0,     0,   108,   133,   134,   135,
     136,   137,   138,   139,     0,   141,     0,     0,   117,     0,
       0,     0,    67,    66,    68,     0,     0,     0,    87,     0,
      39,     0,    44,     0,    42,    33,    34,     0,     0,     0,
      58,    53,   121,   100,     0,   140,   142,     0,   107,   106,
     118,     0,   110,   109,   105,   104,     0,    69,    65,     0,
      85,     0,    98,    87,    78,    40,    38,    45,     0,     0,
       0,    34,    56,    54,    59,   101,   120,     0,   113,   112,
     119,   143,    86,     0,    71,    88,    46,     0,    34,     0,
       0,    57,   122,     0,     0,     0,    41,    35,    31,     0,
     113,   111,     0,    32,   114,    90,     0,     0,    92,    93,
      89,     0,     0,     0,    90,    97,    96,    95,    94,    91
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,  -256,
    -256,  -256,  -256,  -192,  -225,  -256,  -256,  -256,   120,   161,
    -256,  -256,  -256,  -256,  -256,   151,   111,    79,   112,  -256,
    -256,  -256,   176,   130,  -256,     0,  -256,   225,   203,  -256,
    -256,    97,    96,  -256,    44,  -256,    49,  -134,   121,  -256,
     158,  -256,    68,    66,  -256,  -256,  -256,   146,  -255,  -177,
     -37,  -132,  -256
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   196,   230,    29,    30,    31,   146,   121,
     194,   247,   152,   122,    32,   127,   155,   199,   158,    71,
      33,    34,   108,   138,    35,   204,    37,    72,    92,    73,
      74,   188,   222,   223,   270,   271,   265,   106,   163,   164,
     131,   212,   238,   254,   132,   179,   182,   166,   133,   208,
      88,   176,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      75,    36,   180,   214,   185,   231,   250,   266,    39,    94,
      40,    58,   192,     5,    45,    46,   266,    97,    59,    44,
     193,   110,   205,   257,   114,    47,   210,   115,    89,    48,
      51,    60,    61,    62,    63,    64,    41,   248,    65,    66,
      67,    68,    58,    69,    70,    94,    95,    96,   142,    59,
      42,   143,    43,    97,    75,   161,   162,   116,   117,   118,
     119,    49,    60,    61,    62,    63,    64,    52,   134,    65,
      66,    67,    68,    50,    69,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   128,    94,    95,    96,   244,   156,
      53,    59,    54,    97,    55,   275,   277,   268,   269,   183,
     129,    56,   130,    57,    60,    61,    62,    63,    64,    76,
      77,    65,    66,    67,    68,    78,    69,   147,   148,   149,
     150,   151,    79,    81,    58,    82,    80,   134,   159,    83,
      84,    59,    85,    87,   272,   273,    86,    90,    93,   209,
      91,    99,    98,   215,    60,    61,    62,    63,    64,   100,
     101,    65,    66,    67,    68,   181,    69,   102,   104,   103,
     107,   156,    59,   105,   109,   111,   113,   120,   124,   125,
     126,   136,   135,   207,   239,    60,    61,    62,    63,    64,
      59,   216,    65,    66,    67,    68,   123,    69,   137,   139,
     153,   128,   145,    60,    61,    62,    63,    64,    59,   141,
      65,    66,    67,    68,   144,    69,   154,   237,   157,   186,
     160,    60,    61,    62,    63,    64,   239,   165,    65,    66,
      67,    68,   187,    69,   189,   267,   191,   195,   197,     2,
     198,   201,     3,     4,   267,   276,   278,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,   202,
       5,   205,   211,   206,   218,   221,   219,    17,   167,   168,
     169,   170,   171,   172,   173,   177,   175,   226,   178,   220,
     224,   227,   228,   241,    94,    95,    96,   229,   233,   243,
     253,   236,    97,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   240,   246,   249,   252,   256,   255,   258,    94,
      95,    96,   262,   259,   261,   263,   190,    97,   200,   232,
     225,   251,   234,   184,   217,   140,   112,   242,   279,   245,
     274,   260,   203,     0,   235,   213,   264
};

static const yytype_int16 yycheck[] =
{
      37,     1,   134,   180,   138,   197,   231,   262,     5,    62,
       7,    37,    45,     8,     6,     7,   271,    70,    44,    67,
      53,    38,    52,   248,    67,    34,    56,    70,    65,    20,
      34,    57,    58,    59,    60,    61,    33,   229,    64,    65,
      66,    67,    37,    69,    70,    62,    63,    64,    35,    44,
       5,    38,     7,    70,    91,    24,    25,    94,    95,    96,
      97,    22,    57,    58,    59,    60,    61,    34,   105,    64,
      65,    66,    67,    67,    69,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    37,    62,    63,    64,   222,   126,
      34,    44,    34,    70,    34,   272,   273,    24,    25,   136,
      53,    29,    55,    34,    57,    58,    59,    60,    61,    67,
      67,    64,    65,    66,    67,     7,    69,    39,    40,    41,
      42,    43,    67,    34,    37,    34,    67,   164,   128,    22,
      67,    44,    67,    30,   266,   267,    26,    35,    37,   176,
      36,    27,    37,   180,    57,    58,    59,    60,    61,    67,
      34,    64,    65,    66,    67,    37,    69,    34,    21,    67,
      67,   198,    44,    23,    69,    67,    22,    67,    27,    34,
      37,    46,    34,    37,   211,    57,    58,    59,    60,    61,
      44,   181,    64,    65,    66,    67,    67,    69,    36,    20,
      37,    37,    36,    57,    58,    59,    60,    61,    44,    67,
      64,    65,    66,    67,    38,    69,    67,   207,    36,     5,
      55,    57,    58,    59,    60,    61,   253,    37,    64,    65,
      66,    67,    36,    69,    67,   262,    38,    67,    37,     0,
      36,    34,     3,     4,   271,   272,   273,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    38,
       8,    52,    37,    53,    34,    31,    67,    28,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    34,    56,    67,
      38,    44,    37,    34,    62,    63,    64,    36,    38,    32,
      36,    38,    70,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    38,    65,    38,    38,    38,    67,    34,    62,
      63,    64,    27,    38,    38,    34,   145,    70,   157,   198,
     190,   232,   200,   137,   184,   112,    91,   220,   274,   223,
     271,   253,   164,    -1,   203,   179,   260
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    73,     0,     3,     4,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    28,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    87,
      88,    89,    96,   102,   103,   106,   107,   108,   134,     5,
       7,    33,     5,     7,    67,     6,     7,    34,    20,    22,
      67,    34,    34,    34,    34,    34,    29,    34,    37,    44,
      57,    58,    59,    60,    61,    64,    65,    66,    67,    69,
      70,   101,   109,   111,   112,   132,    67,    67,     7,    67,
      67,    34,    34,    22,    67,    67,    26,    30,   132,   132,
      35,    36,   110,    37,    62,    63,    64,    70,    37,    27,
      67,    34,    34,    67,    21,    23,   119,    67,   104,    69,
      38,    67,   109,    22,    67,    70,   132,   132,   132,   132,
      67,    91,    95,    67,    27,    34,    37,    97,    37,    53,
      55,   122,   126,   130,   132,    34,    46,    36,   105,    20,
     110,    67,    35,    38,    38,    36,    90,    39,    40,    41,
      42,    43,    94,    37,    67,    98,   132,    36,   100,   107,
      55,    24,    25,   120,   121,    37,   129,    46,    47,    48,
      49,    50,    51,    52,    53,    54,   133,    53,    56,   127,
     133,    37,   128,   132,   104,   119,     5,    36,   113,    67,
      91,    38,    45,    53,    92,    67,    85,    37,    36,    99,
      97,    34,    38,   122,   107,    52,    53,    37,   131,   132,
      56,    37,   123,   129,   131,   132,   107,   105,    34,    67,
      67,    31,   114,   115,    38,    90,    34,    44,    37,    36,
      86,    85,    98,    38,   100,   120,    38,   107,   124,   132,
      38,    34,   113,    32,   119,   114,    65,    93,    85,    38,
      86,    99,    38,    36,   125,    67,    38,    86,    34,    38,
     124,    38,    27,    34,   125,   118,   130,   132,    24,    25,
     116,   117,   133,   133,   118,   131,   132,   131,   132,   116
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    72,    73,    73,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    84,    85,    86,    86,    87,    88,    89,    90,
      90,    91,    91,    92,    92,    92,    93,    94,    94,    94,
      94,    94,    95,    96,    97,    98,    99,    99,   100,   100,
     101,   101,   101,   101,   102,   103,   104,   104,   105,   105,
     106,   107,   108,   109,   109,   110,   110,   111,   111,   111,
     112,   112,   112,   112,   112,   113,   113,   114,   114,   115,
     116,   116,   117,   117,   118,   118,   118,   118,   119,   119,
     120,   120,   121,   121,   122,   122,   122,   122,   122,   122,
     122,   123,   124,   125,   125,   126,   126,   127,   127,   128,
     129,   130,   131,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   134
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,    10,    11,     1,     0,     3,     4,     5,     8,     0,
       3,     6,     3,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     7,     4,     1,     0,     3,     0,     3,
       1,     1,     1,     1,     5,     7,     3,     3,     0,     3,
       2,     8,     1,     1,     1,     0,     3,     4,     6,     4,
       1,     1,     1,     1,     1,     0,     3,     0,     2,     6,
       0,     3,     1,     1,     3,     3,     3,     3,     0,     3,
       0,     3,     1,     1,     3,     3,     3,     3,     2,     3,
       3,     4,     1,     0,     3,     1,     2,     1,     2,     3,
       3,     3,     3,     2,     3,     3,     3,     3,     3,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 22: /* exit: EXIT SEMICOLON  */
#line 181 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1510 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 186 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1518 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 191 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1526 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 197 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1534 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 203 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1542 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 209 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1550 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 215 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1559 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 221 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1567 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 227 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1576 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE index_id id_list RBRACE SEMICOLON  */
#line 234 "yacc_sql.y"
                                                                   {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
		}
#line 1585 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE index_id id_list RBRACE SEMICOLON  */
#line 238 "yacc_sql.y"
                                                                                        {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
		}
#line 1594 "yacc_sql.tab.c"
    break;

  case 33: /* index_id: ID  */
#line 245 "yacc_sql.y"
                   {
			create_index_append_attributes(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
		}
#line 1602 "yacc_sql.tab.c"
    break;

  case 36: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 257 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1611 "yacc_sql.tab.c"
    break;

  case 37: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 264 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1620 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 271 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
		}
#line 1629 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type nullable LBRACE number RBRACE  */
#line 283 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-1].number), (yyvsp[-3].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1639 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type nullable  */
#line 289 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, (yyvsp[0].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1649 "yacc_sql.tab.c"
    break;

  case 43: /* nullable: %empty  */
#line 296 "yacc_sql.y"
                            {
			(yyval.number) = 0;
		}
#line 1657 "yacc_sql.tab.c"
    break;

  case 44: /* nullable: NULLABLE  */
#line 299 "yacc_sql.y"
                           {
			(yyval.number) = 1;
		}
#line 1665 "yacc_sql.tab.c"
    break;

  case 45: /* nullable: NOT NULL_T  */
#line 302 "yacc_sql.y"
                             {
			(yyval.number) = 0;
		}
#line 1673 "yacc_sql.tab.c"
    break;

  case 46: /* number: NUMBER  */
#line 307 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1679 "yacc_sql.tab.c"
    break;

  case 47: /* type: INT_T  */
#line 310 "yacc_sql.y"
                           { (yyval.number)=INTS;   }
#line 1685 "yacc_sql.tab.c"
    break;

  case 48: /* type: STRING_T  */
#line 311 "yacc_sql.y"
                           { (yyval.number)=CHARS;  }
#line 1691 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 312 "yacc_sql.y"
                           { (yyval.number)=FLOATS; }
#line 1697 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 313 "yacc_sql.y"
                           { (yyval.number)=DATES;  }
#line 1703 "yacc_sql.tab.c"
    break;

  case 51: /* type: TEXT_T  */
#line 314 "yacc_sql.y"
                           { (yyval.number)=TEXTS;  }
#line 1709 "yacc_sql.tab.c"
    break;

  case 52: /* ID_get: ID  */
#line 317 "yacc_sql.y"
                   {
			char *temp=(yyvsp[0].string); 
			snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
		}
#line 1718 "yacc_sql.tab.c"
    break;

  case 53: /* insert: INSERT INTO ID VALUES insert_pair insert_pair_list SEMICOLON  */
#line 325 "yacc_sql.y"
                                                                 {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
#line 1727 "yacc_sql.tab.c"
    break;

  case 54: /* insert_pair: LBRACE insert_expr insert_expr_list RBRACE  */
#line 331 "yacc_sql.y"
                                                           {
			insert_append_exprs(&CONTEXT->ssql->sstr.insertion, CONTEXT->exprs[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
			CONTEXT->expr_length[CUR_SEL] = 0;
		}
#line 1736 "yacc_sql.tab.c"
    break;

  case 55: /* insert_expr: exp  */
#line 338 "yacc_sql.y"
                    {
			CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 1744 "yacc_sql.tab.c"
    break;

  case 60: /* value: NUMBER  */
#line 353 "yacc_sql.y"
           {
			Value value;
			value_init_integer(&value, (yyvsp[0].number));
			(yyval.ast1) = new_value_node(&value);
		}
#line 1754 "yacc_sql.tab.c"
    break;

  case 61: /* value: FLOAT  */
#line 358 "yacc_sql.y"
           {
			Value value;
			value_init_float(&value, (yyvsp[0].floats));
			(yyval.ast1) = new_value_node(&value);
		}
#line 1764 "yacc_sql.tab.c"
    break;

  case 62: /* value: SSS  */
#line 363 "yacc_sql.y"
         {
			Value value;
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&value, (yyvsp[0].string));
			(yyval.ast1) = new_value_node(&value);
		}
#line 1775 "yacc_sql.tab.c"
    break;

  case 63: /* value: NULL_T  */
#line 369 "yacc_sql.y"
                        {
			Value value;
			value_init_null(&value);
			(yyval.ast1) = new_value_node(&value);
		}
#line 1785 "yacc_sql.tab.c"
    break;

  case 64: /* delete: DELETE FROM ID where SEMICOLON  */
#line 378 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			deletes_set_condition_ops(&CONTEXT->ssql->sstr.deletion, CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			CONTEXT->condition_length[CUR_SEL] = 0;	
    }
#line 1798 "yacc_sql.tab.c"
    break;

  case 65: /* update: UPDATE ID SET update_pair update_pair_list where SEMICOLON  */
#line 389 "yacc_sql.y"
                                                               {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			updates_set_condition_ops(&CONTEXT->ssql->sstr.update, CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			CONTEXT->condition_length[CUR_SEL] = 0;
		}
#line 1809 "yacc_sql.tab.c"
    break;

  case 66: /* update_pair: ID EQ exp  */
#line 398 "yacc_sql.y"
                          {
			UpdatePair pair;
			update_pair_init(&pair, (yyvsp[-2].string), 0, NULL, (yyvsp[0].ast1));
			update_append_pair(&CONTEXT->ssql->sstr.update, &pair);
		}
#line 1819 "yacc_sql.tab.c"
    break;

  case 67: /* update_pair: ID EQ update_select  */
#line 403 "yacc_sql.y"
                                      {
			UpdatePair pair;
			update_pair_init(&pair, (yyvsp[-2].string), 1, &CONTEXT->update_select, NULL);
			update_append_pair(&CONTEXT->ssql->sstr.update, &pair);
		}
#line 1829 "yacc_sql.tab.c"
    break;

  case 70: /* select: select_body SEMICOLON  */
#line 417 "yacc_sql.y"
                                      {
			CONTEXT->ssql->sstr.selection = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 1839 "yacc_sql.tab.c"
    break;

  case 71: /* select_body: begin_select select_expr select_exprs FROM ID rel_list inner_join_list where  */
#line 426 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			selects_append_relation(&CONTEXT->selects[CUR_SEL], (yyvsp[-3].string));
			selects_append_conditions(&CONTEXT->selects[CUR_SEL], CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			selects_set_condition_ops(&CONTEXT->selects[CUR_SEL], CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			select_append_joins(&CONTEXT->selects[CUR_SEL], CONTEXT->joins[CUR_SEL], CONTEXT->join_length[CUR_SEL]);
			select_append_exprs(&CONTEXT->selects[CUR_SEL], CONTEXT->exprs[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
	}
#line 1853 "yacc_sql.tab.c"
    break;

  case 72: /* begin_select: SELECT  */
#line 438 "yacc_sql.y"
                       {
			CONTEXT->select_length++;
		}
#line 1861 "yacc_sql.tab.c"
    break;

  case 73: /* select_expr: STAR  */
#line 444 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = new_attr_node(&attr);
	}
#line 1871 "yacc_sql.tab.c"
    break;

  case 74: /* select_expr: exp  */
#line 449 "yacc_sql.y"
              {
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = (yyvsp[0].ast1);
	}
#line 1879 "yacc_sql.tab.c"
    break;

  case 77: /* aggr_func: aggr_type LBRACE ID RBRACE  */
#line 460 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 1891 "yacc_sql.tab.c"
    break;

  case 78: /* aggr_func: aggr_type LBRACE ID DOT ID RBRACE  */
#line 467 "yacc_sql.y"
                                                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 1903 "yacc_sql.tab.c"
    break;

  case 79: /* aggr_func: aggr_type LBRACE STAR RBRACE  */
#line 474 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 1915 "yacc_sql.tab.c"
    break;

  case 80: /* aggr_type: MAX  */
#line 484 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = MAXS; }
#line 1921 "yacc_sql.tab.c"
    break;

  case 81: /* aggr_type: MIN  */
#line 485 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = MINS; }
#line 1927 "yacc_sql.tab.c"
    break;

  case 82: /* aggr_type: AVG  */
#line 486 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = AVGS; }
#line 1933 "yacc_sql.tab.c"
    break;

  case 83: /* aggr_type: SUM  */
#line 487 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = SUMS; }
#line 1939 "yacc_sql.tab.c"
    break;

  case 84: /* aggr_type: COUNT  */
#line 488 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = COUNTS; }
#line 1945 "yacc_sql.tab.c"
    break;

  case 86: /* rel_list: COMMA ID rel_list  */
#line 493 "yacc_sql.y"
                        {	
			selects_append_relation(&CONTEXT->selects[CUR_SEL], (yyvsp[-1].string));
		}
#line 1953 "yacc_sql.tab.c"
    break;

  case 89: /* inner_join: INNER JOIN ID ON join_condition join_condition_list  */
#line 504 "yacc_sql.y"
                                                                    {
			Join join;
			join_init(&join, (yyvsp[-3].string), CONTEXT->join_conditions[CUR_SEL], CONTEXT->join_condition_length[CUR_SEL]);
			CONTEXT->joins[CUR_SEL][CONTEXT->join_length[CUR_SEL]++] = join;
			CONTEXT->join_condition_length[CUR_SEL] = 0;
		}
#line 1964 "yacc_sql.tab.c"
    break;

  case 92: /* join_condition_op: AND  */
#line 518 "yacc_sql.y"
                    {
			CONTEXT->join_condition_ops[CUR_SEL][CONTEXT->join_condition_op_length[CUR_SEL]++] = COND_AND;
		}
#line 1972 "yacc_sql.tab.c"
    break;

  case 93: /* join_condition_op: OR  */
#line 521 "yacc_sql.y"
                     {
			CONTEXT->join_condition_ops[CUR_SEL][CONTEXT->join_condition_op_length[CUR_SEL]++] = COND_OR;
		}
#line 1980 "yacc_sql.tab.c"
    break;

  case 94: /* join_condition: exp comOp exp  */
#line 527 "yacc_sql.y"
                              {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->join_condition_length[CUR_SEL]++] = condition;
		}
#line 1990 "yacc_sql.tab.c"
    break;

  case 95: /* join_condition: exp comOp right_sub_select  */
#line 532 "yacc_sql.y"
                                             {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, NULL, &CONTEXT->right_sub_select);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2000 "yacc_sql.tab.c"
    break;

  case 96: /* join_condition: left_sub_select comOp exp  */
#line 537 "yacc_sql.y"
                                            {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, NULL, &CONTEXT->left_sub_select, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2010 "yacc_sql.tab.c"
    break;

  case 97: /* join_condition: left_sub_select comOp right_sub_select  */
#line 542 "yacc_sql.y"
                                                         {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, NULL, &CONTEXT->left_sub_select, 0, NULL, &CONTEXT->right_sub_select);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2020 "yacc_sql.tab.c"
    break;

  case 102: /* condition_op: AND  */
#line 558 "yacc_sql.y"
                    {
			CONTEXT->condition_ops[CUR_SEL][CONTEXT->condition_op_length[CUR_SEL]++] = COND_AND;
		}
#line 2028 "yacc_sql.tab.c"
    break;

  case 103: /* condition_op: OR  */
#line 561 "yacc_sql.y"
                     {
			CONTEXT->condition_ops[CUR_SEL][CONTEXT->condition_op_length[CUR_SEL]++] = COND_OR;
		}
#line 2036 "yacc_sql.tab.c"
    break;

  case 104: /* condition: exp comOp exp  */
#line 566 "yacc_sql.y"
                              {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2046 "yacc_sql.tab.c"
    break;

  case 105: /* condition: exp comOp right_sub_select  */
#line 571 "yacc_sql.y"
                                             {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 1, NULL, &CONTEXT->right_sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2056 "yacc_sql.tab.c"
    break;

  case 106: /* condition: left_sub_select comOp exp  */
#line 576 "yacc_sql.y"
                                            {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 1, NULL, &CONTEXT->left_sub_select, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2066 "yacc_sql.tab.c"
    break;

  case 107: /* condition: left_sub_select comOp right_sub_select  */
#line 581 "yacc_sql.y"
                                                         {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 1, NULL, &CONTEXT->left_sub_select, 1, NULL, &CONTEXT->right_sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2076 "yacc_sql.tab.c"
    break;

  case 108: /* condition: is_exist sub_select  */
#line 586 "yacc_sql.y"
                                      {
			Condition condition;
			condition_init_exists(&condition, (yyvsp[-1].number), &CONTEXT->sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2086 "yacc_sql.tab.c"
    break;

  case 109: /* condition: exp is_in sub_select  */
#line 591 "yacc_sql.y"
                                       {
			Condition condition;
			condition_init_in(&condition, (yyvsp[-1].number), (yyvsp[-2].ast1), &CONTEXT->sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2096 "yacc_sql.tab.c"
    break;

  case 110: /* condition: exp is_in in_pair  */
#line 596 "yacc_sql.y"
                                    {
			Condition condition;
			condition_init_in_exprs(&condition, (yyvsp[-1].number), (yyvsp[-2].ast1), CONTEXT->in_exprs[CUR_SEL], CONTEXT->in_expr_length[CUR_SEL]);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
			CONTEXT->in_expr_length[CUR_SEL] = 0;
		}
#line 2107 "yacc_sql.tab.c"
    break;

  case 112: /* in_expr: exp  */
#line 610 "yacc_sql.y"
                    {
			CONTEXT->in_exprs[CUR_SEL][CONTEXT->in_expr_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 2115 "yacc_sql.tab.c"
    break;

  case 115: /* is_exist: EXISTSS  */
#line 621 "yacc_sql.y"
                        {
			(yyval.number) = 1;
		}
#line 2123 "yacc_sql.tab.c"
    break;

  case 116: /* is_exist: NOT EXISTSS  */
#line 624 "yacc_sql.y"
                              {
			(yyval.number) = 0;
		}
#line 2131 "yacc_sql.tab.c"
    break;

  case 117: /* is_in: INS  */
#line 629 "yacc_sql.y"
                    {
			(yyval.number) = 1;
		}
#line 2139 "yacc_sql.tab.c"
    break;

  case 118: /* is_in: NOT INS  */
#line 632 "yacc_sql.y"
                          {
			(yyval.number) = 0;
		}
#line 2147 "yacc_sql.tab.c"
    break;

  case 119: /* update_select: LBRACE select_body RBRACE  */
#line 638 "yacc_sql.y"
                                          {
			CONTEXT->update_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2157 "yacc_sql.tab.c"
    break;

  case 120: /* sub_select: LBRACE select_body RBRACE  */
#line 646 "yacc_sql.y"
                                          {
			CONTEXT->sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2167 "yacc_sql.tab.c"
    break;

  case 121: /* left_sub_select: LBRACE select_body RBRACE  */
#line 654 "yacc_sql.y"
                                          {
			CONTEXT->left_sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2177 "yacc_sql.tab.c"
    break;

  case 122: /* right_sub_select: LBRACE select_body RBRACE  */
#line 662 "yacc_sql.y"
                                          {
			CONTEXT->right_sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2187 "yacc_sql.tab.c"
    break;

  case 123: /* exp: MINUS exp  */
#line 670 "yacc_sql.y"
                          {
			(yyval.ast1) = new_op_node(MATH_SUB, NULL, (yyvsp[0].ast1));
		}
#line 2195 "yacc_sql.tab.c"
    break;

  case 124: /* exp: exp PLUS exp  */
#line 673 "yacc_sql.y"
                               {
			(yyval.ast1) = new_op_node(MATH_ADD, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2203 "yacc_sql.tab.c"
    break;

  case 125: /* exp: exp MINUS exp  */
#line 676 "yacc_sql.y"
                                {
			(yyval.ast1) = new_op_node(MATH_SUB, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2211 "yacc_sql.tab.c"
    break;

  case 126: /* exp: exp STAR exp  */
#line 679 "yacc_sql.y"
                               {
			(yyval.ast1) = new_op_node(MATH_MUL, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2219 "yacc_sql.tab.c"
    break;

  case 127: /* exp: exp SLASH exp  */
#line 682 "yacc_sql.y"
                                {
			(yyval.ast1) = new_op_node(MATH_DIV, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2227 "yacc_sql.tab.c"
    break;

  case 128: /* exp: LBRACE exp RBRACE  */
#line 685 "yacc_sql.y"
                                    {
			(yyval.ast1) = (yyvsp[-1].ast1);
			(yyval.ast1)->l_brace++;
			(yyval.ast1)->r_brace++;
		}
#line 2237 "yacc_sql.tab.c"
    break;

  case 129: /* exp: value  */
#line 690 "yacc_sql.y"
                        {
			(yyval.ast1) = (yyvsp[0].ast1);
		}
#line 2245 "yacc_sql.tab.c"
    break;

  case 130: /* exp: ID  */
#line 693 "yacc_sql.y"
                     {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			(yyval.ast1) = new_attr_node(&attr);
		}
#line 2255 "yacc_sql.tab.c"
    break;

  case 131: /* exp: ID DOT ID  */
#line 698 "yacc_sql.y"
                            {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			(yyval.ast1) = new_attr_node(&attr);
		}
#line 2265 "yacc_sql.tab.c"
    break;

  case 132: /* exp: aggr_func  */
#line 703 "yacc_sql.y"
                            {
			(yyval.ast1) = (yyvsp[0].ast1);
		}
#line 2273 "yacc_sql.tab.c"
    break;

  case 133: /* comOp: EQ  */
#line 709 "yacc_sql.y"
             { CONTEXT->comp[CUR_SEL] = EQUAL_TO; }
#line 2279 "yacc_sql.tab.c"
    break;

  case 134: /* comOp: LT  */
#line 710 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = LESS_THAN; }
#line 2285 "yacc_sql.tab.c"
    break;

  case 135: /* comOp: GT  */
#line 711 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = GREAT_THAN; }
#line 2291 "yacc_sql.tab.c"
    break;

  case 136: /* comOp: LE  */
#line 712 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = LESS_EQUAL; }
#line 2297 "yacc_sql.tab.c"
    break;

  case 137: /* comOp: GE  */
#line 713 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = GREAT_EQUAL; }
#line 2303 "yacc_sql.tab.c"
    break;

  case 138: /* comOp: NE  */
#line 714 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = NOT_EQUAL; }
#line 2309 "yacc_sql.tab.c"
    break;

  case 139: /* comOp: LIKE  */
#line 715 "yacc_sql.y"
                       { CONTEXT->comp[CUR_SEL] = STR_LIKE; }
#line 2315 "yacc_sql.tab.c"
    break;

  case 140: /* comOp: NOT LIKE  */
#line 716 "yacc_sql.y"
                           { CONTEXT->comp[CUR_SEL] = STR_NOT_LIKE; }
#line 2321 "yacc_sql.tab.c"
    break;

  case 141: /* comOp: ISS  */
#line 717 "yacc_sql.y"
                      { CONTEXT->comp[CUR_SEL] = IS; }
#line 2327 "yacc_sql.tab.c"
    break;

  case 142: /* comOp: ISS NOT  */
#line 718 "yacc_sql.y"
                          { CONTEXT->comp[CUR_SEL] = IS_NOT; }
#line 2333 "yacc_sql.tab.c"
    break;

  case 143: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 723 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2342 "yacc_sql.tab.c"
    break;


#line 2346 "yacc_sql.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 728 "yacc_sql.y"

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
