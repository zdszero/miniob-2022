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


#line 142 "yacc_sql.tab.c"

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
  YYSYMBOL_SET = 25,                       /* SET  */
  YYSYMBOL_ON = 26,                        /* ON  */
  YYSYMBOL_LOAD = 27,                      /* LOAD  */
  YYSYMBOL_DATA = 28,                      /* DATA  */
  YYSYMBOL_INFILE = 29,                    /* INFILE  */
  YYSYMBOL_INNER = 30,                     /* INNER  */
  YYSYMBOL_JOIN = 31,                      /* JOIN  */
  YYSYMBOL_SEMICOLON = 32,                 /* SEMICOLON  */
  YYSYMBOL_DOT = 33,                       /* DOT  */
  YYSYMBOL_COMMA = 34,                     /* COMMA  */
  YYSYMBOL_LBRACE = 35,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 36,                    /* RBRACE  */
  YYSYMBOL_INT_T = 37,                     /* INT_T  */
  YYSYMBOL_STRING_T = 38,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 39,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 40,                    /* DATE_T  */
  YYSYMBOL_EQ = 41,                        /* EQ  */
  YYSYMBOL_LT = 42,                        /* LT  */
  YYSYMBOL_GT = 43,                        /* GT  */
  YYSYMBOL_LE = 44,                        /* LE  */
  YYSYMBOL_GE = 45,                        /* GE  */
  YYSYMBOL_NE = 46,                        /* NE  */
  YYSYMBOL_LIKE = 47,                      /* LIKE  */
  YYSYMBOL_NOT = 48,                       /* NOT  */
  YYSYMBOL_MAX = 49,                       /* MAX  */
  YYSYMBOL_MIN = 50,                       /* MIN  */
  YYSYMBOL_AVG = 51,                       /* AVG  */
  YYSYMBOL_SUM = 52,                       /* SUM  */
  YYSYMBOL_COUNT = 53,                     /* COUNT  */
  YYSYMBOL_SLASH = 54,                     /* SLASH  */
  YYSYMBOL_PLUS = 55,                      /* PLUS  */
  YYSYMBOL_MINUS = 56,                     /* MINUS  */
  YYSYMBOL_NUMBER = 57,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 58,                     /* FLOAT  */
  YYSYMBOL_ID = 59,                        /* ID  */
  YYSYMBOL_PATH = 60,                      /* PATH  */
  YYSYMBOL_SSS = 61,                       /* SSS  */
  YYSYMBOL_STAR = 62,                      /* STAR  */
  YYSYMBOL_STRING_V = 63,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 64,                  /* $accept  */
  YYSYMBOL_commands = 65,                  /* commands  */
  YYSYMBOL_command = 66,                   /* command  */
  YYSYMBOL_exit = 67,                      /* exit  */
  YYSYMBOL_help = 68,                      /* help  */
  YYSYMBOL_sync = 69,                      /* sync  */
  YYSYMBOL_begin = 70,                     /* begin  */
  YYSYMBOL_commit = 71,                    /* commit  */
  YYSYMBOL_rollback = 72,                  /* rollback  */
  YYSYMBOL_drop_table = 73,                /* drop_table  */
  YYSYMBOL_show_tables = 74,               /* show_tables  */
  YYSYMBOL_desc_table = 75,                /* desc_table  */
  YYSYMBOL_create_index = 76,              /* create_index  */
  YYSYMBOL_drop_index = 77,                /* drop_index  */
  YYSYMBOL_show_index = 78,                /* show_index  */
  YYSYMBOL_create_table = 79,              /* create_table  */
  YYSYMBOL_attr_def_list = 80,             /* attr_def_list  */
  YYSYMBOL_attr_def = 81,                  /* attr_def  */
  YYSYMBOL_number = 82,                    /* number  */
  YYSYMBOL_type = 83,                      /* type  */
  YYSYMBOL_ID_get = 84,                    /* ID_get  */
  YYSYMBOL_insert = 85,                    /* insert  */
  YYSYMBOL_insert_pair = 86,               /* insert_pair  */
  YYSYMBOL_insert_expr = 87,               /* insert_expr  */
  YYSYMBOL_insert_expr_list = 88,          /* insert_expr_list  */
  YYSYMBOL_insert_pair_list = 89,          /* insert_pair_list  */
  YYSYMBOL_value = 90,                     /* value  */
  YYSYMBOL_delete = 91,                    /* delete  */
  YYSYMBOL_update = 92,                    /* update  */
  YYSYMBOL_select = 93,                    /* select  */
  YYSYMBOL_select_expr = 94,               /* select_expr  */
  YYSYMBOL_select_exprs = 95,              /* select_exprs  */
  YYSYMBOL_aggr_func = 96,                 /* aggr_func  */
  YYSYMBOL_aggr_type = 97,                 /* aggr_type  */
  YYSYMBOL_rel_list = 98,                  /* rel_list  */
  YYSYMBOL_inner_join_list = 99,           /* inner_join_list  */
  YYSYMBOL_inner_join = 100,               /* inner_join  */
  YYSYMBOL_join_condition_list = 101,      /* join_condition_list  */
  YYSYMBOL_join_condition = 102,           /* join_condition  */
  YYSYMBOL_where = 103,                    /* where  */
  YYSYMBOL_condition_list = 104,           /* condition_list  */
  YYSYMBOL_condition = 105,                /* condition  */
  YYSYMBOL_exp = 106,                      /* exp  */
  YYSYMBOL_comOp = 107,                    /* comOp  */
  YYSYMBOL_load_data = 108                 /* load_data  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYLAST   181

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  204

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   318


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
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   126,   126,   128,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   153,   158,   163,   169,   175,   181,   187,   193,
     199,   206,   214,   221,   228,   234,   236,   240,   246,   254,
     257,   258,   259,   260,   263,   271,   277,   284,   289,   291,
     294,   296,   299,   304,   309,   318,   328,   337,   356,   361,
     364,   369,   371,   375,   382,   389,   399,   400,   401,   402,
     403,   406,   408,   413,   415,   419,   427,   429,   433,   440,
     442,   444,   446,   449,   457,   460,   463,   466,   469,   472,
     477,   480,   485,   493,   494,   495,   496,   497,   498,   499,
     500,   504
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
  "EXIT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD",
  "DATA", "INFILE", "INNER", "JOIN", "SEMICOLON", "DOT", "COMMA", "LBRACE",
  "RBRACE", "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "EQ", "LT", "GT",
  "LE", "GE", "NE", "LIKE", "NOT", "MAX", "MIN", "AVG", "SUM", "COUNT",
  "SLASH", "PLUS", "MINUS", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR",
  "STRING_V", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "drop_index", "show_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "insert",
  "insert_pair", "insert_expr", "insert_expr_list", "insert_pair_list",
  "value", "delete", "update", "select", "select_expr", "select_exprs",
  "aggr_func", "aggr_type", "rel_list", "inner_join_list", "inner_join",
  "join_condition_list", "join_condition", "where", "condition_list",
  "condition", "exp", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-99)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -99,     1,   -99,    59,    82,   -27,   -52,    -4,   -11,    13,
      24,   -12,    36,    54,    60,    61,    62,    63,   -99,   -99,
     -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,
     -99,   -99,   -99,   -99,   -99,   -99,   -99,    37,    38,    39,
      41,    -8,   -99,   -99,   -99,   -99,   -99,    -8,   -99,   -99,
      66,   -99,   -99,   -99,    67,   -99,    69,   -17,    70,    73,
      84,   -99,    48,    49,    85,   -99,   -99,   -99,   -99,   -99,
      80,    76,    86,    83,    87,     0,   -10,    55,   -27,    94,
      -1,    -8,    -8,    -8,    -8,   -99,   -99,    58,    74,    95,
      64,    65,    68,    71,   -99,   -99,   -99,   -99,    67,    72,
      52,    88,   -99,   -10,   -10,   -99,    89,    93,    -8,    90,
      79,   109,   -99,    98,    40,    99,   -99,   101,    77,   -99,
     -99,   -99,    -8,   103,   114,    28,   -99,     2,   128,    68,
     104,   -99,   -99,   -99,   -99,   106,    91,    92,   112,   107,
     105,   -17,    93,   113,    -8,   -99,   -99,   -99,   -99,   -99,
     -99,   -99,   -99,    97,    -8,    95,    96,    98,   115,   108,
     110,   101,   117,    95,   112,   -99,    -8,   116,   103,   -99,
     114,   -99,   -17,   121,   124,   -99,   -99,   -99,   122,   129,
     -99,   111,   130,   -99,   105,   -99,   -99,   -99,   -99,   -99,
     -99,   -99,   123,   -99,   -99,    -8,   136,    28,    -8,   -99,
      -8,   136,   -17,   -99
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,    19,     0,     0,     0,
       0,     0,    66,    67,    68,    69,    70,     0,    52,    53,
      91,    54,    58,    90,    61,    60,     0,    59,     0,     0,
       0,    24,     0,     0,     0,    25,    26,    27,    23,    22,
       0,     0,     0,     0,     0,     0,    84,     0,     0,     0,
       0,     0,     0,     0,     0,    30,    29,     0,     0,    79,
       0,     0,     0,     0,    28,    32,    89,    92,    61,     0,
       0,     0,    88,    85,    86,    87,     0,     0,     0,     0,
       0,     0,    44,    35,     0,     0,    62,    71,     0,    63,
      65,    33,     0,    50,    81,     0,    55,     0,     0,     0,
       0,    40,    41,    42,    43,    38,     0,     0,    73,     0,
      48,    47,     0,     0,     0,    80,    93,    94,    95,    96,
      97,    98,    99,     0,     0,    79,     0,    35,     0,     0,
       0,    71,     0,    79,    73,    64,     0,     0,    50,    45,
      81,   100,    83,     0,     0,    36,    34,    39,     0,     0,
      72,     0,     0,    74,    48,    46,    51,    82,    56,   101,
      37,    31,     0,    57,    49,     0,    76,     0,     0,    75,
       0,    76,    78,    77
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,
     -99,   -99,   -99,   -99,   -99,   -99,     6,    35,   -99,   -99,
     -99,   -99,    25,     3,   -18,     4,    44,   -99,   -99,   -99,
     100,    75,   -99,   -99,     7,    10,   -99,   -26,   -22,   -98,
       9,    33,   -41,   -16,   -99
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,   130,   113,   178,   135,
     114,    32,   123,   140,   167,   143,    53,    33,    34,    35,
      54,    79,    55,    56,   138,   163,   164,   199,   196,   109,
     145,   124,    57,   154,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      75,     2,    59,    60,     3,     4,    76,    58,    41,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    61,    42,    43,    44,    45,    46,    41,    17,    47,
      48,    49,    50,    62,    51,    52,    96,    81,    82,    83,
     102,   103,   104,   105,    81,    84,    63,    64,    47,    48,
      49,    50,    84,    51,    81,    82,    83,   173,   100,    48,
      49,   101,    84,    51,    37,   182,    38,   125,    65,   146,
     147,   148,   149,   150,   151,   152,   153,   131,   132,   133,
     134,   141,    81,    82,    83,   118,    66,    39,   119,    40,
      84,    70,    67,    68,    69,   107,    71,    72,    73,    77,
      74,    78,    85,   125,    80,    86,    87,    88,    89,    91,
      90,    92,    93,   172,    97,    94,    99,   106,   108,    95,
     127,   121,   126,   110,   120,   141,   111,   112,   122,   128,
     115,   117,   129,   156,   136,   137,   139,   142,   144,   166,
     158,   159,   162,   165,   171,   169,   179,   176,   181,   195,
     160,   161,   185,   188,   197,   174,   189,   197,   190,   202,
     198,   191,   193,   175,   157,   177,   194,   168,   180,   184,
     192,   155,   186,   116,   183,   203,   201,   170,    98,   187,
       0,   200
};

static const yytype_int16 yycheck[] =
{
      41,     0,     6,     7,     3,     4,    47,    59,    35,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    32,    49,    50,    51,    52,    53,    35,    27,    56,
      57,    58,    59,    20,    61,    62,    36,    54,    55,    56,
      81,    82,    83,    84,    54,    62,    22,    59,    56,    57,
      58,    59,    62,    61,    54,    55,    56,   155,    59,    57,
      58,    62,    62,    61,     5,   163,     7,   108,    32,    41,
      42,    43,    44,    45,    46,    47,    48,    37,    38,    39,
      40,   122,    54,    55,    56,    33,    32,     5,    36,     7,
      62,    28,    32,    32,    32,    21,    59,    59,    59,    33,
      59,    34,    32,   144,    35,    32,    22,    59,    59,    29,
      25,    35,    26,   154,    59,    32,    22,    59,    23,    32,
      41,    32,    32,    59,    36,   166,    61,    59,    35,    20,
      59,    59,    34,     5,    35,    34,    59,    34,    24,    34,
      36,    35,    30,    36,    47,    32,    36,    32,    31,    26,
      59,    59,    36,    32,   195,    59,    32,   198,    36,   200,
      24,    32,    32,   157,   129,    57,   184,   142,   161,   166,
      59,   127,   168,    98,   164,   201,   198,   144,    78,   170,
      -1,   197
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    65,     0,     3,     4,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    27,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    85,    91,    92,    93,   108,     5,     7,     5,
       7,    35,    49,    50,    51,    52,    53,    56,    57,    58,
      59,    61,    62,    90,    94,    96,    97,   106,    59,     6,
       7,    32,    20,    22,    59,    32,    32,    32,    32,    32,
      28,    59,    59,    59,    59,   106,   106,    33,    34,    95,
      35,    54,    55,    56,    62,    32,    32,    22,    59,    59,
      25,    29,    35,    26,    32,    32,    36,    59,    94,    22,
      59,    62,   106,   106,   106,   106,    59,    21,    23,   103,
      59,    61,    59,    81,    84,    59,    95,    59,    33,    36,
      36,    32,    35,    86,   105,   106,    32,    41,    20,    34,
      80,    37,    38,    39,    40,    83,    35,    34,    98,    59,
      87,   106,    34,    89,    24,   104,    41,    42,    43,    44,
      45,    46,    47,    48,   107,    90,     5,    81,    36,    35,
      59,    59,    30,    99,   100,    36,    34,    88,    86,    32,
     105,    47,   106,   103,    59,    80,    32,    57,    82,    36,
      98,    31,   103,    99,    87,    36,    89,   104,    32,    32,
      36,    32,    59,    32,    88,    26,   102,   106,    24,   101,
     107,   102,   106,   101
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    64,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    80,    81,    81,    82,
      83,    83,    83,    83,    84,    85,    86,    87,    88,    88,
      89,    89,    90,    90,    90,    91,    92,    93,    94,    94,
      94,    95,    95,    96,    96,    96,    97,    97,    97,    97,
      97,    98,    98,    99,    99,   100,   101,   101,   102,   103,
     103,   104,   104,   105,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   107,   107,   107,   107,   107,   107,   107,
     107,   108
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,     9,     4,     5,     8,     0,     3,     5,     2,     1,
       1,     1,     1,     1,     1,     7,     4,     1,     0,     3,
       0,     3,     1,     1,     1,     5,     8,     9,     1,     1,
       1,     0,     3,     4,     6,     4,     1,     1,     1,     1,
       1,     0,     3,     0,     2,     6,     0,     3,     3,     0,
       3,     0,     3,     3,     2,     3,     3,     3,     3,     3,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       2,     8
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
#line 153 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1388 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 158 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1396 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 163 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1404 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 169 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1412 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 175 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1420 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 181 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1428 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 187 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1437 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 193 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1445 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 199 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1454 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 207 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1463 "yacc_sql.tab.c"
    break;

  case 32: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 215 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1472 "yacc_sql.tab.c"
    break;

  case 33: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 222 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1481 "yacc_sql.tab.c"
    break;

  case 34: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 229 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
		}
#line 1490 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 241 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1500 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type  */
#line 247 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1510 "yacc_sql.tab.c"
    break;

  case 39: /* number: NUMBER  */
#line 254 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1516 "yacc_sql.tab.c"
    break;

  case 40: /* type: INT_T  */
#line 257 "yacc_sql.y"
                           { (yyval.number)=INTS;   }
#line 1522 "yacc_sql.tab.c"
    break;

  case 41: /* type: STRING_T  */
#line 258 "yacc_sql.y"
                           { (yyval.number)=CHARS;  }
#line 1528 "yacc_sql.tab.c"
    break;

  case 42: /* type: FLOAT_T  */
#line 259 "yacc_sql.y"
                           { (yyval.number)=FLOATS; }
#line 1534 "yacc_sql.tab.c"
    break;

  case 43: /* type: DATE_T  */
#line 260 "yacc_sql.y"
                           { (yyval.number)=DATES;  }
#line 1540 "yacc_sql.tab.c"
    break;

  case 44: /* ID_get: ID  */
#line 263 "yacc_sql.y"
                   {
			char *temp=(yyvsp[0].string); 
			snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
		}
#line 1549 "yacc_sql.tab.c"
    break;

  case 45: /* insert: INSERT INTO ID VALUES insert_pair insert_pair_list SEMICOLON  */
#line 271 "yacc_sql.y"
                                                                 {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
#line 1558 "yacc_sql.tab.c"
    break;

  case 46: /* insert_pair: LBRACE insert_expr insert_expr_list RBRACE  */
#line 277 "yacc_sql.y"
                                                           {
			insert_append_exprs(&CONTEXT->ssql->sstr.insertion, CONTEXT->exprs, CONTEXT->expr_length);
			CONTEXT->expr_length = 0;
		}
#line 1567 "yacc_sql.tab.c"
    break;

  case 47: /* insert_expr: exp  */
#line 284 "yacc_sql.y"
                    {
			CONTEXT->exprs[CONTEXT->expr_length++] = (yyvsp[0].ast1);
		}
#line 1575 "yacc_sql.tab.c"
    break;

  case 52: /* value: NUMBER  */
#line 299 "yacc_sql.y"
           {
			Value value;
			value_init_integer(&value, (yyvsp[0].number));
			(yyval.value1) = new_value_node(&value);
		}
#line 1585 "yacc_sql.tab.c"
    break;

  case 53: /* value: FLOAT  */
#line 304 "yacc_sql.y"
           {
			Value value;
			value_init_float(&value, (yyvsp[0].floats));
			(yyval.value1) = new_value_node(&value);
		}
#line 1595 "yacc_sql.tab.c"
    break;

  case 54: /* value: SSS  */
#line 309 "yacc_sql.y"
         {
			Value value;
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&value, (yyvsp[0].string));
			(yyval.value1) = new_value_node(&value);
		}
#line 1606 "yacc_sql.tab.c"
    break;

  case 55: /* delete: DELETE FROM ID where SEMICOLON  */
#line 319 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1618 "yacc_sql.tab.c"
    break;

  case 56: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 329 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].value1), 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1629 "yacc_sql.tab.c"
    break;

  case 57: /* select: SELECT select_expr select_exprs FROM ID rel_list inner_join_list where SEMICOLON  */
#line 338 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));
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
#line 1649 "yacc_sql.tab.c"
    break;

  case 58: /* select_expr: STAR  */
#line 356 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		CONTEXT->exprs[CONTEXT->expr_length++] = new_attr_node(&attr);
	}
#line 1659 "yacc_sql.tab.c"
    break;

  case 59: /* select_expr: exp  */
#line 361 "yacc_sql.y"
              {
		CONTEXT->exprs[CONTEXT->expr_length++] = (yyvsp[0].ast1);
	}
#line 1667 "yacc_sql.tab.c"
    break;

  case 60: /* select_expr: aggr_func  */
#line 364 "yacc_sql.y"
                    {
		CONTEXT->exprs[CONTEXT->expr_length++] = (yyvsp[0].ast1);
	}
#line 1675 "yacc_sql.tab.c"
    break;

  case 63: /* aggr_func: aggr_type LBRACE ID RBRACE  */
#line 375 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type, 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 1687 "yacc_sql.tab.c"
    break;

  case 64: /* aggr_func: aggr_type LBRACE ID DOT ID RBRACE  */
#line 382 "yacc_sql.y"
                                                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type, 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 1699 "yacc_sql.tab.c"
    break;

  case 65: /* aggr_func: aggr_type LBRACE STAR RBRACE  */
#line 389 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type, 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 1711 "yacc_sql.tab.c"
    break;

  case 66: /* aggr_type: MAX  */
#line 399 "yacc_sql.y"
                        { CONTEXT->aggr_type = MAXS; }
#line 1717 "yacc_sql.tab.c"
    break;

  case 67: /* aggr_type: MIN  */
#line 400 "yacc_sql.y"
                        { CONTEXT->aggr_type = MINS; }
#line 1723 "yacc_sql.tab.c"
    break;

  case 68: /* aggr_type: AVG  */
#line 401 "yacc_sql.y"
                        { CONTEXT->aggr_type = AVGS; }
#line 1729 "yacc_sql.tab.c"
    break;

  case 69: /* aggr_type: SUM  */
#line 402 "yacc_sql.y"
                        { CONTEXT->aggr_type = SUMS; }
#line 1735 "yacc_sql.tab.c"
    break;

  case 70: /* aggr_type: COUNT  */
#line 403 "yacc_sql.y"
                        { CONTEXT->aggr_type = COUNTS; }
#line 1741 "yacc_sql.tab.c"
    break;

  case 72: /* rel_list: COMMA ID rel_list  */
#line 408 "yacc_sql.y"
                        {	
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		}
#line 1749 "yacc_sql.tab.c"
    break;

  case 75: /* inner_join: INNER JOIN ID ON join_condition join_condition_list  */
#line 419 "yacc_sql.y"
                                                                    {
			Join join;
			join_init(&join, (yyvsp[-3].string), CONTEXT->join_conditions, CONTEXT->join_condition_length);
			CONTEXT->joins[CONTEXT->join_length++] = join;
			CONTEXT->join_condition_length = 0;
		}
#line 1760 "yacc_sql.tab.c"
    break;

  case 78: /* join_condition: exp comOp exp  */
#line 433 "yacc_sql.y"
                              {
			Condition condition;
			condition_init(&condition, CONTEXT->comp, (yyvsp[-2].ast1), (yyvsp[0].ast1));
			CONTEXT->join_conditions[CONTEXT->join_condition_length++] = condition;
		}
#line 1770 "yacc_sql.tab.c"
    break;

  case 83: /* condition: exp comOp exp  */
#line 449 "yacc_sql.y"
                              {
			Condition condition;
			condition_init(&condition, CONTEXT->comp, (yyvsp[-2].ast1), (yyvsp[0].ast1));
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 1780 "yacc_sql.tab.c"
    break;

  case 84: /* exp: MINUS exp  */
#line 457 "yacc_sql.y"
                          {
			(yyval.ast1) = new_op_node(MATH_SUB, NULL, (yyvsp[0].ast1));
		}
#line 1788 "yacc_sql.tab.c"
    break;

  case 85: /* exp: exp PLUS exp  */
#line 460 "yacc_sql.y"
                               {
			(yyval.ast1) = new_op_node(MATH_ADD, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 1796 "yacc_sql.tab.c"
    break;

  case 86: /* exp: exp MINUS exp  */
#line 463 "yacc_sql.y"
                                {
			(yyval.ast1) = new_op_node(MATH_SUB, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 1804 "yacc_sql.tab.c"
    break;

  case 87: /* exp: exp STAR exp  */
#line 466 "yacc_sql.y"
                               {
			(yyval.ast1) = new_op_node(MATH_MUL, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 1812 "yacc_sql.tab.c"
    break;

  case 88: /* exp: exp SLASH exp  */
#line 469 "yacc_sql.y"
                                {
			(yyval.ast1) = new_op_node(MATH_DIV, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 1820 "yacc_sql.tab.c"
    break;

  case 89: /* exp: LBRACE exp RBRACE  */
#line 472 "yacc_sql.y"
                                    {
			(yyval.ast1) = (yyvsp[-1].ast1);
			(yyval.ast1)->l_brace++;
			(yyval.ast1)->r_brace++;
		}
#line 1830 "yacc_sql.tab.c"
    break;

  case 90: /* exp: value  */
#line 477 "yacc_sql.y"
                        {
			(yyval.ast1) = (yyvsp[0].value1);
		}
#line 1838 "yacc_sql.tab.c"
    break;

  case 91: /* exp: ID  */
#line 480 "yacc_sql.y"
                     {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			(yyval.ast1) = new_attr_node(&attr);
		}
#line 1848 "yacc_sql.tab.c"
    break;

  case 92: /* exp: ID DOT ID  */
#line 485 "yacc_sql.y"
                            {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			(yyval.ast1) = new_attr_node(&attr);
		}
#line 1858 "yacc_sql.tab.c"
    break;

  case 93: /* comOp: EQ  */
#line 493 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 1864 "yacc_sql.tab.c"
    break;

  case 94: /* comOp: LT  */
#line 494 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 1870 "yacc_sql.tab.c"
    break;

  case 95: /* comOp: GT  */
#line 495 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 1876 "yacc_sql.tab.c"
    break;

  case 96: /* comOp: LE  */
#line 496 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 1882 "yacc_sql.tab.c"
    break;

  case 97: /* comOp: GE  */
#line 497 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 1888 "yacc_sql.tab.c"
    break;

  case 98: /* comOp: NE  */
#line 498 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 1894 "yacc_sql.tab.c"
    break;

  case 99: /* comOp: LIKE  */
#line 499 "yacc_sql.y"
                       { CONTEXT->comp = STR_LIKE; }
#line 1900 "yacc_sql.tab.c"
    break;

  case 100: /* comOp: NOT LIKE  */
#line 500 "yacc_sql.y"
                           { CONTEXT->comp = STR_NOT_LIKE; }
#line 1906 "yacc_sql.tab.c"
    break;

  case 101: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 505 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 1915 "yacc_sql.tab.c"
    break;


#line 1919 "yacc_sql.tab.c"

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

#line 510 "yacc_sql.y"

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
