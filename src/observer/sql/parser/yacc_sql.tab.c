/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

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


#line 171 "yacc_sql.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CREATE = 258,
    DROP = 259,
    TABLE = 260,
    TABLES = 261,
    INDEX = 262,
    SELECT = 263,
    DESC = 264,
    SHOW = 265,
    SYNC = 266,
    INSERT = 267,
    DELETE = 268,
    UPDATE = 269,
    TRX_BEGIN = 270,
    TRX_COMMIT = 271,
    TRX_ROLLBACK = 272,
    HELP = 273,
    EXIT = 274,
    INTO = 275,
    VALUES = 276,
    FROM = 277,
    WHERE = 278,
    AND = 279,
    OR = 280,
    SET = 281,
    ON = 282,
    LOAD = 283,
    DATA = 284,
    INFILE = 285,
    INNER = 286,
    JOIN = 287,
    UNIQUE = 288,
    ORDER = 289,
    BY = 290,
    ASC = 291,
    GROUP = 292,
    HAVING = 293,
    SEMICOLON = 294,
    DOT = 295,
    COMMA = 296,
    LBRACE = 297,
    RBRACE = 298,
    INT_T = 299,
    STRING_T = 300,
    FLOAT_T = 301,
    DATE_T = 302,
    TEXT_T = 303,
    NULL_T = 304,
    NULLABLE = 305,
    EQ = 306,
    LT = 307,
    GT = 308,
    LE = 309,
    GE = 310,
    NE = 311,
    LIKE = 312,
    NOT = 313,
    ISS = 314,
    EXISTSS = 315,
    INS = 316,
    MAX = 317,
    MIN = 318,
    AVG = 319,
    SUM = 320,
    COUNT = 321,
    SLASH = 322,
    PLUS = 323,
    MINUS = 324,
    NUMBER = 325,
    FLOAT = 326,
    ID = 327,
    PATH = 328,
    SSS = 329,
    STAR = 330,
    STRING_V = 331
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 124 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
	struct ast *ast1;
  char *string;
  int number;
  float floats;
	char *position;
	int order_policy1;

#line 312 "yacc_sql.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYLAST   351

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  158
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  306

#define YYUNDEFTOK  2
#define YYMAXUTOK   331


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   162,   162,   164,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   189,   194,   199,   205,   211,   217,   223,   229,
     235,   242,   246,   253,   258,   260,   264,   271,   278,   284,
     286,   290,   296,   304,   307,   310,   315,   318,   319,   320,
     321,   322,   325,   333,   339,   346,   351,   353,   356,   358,
     361,   366,   371,   377,   385,   397,   406,   411,   418,   420,
     425,   433,   447,   449,   456,   458,   462,   467,   469,   472,
     474,   478,   485,   487,   491,   494,   497,   503,   509,   514,
     519,   521,   525,   532,   539,   549,   550,   551,   552,   553,
     556,   558,   563,   565,   569,   577,   579,   583,   586,   592,
     597,   602,   607,   614,   616,   618,   620,   623,   626,   631,
     636,   641,   646,   651,   656,   661,   671,   675,   680,   682,
     686,   689,   694,   697,   703,   711,   719,   727,   735,   738,
     741,   744,   747,   750,   755,   758,   763,   768,   774,   775,
     776,   777,   778,   779,   780,   781,   782,   783,   787
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CREATE", "DROP", "TABLE", "TABLES",
  "INDEX", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "HELP", "EXIT", "INTO",
  "VALUES", "FROM", "WHERE", "AND", "OR", "SET", "ON", "LOAD", "DATA",
  "INFILE", "INNER", "JOIN", "UNIQUE", "ORDER", "BY", "ASC", "GROUP",
  "HAVING", "SEMICOLON", "DOT", "COMMA", "LBRACE", "RBRACE", "INT_T",
  "STRING_T", "FLOAT_T", "DATE_T", "TEXT_T", "NULL_T", "NULLABLE", "EQ",
  "LT", "GT", "LE", "GE", "NE", "LIKE", "NOT", "ISS", "EXISTSS", "INS",
  "MAX", "MIN", "AVG", "SUM", "COUNT", "SLASH", "PLUS", "MINUS", "NUMBER",
  "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index", "index_id",
  "id_list", "drop_index", "show_index", "create_table", "attr_def_list",
  "attr_def", "nullable", "number", "type", "ID_get", "insert",
  "insert_pair", "insert_expr", "insert_expr_list", "insert_pair_list",
  "value", "delete", "update", "update_pair", "update_pair_list", "select",
  "select_body", "having", "group_by", "group_by_expr",
  "group_by_expr_list", "order_by", "order_attr", "order_attr_list",
  "order_policy", "begin_select", "select_expr", "select_exprs",
  "aggr_func", "aggr_type", "rel_list", "inner_join_list", "inner_join",
  "join_condition_list", "join_condition_op", "join_condition", "where",
  "condition_list", "condition_op", "condition", "in_pair", "in_expr",
  "in_expr_list", "is_exist", "is_in", "update_select", "sub_select",
  "left_sub_select", "right_sub_select", "exp", "comOp", "load_data", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331
};
# endif

#define YYPACT_NINF (-258)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -258,   264,  -258,     8,    46,  -258,   -47,    29,   -28,    26,
      52,    -3,    55,    56,    57,    58,    59,    71,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,    62,    44,  -258,    13,
      30,    96,    39,    40,    78,    81,    99,  -258,    50,    51,
      98,  -258,  -258,  -258,  -258,  -258,    95,  -258,   -32,  -258,
    -258,  -258,  -258,  -258,  -258,   -32,  -258,  -258,    86,  -258,
    -258,  -258,    90,  -258,    87,   -48,    91,   105,    63,    97,
     103,  -258,  -258,    66,   124,   111,    75,   101,   -20,   -61,
      77,    44,   133,   -46,   -32,   -32,   -32,   -32,   115,   118,
     146,  -258,  -258,   152,   150,    88,   154,   143,   155,   175,
    -258,  -258,    90,   125,    47,   156,  -258,   -61,   -61,  -258,
    -258,   157,    35,   158,   129,  -258,   -32,   167,     1,   153,
    -258,    37,   173,   113,   242,  -258,   114,    75,   111,   221,
    -258,   191,   164,  -258,  -258,   115,   187,  -258,  -258,  -258,
    -258,  -258,   -42,   165,   197,   199,   -48,   150,   203,   200,
    -258,  -258,  -258,  -258,    88,   240,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,   208,   198,   140,    -5,  -258,   215,
     140,     1,  -258,   -48,   155,   227,   212,   213,   238,   228,
     157,   231,  -258,   237,   245,  -258,   247,   165,   -32,   246,
     167,  -258,  -258,    37,   248,  -258,  -258,     1,  -258,   -48,
    -258,     1,  -258,  -258,  -258,   -48,   259,  -258,  -258,   251,
     191,   272,   111,   238,  -258,  -258,  -258,  -258,   235,   165,
     263,   247,   199,  -258,  -258,  -258,  -258,   265,   266,   -48,
    -258,  -258,  -258,   241,   275,  -258,  -258,   271,   247,   276,
     273,  -258,  -258,   -32,   277,   291,   284,   283,  -258,  -258,
    -258,   285,   266,  -258,   189,   -32,   -32,   288,  -258,  -258,
      67,   113,   166,   282,   -48,   166,   290,  -258,  -258,  -258,
    -258,   189,   140,   140,   -32,  -258,   -32,   -32,    67,  -258,
     -48,  -258,   -48,   282,   -48,   286,     9,  -258,  -258,   -32,
    -258,  -258,  -258,  -258,   286,  -258
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    87,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,     0,     0,    19,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,    25,    26,    27,    23,    22,     0,    70,     0,    63,
      95,    96,    97,    98,    99,     0,    60,    61,   145,    62,
      88,   144,    90,   147,     0,    89,     0,     0,     0,     0,
       0,    30,    29,     0,     0,   113,     0,     0,     0,   138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    36,     0,     0,     0,     0,     0,    68,     0,
     143,   146,    90,     0,     0,     0,   142,   139,   140,   141,
      52,    39,     0,     0,     0,    37,     0,    58,     0,     0,
     130,   115,     0,     0,     0,    64,     0,     0,   113,     0,
      91,   100,     0,    92,    94,     0,     0,    47,    48,    49,
      50,    51,    43,     0,     0,    56,    55,     0,     0,     0,
     131,   117,   118,   114,     0,     0,   123,   148,   149,   150,
     151,   152,   153,   154,     0,   156,     0,     0,   132,     0,
       0,     0,    67,    66,    68,     0,     0,     0,   102,     0,
      39,     0,    44,     0,    42,    33,    34,     0,     0,     0,
      58,    53,   136,   115,     0,   155,   157,     0,   122,   121,
     133,     0,   125,   124,   120,   119,     0,    69,    65,     0,
     100,     0,   113,   102,    93,    40,    38,    45,     0,     0,
       0,    34,    56,    54,    59,   116,   135,     0,   128,   127,
     134,   158,   101,     0,    74,   103,    46,     0,    34,     0,
       0,    57,   137,     0,     0,     0,     0,    72,    41,    35,
      31,     0,   128,   126,     0,     0,     0,    79,    32,   129,
     105,     0,     0,    77,    76,     0,     0,    71,   107,   108,
     104,     0,     0,     0,     0,    75,     0,     0,   105,   112,
     111,   110,   109,    77,    73,    82,    84,   106,    78,     0,
      80,    86,    85,    81,    82,    83
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -185,  -226,  -258,  -258,  -258,   136,   183,
    -258,  -258,  -258,  -258,  -258,   172,   132,   100,   131,  -258,
    -258,  -258,   196,   151,  -258,     0,  -258,  -258,    53,    41,
    -258,    42,    32,  -258,  -258,   249,   226,  -258,  -258,   119,
     120,  -258,    54,  -258,    64,  -134,   141,  -258,   182,  -258,
      94,    89,  -258,  -258,  -258,   169,  -257,  -178,   -37,  -131,
    -258
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   196,   230,    29,    30,    31,   146,   121,
     194,   247,   152,   122,    32,   127,   155,   199,   158,    71,
      33,    34,   108,   138,    35,   204,   267,   257,   273,   285,
     277,   295,   300,   303,    37,    72,    92,    73,    74,   188,
     222,   223,   280,   281,   270,   106,   163,   164,   131,   212,
     238,   254,   132,   179,   182,   166,   133,   208,    88,   176,
      38
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      75,    36,   214,   180,   185,   250,    94,   271,   192,     5,
      58,    47,   231,    39,    97,    40,   193,    59,   301,    94,
      95,    96,   259,   110,   271,    44,   114,    97,    89,   115,
      60,    61,    62,    63,    64,    45,    46,    65,    66,    67,
      68,    41,    69,    58,   248,   302,    48,    94,    95,    96,
      59,    42,   205,    43,    75,    97,   210,   116,   117,   118,
     119,   161,   162,    60,    61,    62,    63,    64,   134,    50,
      65,    66,    67,    68,    49,    69,    94,    95,    96,   147,
     148,   149,   150,   151,    97,    76,    58,   142,   244,   156,
     143,   278,   279,    59,    51,    52,    53,    54,    55,   183,
      56,    57,    77,    78,   289,   291,    60,    61,    62,    63,
      64,    79,    80,    65,    66,    67,    68,    81,    69,    70,
      82,    83,    84,    85,    86,    87,    90,   134,   159,    93,
     128,    91,    99,    98,   105,   100,   101,    59,   103,   209,
     282,   283,   102,   215,   286,   104,   129,   107,   130,   111,
      60,    61,    62,    63,    64,   113,   181,    65,    66,    67,
      68,   156,    69,    59,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   124,   239,   109,    60,    61,    62,    63,
      64,   216,   207,    65,    66,    67,    68,   120,    69,    59,
     123,   125,   126,   135,   136,   139,   137,   141,   145,   144,
     153,   154,    60,    61,    62,    63,    64,   237,   157,    65,
      66,    67,    68,   160,    69,   165,   239,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   186,   272,   274,   275,
     191,   128,   187,    94,    95,    96,   189,   195,    59,   197,
     198,    97,   201,   202,   272,   290,   292,   274,     5,   294,
     296,    60,    61,    62,    63,    64,   206,   211,    65,    66,
      67,    68,   296,    69,     2,   205,   218,     3,     4,   221,
     226,   224,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,   219,   220,   227,   228,   229,   233,
     241,   236,    17,   167,   168,   169,   170,   171,   172,   173,
     177,   175,   240,   178,   243,   246,   249,   253,   252,    94,
      95,    96,   256,   255,   258,   260,   261,    97,   264,   265,
     263,   266,   276,   284,   268,   287,   225,   299,   190,   200,
     232,   234,   251,   184,   298,   217,   305,   293,   140,   242,
     112,   304,   297,   245,   235,   288,   203,   262,   213,     0,
       0,   269
};

static const yytype_int16 yycheck[] =
{
      37,     1,   180,   134,   138,   231,    67,   264,    50,     8,
      42,    39,   197,     5,    75,     7,    58,    49,     9,    67,
      68,    69,   248,    43,   281,    72,    72,    75,    65,    75,
      62,    63,    64,    65,    66,     6,     7,    69,    70,    71,
      72,    33,    74,    42,   229,    36,    20,    67,    68,    69,
      49,     5,    57,     7,    91,    75,    61,    94,    95,    96,
      97,    24,    25,    62,    63,    64,    65,    66,   105,    72,
      69,    70,    71,    72,    22,    74,    67,    68,    69,    44,
      45,    46,    47,    48,    75,    72,    42,    40,   222,   126,
      43,    24,    25,    49,    39,    39,    39,    39,    39,   136,
      29,    39,    72,     7,   282,   283,    62,    63,    64,    65,
      66,    72,    72,    69,    70,    71,    72,    39,    74,    75,
      39,    22,    72,    72,    26,    30,    40,   164,   128,    42,
      42,    41,    27,    42,    23,    72,    39,    49,    72,   176,
     271,   272,    39,   180,   275,    21,    58,    72,    60,    72,
      62,    63,    64,    65,    66,    22,    42,    69,    70,    71,
      72,   198,    74,    49,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    27,   211,    74,    62,    63,    64,    65,
      66,   181,    42,    69,    70,    71,    72,    72,    74,    49,
      72,    39,    42,    39,    51,    20,    41,    72,    41,    43,
      42,    72,    62,    63,    64,    65,    66,   207,    41,    69,
      70,    71,    72,    60,    74,    42,   253,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     5,   264,   265,   266,
      43,    42,    41,    67,    68,    69,    72,    72,    49,    42,
      41,    75,    39,    43,   281,   282,   283,   284,     8,   286,
     287,    62,    63,    64,    65,    66,    58,    42,    69,    70,
      71,    72,   299,    74,     0,    57,    39,     3,     4,    31,
      39,    43,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    72,    72,    49,    42,    41,    43,
      39,    43,    28,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    43,    61,    32,    70,    43,    41,    43,    67,
      68,    69,    37,    72,    43,    39,    43,    75,    27,    35,
      43,    38,    34,    41,    39,    35,   190,    41,   145,   157,
     198,   200,   232,   137,   293,   184,   304,   284,   112,   220,
      91,   299,   288,   223,   203,   281,   164,   253,   179,    -1,
      -1,   262
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    78,     0,     3,     4,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    28,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    92,
      93,    94,   101,   107,   108,   111,   112,   121,   147,     5,
       7,    33,     5,     7,    72,     6,     7,    39,    20,    22,
      72,    39,    39,    39,    39,    39,    29,    39,    42,    49,
      62,    63,    64,    65,    66,    69,    70,    71,    72,    74,
      75,   106,   122,   124,   125,   145,    72,    72,     7,    72,
      72,    39,    39,    22,    72,    72,    26,    30,   145,   145,
      40,    41,   123,    42,    67,    68,    69,    75,    42,    27,
      72,    39,    39,    72,    21,    23,   132,    72,   109,    74,
      43,    72,   122,    22,    72,    75,   145,   145,   145,   145,
      72,    96,   100,    72,    27,    39,    42,   102,    42,    58,
      60,   135,   139,   143,   145,    39,    51,    41,   110,    20,
     123,    72,    40,    43,    43,    41,    95,    44,    45,    46,
      47,    48,    99,    42,    72,   103,   145,    41,   105,   112,
      60,    24,    25,   133,   134,    42,   142,    51,    52,    53,
      54,    55,    56,    57,    58,    59,   146,    58,    61,   140,
     146,    42,   141,   145,   109,   132,     5,    41,   126,    72,
      96,    43,    50,    58,    97,    72,    90,    42,    41,   104,
     102,    39,    43,   135,   112,    57,    58,    42,   144,   145,
      61,    42,   136,   142,   144,   145,   112,   110,    39,    72,
      72,    31,   127,   128,    43,    95,    39,    49,    42,    41,
      91,    90,   103,    43,   105,   133,    43,   112,   137,   145,
      43,    39,   126,    32,   132,   127,    70,    98,    90,    43,
      91,   104,    43,    41,   138,    72,    37,   114,    43,    91,
      39,    43,   137,    43,    27,    35,    38,   113,    39,   138,
     131,   143,   145,   115,   145,   145,    34,   117,    24,    25,
     129,   130,   146,   146,    41,   116,   146,    35,   131,   144,
     145,   144,   145,   115,   145,   118,   145,   129,   116,    41,
     119,     9,    36,   120,   118,   119
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    77,    78,    78,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    89,    90,    91,    91,    92,    93,    94,    95,
      95,    96,    96,    97,    97,    97,    98,    99,    99,    99,
      99,    99,   100,   101,   102,   103,   104,   104,   105,   105,
     106,   106,   106,   106,   107,   108,   109,   109,   110,   110,
     111,   112,   113,   113,   114,   114,   115,   116,   116,   117,
     117,   118,   119,   119,   120,   120,   120,   121,   122,   122,
     123,   123,   124,   124,   124,   125,   125,   125,   125,   125,
     126,   126,   127,   127,   128,   129,   129,   130,   130,   131,
     131,   131,   131,   132,   132,   133,   133,   134,   134,   135,
     135,   135,   135,   135,   135,   135,   136,   137,   138,   138,
     139,   139,   140,   140,   141,   142,   143,   144,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   147
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,    10,    11,     1,     0,     3,     4,     5,     8,     0,
       3,     6,     3,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     7,     4,     1,     0,     3,     0,     3,
       1,     1,     1,     1,     5,     7,     3,     3,     0,     3,
       2,    11,     0,     4,     0,     4,     1,     0,     3,     0,
       4,     2,     0,     3,     0,     1,     1,     1,     1,     1,
       0,     3,     4,     6,     4,     1,     1,     1,     1,     1,
       0,     3,     0,     2,     6,     0,     3,     1,     1,     3,
       3,     3,     3,     0,     3,     0,     3,     1,     1,     3,
       3,     3,     3,     2,     3,     3,     4,     1,     0,     3,
       1,     2,     1,     2,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     8
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, void *scanner)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , scanner);
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 22:
#line 189 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1737 "yacc_sql.tab.c"
    break;

  case 23:
#line 194 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1745 "yacc_sql.tab.c"
    break;

  case 24:
#line 199 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1753 "yacc_sql.tab.c"
    break;

  case 25:
#line 205 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1761 "yacc_sql.tab.c"
    break;

  case 26:
#line 211 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1769 "yacc_sql.tab.c"
    break;

  case 27:
#line 217 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1777 "yacc_sql.tab.c"
    break;

  case 28:
#line 223 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1786 "yacc_sql.tab.c"
    break;

  case 29:
#line 229 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1794 "yacc_sql.tab.c"
    break;

  case 30:
#line 235 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1803 "yacc_sql.tab.c"
    break;

  case 31:
#line 242 "yacc_sql.y"
                                                                   {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
		}
#line 1812 "yacc_sql.tab.c"
    break;

  case 32:
#line 246 "yacc_sql.y"
                                                                                        {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
		}
#line 1821 "yacc_sql.tab.c"
    break;

  case 33:
#line 253 "yacc_sql.y"
                   {
			create_index_append_attributes(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
		}
#line 1829 "yacc_sql.tab.c"
    break;

  case 36:
#line 265 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1838 "yacc_sql.tab.c"
    break;

  case 37:
#line 272 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1847 "yacc_sql.tab.c"
    break;

  case 38:
#line 279 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
		}
#line 1856 "yacc_sql.tab.c"
    break;

  case 41:
#line 291 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-1].number), (yyvsp[-3].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1866 "yacc_sql.tab.c"
    break;

  case 42:
#line 297 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, (yyvsp[0].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1876 "yacc_sql.tab.c"
    break;

  case 43:
#line 304 "yacc_sql.y"
                            {
			(yyval.number) = 0;
		}
#line 1884 "yacc_sql.tab.c"
    break;

  case 44:
#line 307 "yacc_sql.y"
                           {
			(yyval.number) = 1;
		}
#line 1892 "yacc_sql.tab.c"
    break;

  case 45:
#line 310 "yacc_sql.y"
                             {
			(yyval.number) = 0;
		}
#line 1900 "yacc_sql.tab.c"
    break;

  case 46:
#line 315 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1906 "yacc_sql.tab.c"
    break;

  case 47:
#line 318 "yacc_sql.y"
                           { (yyval.number)=INTS;   }
#line 1912 "yacc_sql.tab.c"
    break;

  case 48:
#line 319 "yacc_sql.y"
                           { (yyval.number)=CHARS;  }
#line 1918 "yacc_sql.tab.c"
    break;

  case 49:
#line 320 "yacc_sql.y"
                           { (yyval.number)=FLOATS; }
#line 1924 "yacc_sql.tab.c"
    break;

  case 50:
#line 321 "yacc_sql.y"
                           { (yyval.number)=DATES;  }
#line 1930 "yacc_sql.tab.c"
    break;

  case 51:
#line 322 "yacc_sql.y"
                           { (yyval.number)=TEXTS;  }
#line 1936 "yacc_sql.tab.c"
    break;

  case 52:
#line 325 "yacc_sql.y"
                   {
			char *temp=(yyvsp[0].string); 
			snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
		}
#line 1945 "yacc_sql.tab.c"
    break;

  case 53:
#line 333 "yacc_sql.y"
                                                                 {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
#line 1954 "yacc_sql.tab.c"
    break;

  case 54:
#line 339 "yacc_sql.y"
                                                           {
			insert_append_exprs(&CONTEXT->ssql->sstr.insertion, CONTEXT->exprs[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
			CONTEXT->expr_length[CUR_SEL] = 0;
		}
#line 1963 "yacc_sql.tab.c"
    break;

  case 55:
#line 346 "yacc_sql.y"
                    {
			CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 1971 "yacc_sql.tab.c"
    break;

  case 60:
#line 361 "yacc_sql.y"
           {
			Value value;
			value_init_integer(&value, (yyvsp[0].number));
			(yyval.ast1) = new_value_node(&value);
		}
#line 1981 "yacc_sql.tab.c"
    break;

  case 61:
#line 366 "yacc_sql.y"
           {
			Value value;
			value_init_float(&value, (yyvsp[0].floats));
			(yyval.ast1) = new_value_node(&value);
		}
#line 1991 "yacc_sql.tab.c"
    break;

  case 62:
#line 371 "yacc_sql.y"
         {
			Value value;
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&value, (yyvsp[0].string));
			(yyval.ast1) = new_value_node(&value);
		}
#line 2002 "yacc_sql.tab.c"
    break;

  case 63:
#line 377 "yacc_sql.y"
                        {
			Value value;
			value_init_null(&value);
			(yyval.ast1) = new_value_node(&value);
		}
#line 2012 "yacc_sql.tab.c"
    break;

  case 64:
#line 386 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			deletes_set_condition_ops(&CONTEXT->ssql->sstr.deletion, CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			CONTEXT->condition_length[CUR_SEL] = 0;	
    }
#line 2025 "yacc_sql.tab.c"
    break;

  case 65:
#line 397 "yacc_sql.y"
                                                               {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			updates_set_condition_ops(&CONTEXT->ssql->sstr.update, CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			CONTEXT->condition_length[CUR_SEL] = 0;
		}
#line 2036 "yacc_sql.tab.c"
    break;

  case 66:
#line 406 "yacc_sql.y"
                          {
			UpdatePair pair;
			update_pair_init(&pair, (yyvsp[-2].string), 0, NULL, (yyvsp[0].ast1));
			update_append_pair(&CONTEXT->ssql->sstr.update, &pair);
		}
#line 2046 "yacc_sql.tab.c"
    break;

  case 67:
#line 411 "yacc_sql.y"
                                      {
			UpdatePair pair;
			update_pair_init(&pair, (yyvsp[-2].string), 1, &CONTEXT->update_select, NULL);
			update_append_pair(&CONTEXT->ssql->sstr.update, &pair);
		}
#line 2056 "yacc_sql.tab.c"
    break;

  case 70:
#line 425 "yacc_sql.y"
                                      {
			CONTEXT->ssql->sstr.selection = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2066 "yacc_sql.tab.c"
    break;

  case 71:
#line 434 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			selects_append_relation(&CONTEXT->selects[CUR_SEL], (yyvsp[-6].string));
			selects_append_conditions(&CONTEXT->selects[CUR_SEL], CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			selects_set_condition_ops(&CONTEXT->selects[CUR_SEL], CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			selects_append_joins(&CONTEXT->selects[CUR_SEL], CONTEXT->joins[CUR_SEL], CONTEXT->join_length[CUR_SEL]);
			selects_append_exprs(&CONTEXT->selects[CUR_SEL], CONTEXT->exprs[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
			selects_set_order_info(&CONTEXT->selects[CUR_SEL], CONTEXT->orders[CUR_SEL], CONTEXT->order_attrs[CUR_SEL], CONTEXT->order_attr_length[CUR_SEL]);
			selects_set_group_by(&CONTEXT->selects[CUR_SEL], CONTEXT->group_bys[CUR_SEL], CONTEXT->group_by_length[CUR_SEL]);
	}
#line 2082 "yacc_sql.tab.c"
    break;

  case 73:
#line 449 "yacc_sql.y"
                               {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
		selects_set_having(&CONTEXT->selects[CUR_SEL], &condition);
	}
#line 2092 "yacc_sql.tab.c"
    break;

  case 76:
#line 462 "yacc_sql.y"
                    {
			CONTEXT->group_bys[CUR_SEL][CONTEXT->group_by_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 2100 "yacc_sql.tab.c"
    break;

  case 81:
#line 478 "yacc_sql.y"
                                 {
			CONTEXT->order_attrs[CUR_SEL][CONTEXT->order_attr_length[CUR_SEL]] = (yyvsp[-1].ast1);
			CONTEXT->orders[CUR_SEL][CONTEXT->order_attr_length[CUR_SEL]] = (yyvsp[0].order_policy1);
			CONTEXT->order_attr_length[CUR_SEL]++;
		}
#line 2110 "yacc_sql.tab.c"
    break;

  case 84:
#line 491 "yacc_sql.y"
                            {
			(yyval.order_policy1) = ORDER_ASC;
		}
#line 2118 "yacc_sql.tab.c"
    break;

  case 85:
#line 494 "yacc_sql.y"
                      {
			(yyval.order_policy1) = ORDER_ASC;
		}
#line 2126 "yacc_sql.tab.c"
    break;

  case 86:
#line 497 "yacc_sql.y"
                       {
			(yyval.order_policy1) = ORDER_DESC;
		}
#line 2134 "yacc_sql.tab.c"
    break;

  case 87:
#line 503 "yacc_sql.y"
                       {
			CONTEXT->select_length++;
		}
#line 2142 "yacc_sql.tab.c"
    break;

  case 88:
#line 509 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = new_attr_node(&attr);
	}
#line 2152 "yacc_sql.tab.c"
    break;

  case 89:
#line 514 "yacc_sql.y"
              {
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = (yyvsp[0].ast1);
	}
#line 2160 "yacc_sql.tab.c"
    break;

  case 92:
#line 525 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 2172 "yacc_sql.tab.c"
    break;

  case 93:
#line 532 "yacc_sql.y"
                                                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 2184 "yacc_sql.tab.c"
    break;

  case 94:
#line 539 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 2196 "yacc_sql.tab.c"
    break;

  case 95:
#line 549 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = MAXS; }
#line 2202 "yacc_sql.tab.c"
    break;

  case 96:
#line 550 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = MINS; }
#line 2208 "yacc_sql.tab.c"
    break;

  case 97:
#line 551 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = AVGS; }
#line 2214 "yacc_sql.tab.c"
    break;

  case 98:
#line 552 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = SUMS; }
#line 2220 "yacc_sql.tab.c"
    break;

  case 99:
#line 553 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = COUNTS; }
#line 2226 "yacc_sql.tab.c"
    break;

  case 101:
#line 558 "yacc_sql.y"
                        {	
			selects_append_relation(&CONTEXT->selects[CUR_SEL], (yyvsp[-1].string));
		}
#line 2234 "yacc_sql.tab.c"
    break;

  case 104:
#line 569 "yacc_sql.y"
                                                                    {
			Join join;
			join_init(&join, (yyvsp[-3].string), CONTEXT->join_conditions[CUR_SEL], CONTEXT->join_condition_length[CUR_SEL]);
			CONTEXT->joins[CUR_SEL][CONTEXT->join_length[CUR_SEL]++] = join;
			CONTEXT->join_condition_length[CUR_SEL] = 0;
		}
#line 2245 "yacc_sql.tab.c"
    break;

  case 107:
#line 583 "yacc_sql.y"
                    {
			CONTEXT->join_condition_ops[CUR_SEL][CONTEXT->join_condition_op_length[CUR_SEL]++] = COND_AND;
		}
#line 2253 "yacc_sql.tab.c"
    break;

  case 108:
#line 586 "yacc_sql.y"
                     {
			CONTEXT->join_condition_ops[CUR_SEL][CONTEXT->join_condition_op_length[CUR_SEL]++] = COND_OR;
		}
#line 2261 "yacc_sql.tab.c"
    break;

  case 109:
#line 592 "yacc_sql.y"
                              {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->join_condition_length[CUR_SEL]++] = condition;
		}
#line 2271 "yacc_sql.tab.c"
    break;

  case 110:
#line 597 "yacc_sql.y"
                                             {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, NULL, &CONTEXT->right_sub_select);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2281 "yacc_sql.tab.c"
    break;

  case 111:
#line 602 "yacc_sql.y"
                                            {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, NULL, &CONTEXT->left_sub_select, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2291 "yacc_sql.tab.c"
    break;

  case 112:
#line 607 "yacc_sql.y"
                                                         {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, NULL, &CONTEXT->left_sub_select, 0, NULL, &CONTEXT->right_sub_select);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2301 "yacc_sql.tab.c"
    break;

  case 117:
#line 623 "yacc_sql.y"
                    {
			CONTEXT->condition_ops[CUR_SEL][CONTEXT->condition_op_length[CUR_SEL]++] = COND_AND;
		}
#line 2309 "yacc_sql.tab.c"
    break;

  case 118:
#line 626 "yacc_sql.y"
                     {
			CONTEXT->condition_ops[CUR_SEL][CONTEXT->condition_op_length[CUR_SEL]++] = COND_OR;
		}
#line 2317 "yacc_sql.tab.c"
    break;

  case 119:
#line 631 "yacc_sql.y"
                              {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2327 "yacc_sql.tab.c"
    break;

  case 120:
#line 636 "yacc_sql.y"
                                             {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 1, NULL, &CONTEXT->right_sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2337 "yacc_sql.tab.c"
    break;

  case 121:
#line 641 "yacc_sql.y"
                                            {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 1, NULL, &CONTEXT->left_sub_select, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2347 "yacc_sql.tab.c"
    break;

  case 122:
#line 646 "yacc_sql.y"
                                                         {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 1, NULL, &CONTEXT->left_sub_select, 1, NULL, &CONTEXT->right_sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2357 "yacc_sql.tab.c"
    break;

  case 123:
#line 651 "yacc_sql.y"
                                      {
			Condition condition;
			condition_init_exists(&condition, (yyvsp[-1].number), &CONTEXT->sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2367 "yacc_sql.tab.c"
    break;

  case 124:
#line 656 "yacc_sql.y"
                                       {
			Condition condition;
			condition_init_in(&condition, (yyvsp[-1].number), (yyvsp[-2].ast1), &CONTEXT->sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2377 "yacc_sql.tab.c"
    break;

  case 125:
#line 661 "yacc_sql.y"
                                    {
			Condition condition;
			condition_init_in_exprs(&condition, (yyvsp[-1].number), (yyvsp[-2].ast1), CONTEXT->in_exprs[CUR_SEL], CONTEXT->in_expr_length[CUR_SEL]);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
			CONTEXT->in_expr_length[CUR_SEL] = 0;
		}
#line 2388 "yacc_sql.tab.c"
    break;

  case 127:
#line 675 "yacc_sql.y"
                    {
			CONTEXT->in_exprs[CUR_SEL][CONTEXT->in_expr_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 2396 "yacc_sql.tab.c"
    break;

  case 130:
#line 686 "yacc_sql.y"
                        {
			(yyval.number) = 1;
		}
#line 2404 "yacc_sql.tab.c"
    break;

  case 131:
#line 689 "yacc_sql.y"
                              {
			(yyval.number) = 0;
		}
#line 2412 "yacc_sql.tab.c"
    break;

  case 132:
#line 694 "yacc_sql.y"
                    {
			(yyval.number) = 1;
		}
#line 2420 "yacc_sql.tab.c"
    break;

  case 133:
#line 697 "yacc_sql.y"
                          {
			(yyval.number) = 0;
		}
#line 2428 "yacc_sql.tab.c"
    break;

  case 134:
#line 703 "yacc_sql.y"
                                          {
			CONTEXT->update_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2438 "yacc_sql.tab.c"
    break;

  case 135:
#line 711 "yacc_sql.y"
                                          {
			CONTEXT->sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2448 "yacc_sql.tab.c"
    break;

  case 136:
#line 719 "yacc_sql.y"
                                          {
			CONTEXT->left_sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2458 "yacc_sql.tab.c"
    break;

  case 137:
#line 727 "yacc_sql.y"
                                          {
			CONTEXT->right_sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2468 "yacc_sql.tab.c"
    break;

  case 138:
#line 735 "yacc_sql.y"
                          {
			(yyval.ast1) = new_op_node(MATH_SUB, NULL, (yyvsp[0].ast1));
		}
#line 2476 "yacc_sql.tab.c"
    break;

  case 139:
#line 738 "yacc_sql.y"
                               {
			(yyval.ast1) = new_op_node(MATH_ADD, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2484 "yacc_sql.tab.c"
    break;

  case 140:
#line 741 "yacc_sql.y"
                                {
			(yyval.ast1) = new_op_node(MATH_SUB, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2492 "yacc_sql.tab.c"
    break;

  case 141:
#line 744 "yacc_sql.y"
                               {
			(yyval.ast1) = new_op_node(MATH_MUL, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2500 "yacc_sql.tab.c"
    break;

  case 142:
#line 747 "yacc_sql.y"
                                {
			(yyval.ast1) = new_op_node(MATH_DIV, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2508 "yacc_sql.tab.c"
    break;

  case 143:
#line 750 "yacc_sql.y"
                                    {
			(yyval.ast1) = (yyvsp[-1].ast1);
			(yyval.ast1)->l_brace++;
			(yyval.ast1)->r_brace++;
		}
#line 2518 "yacc_sql.tab.c"
    break;

  case 144:
#line 755 "yacc_sql.y"
                        {
			(yyval.ast1) = (yyvsp[0].ast1);
		}
#line 2526 "yacc_sql.tab.c"
    break;

  case 145:
#line 758 "yacc_sql.y"
                     {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			(yyval.ast1) = new_attr_node(&attr);
		}
#line 2536 "yacc_sql.tab.c"
    break;

  case 146:
#line 763 "yacc_sql.y"
                            {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			(yyval.ast1) = new_attr_node(&attr);
		}
#line 2546 "yacc_sql.tab.c"
    break;

  case 147:
#line 768 "yacc_sql.y"
                            {
			(yyval.ast1) = (yyvsp[0].ast1);
		}
#line 2554 "yacc_sql.tab.c"
    break;

  case 148:
#line 774 "yacc_sql.y"
             { CONTEXT->comp[CUR_SEL] = EQUAL_TO; }
#line 2560 "yacc_sql.tab.c"
    break;

  case 149:
#line 775 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = LESS_THAN; }
#line 2566 "yacc_sql.tab.c"
    break;

  case 150:
#line 776 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = GREAT_THAN; }
#line 2572 "yacc_sql.tab.c"
    break;

  case 151:
#line 777 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = LESS_EQUAL; }
#line 2578 "yacc_sql.tab.c"
    break;

  case 152:
#line 778 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = GREAT_EQUAL; }
#line 2584 "yacc_sql.tab.c"
    break;

  case 153:
#line 779 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = NOT_EQUAL; }
#line 2590 "yacc_sql.tab.c"
    break;

  case 154:
#line 780 "yacc_sql.y"
                       { CONTEXT->comp[CUR_SEL] = STR_LIKE; }
#line 2596 "yacc_sql.tab.c"
    break;

  case 155:
#line 781 "yacc_sql.y"
                           { CONTEXT->comp[CUR_SEL] = STR_NOT_LIKE; }
#line 2602 "yacc_sql.tab.c"
    break;

  case 156:
#line 782 "yacc_sql.y"
                      { CONTEXT->comp[CUR_SEL] = IS; }
#line 2608 "yacc_sql.tab.c"
    break;

  case 157:
#line 783 "yacc_sql.y"
                          { CONTEXT->comp[CUR_SEL] = IS_NOT; }
#line 2614 "yacc_sql.tab.c"
    break;

  case 158:
#line 788 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2623 "yacc_sql.tab.c"
    break;


#line 2627 "yacc_sql.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 793 "yacc_sql.y"

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
