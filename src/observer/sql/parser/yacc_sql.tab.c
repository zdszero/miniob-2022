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


#line 172 "yacc_sql.tab.c"

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
    AS = 294,
    SEMICOLON = 295,
    DOT = 296,
    COMMA = 297,
    LBRACE = 298,
    RBRACE = 299,
    INT_T = 300,
    STRING_T = 301,
    FLOAT_T = 302,
    DATE_T = 303,
    TEXT_T = 304,
    NULL_T = 305,
    NULLABLE = 306,
    EQ = 307,
    LT = 308,
    GT = 309,
    LE = 310,
    GE = 311,
    NE = 312,
    LIKE = 313,
    NOT = 314,
    ISS = 315,
    EXISTSS = 316,
    INS = 317,
    MAX = 318,
    MIN = 319,
    AVG = 320,
    SUM = 321,
    COUNT = 322,
    SLASH = 323,
    PLUS = 324,
    MINUS = 325,
    NUMBER = 326,
    FLOAT = 327,
    ID = 328,
    PATH = 329,
    SSS = 330,
    STAR = 331,
    STRING_V = 332
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 125 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
	struct ast *ast1;
  char *string;
  int number;
  float floats;
	char *position;
	int order_policy1;

#line 314 "yacc_sql.tab.c"

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
#define YYLAST   360

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  162
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  312

#define YYUNDEFTOK  2
#define YYMAXUTOK   332


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
      75,    76,    77
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   164,   164,   166,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   191,   196,   201,   207,   213,   219,   225,   231,
     237,   244,   248,   255,   260,   262,   266,   273,   280,   286,
     288,   292,   298,   306,   309,   312,   317,   320,   321,   322,
     323,   324,   327,   335,   341,   348,   353,   355,   358,   360,
     363,   368,   373,   379,   387,   399,   408,   413,   420,   422,
     427,   435,   448,   450,   457,   459,   463,   468,   470,   473,
     475,   479,   486,   488,   492,   495,   498,   504,   510,   515,
     523,   527,   530,   535,   537,   541,   548,   555,   565,   566,
     567,   568,   569,   573,   578,   580,   583,   585,   589,   597,
     599,   603,   606,   612,   617,   622,   627,   634,   636,   638,
     640,   643,   646,   651,   656,   661,   666,   671,   676,   681,
     691,   695,   700,   702,   706,   709,   714,   717,   723,   731,
     739,   747,   755,   758,   761,   764,   767,   770,   775,   778,
     783,   788,   794,   795,   796,   797,   798,   799,   800,   801,
     802,   803,   807
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
  "HAVING", "AS", "SEMICOLON", "DOT", "COMMA", "LBRACE", "RBRACE", "INT_T",
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
  "order_policy", "begin_select", "select_expr", "as_alias",
  "select_exprs", "aggr_func", "aggr_type", "rel", "rel_list",
  "inner_join_list", "inner_join", "join_condition_list",
  "join_condition_op", "join_condition", "where", "condition_list",
  "condition_op", "condition", "in_pair", "in_expr", "in_expr_list",
  "is_exist", "is_in", "update_select", "sub_select", "left_sub_select",
  "right_sub_select", "exp", "comOp", "load_data", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331,   332
};
# endif

#define YYPACT_NINF (-263)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -263,   273,  -263,    11,    84,  -263,   -62,    26,   -25,    -3,
       4,   -30,    23,    30,    48,    52,    55,    22,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,    56,    44,  -263,     3,
      24,    91,    27,    28,    59,    62,    90,  -263,    33,    40,
      92,  -263,  -263,  -263,  -263,  -263,    93,  -263,   119,  -263,
    -263,  -263,  -263,  -263,  -263,   119,  -263,  -263,    80,  -263,
    -263,  -263,    82,  -263,    79,   -34,    83,    98,    54,    88,
      94,  -263,  -263,    57,   110,   112,    64,    63,   -21,   -47,
      66,    44,   132,   -23,    67,   119,   119,   119,  -263,   119,
    -263,    68,    87,   128,  -263,  -263,   123,   121,    86,   125,
     114,   126,   159,  -263,  -263,    82,   120,    20,   151,  -263,
    -263,   -47,   -47,  -263,  -263,   154,    36,   155,   124,  -263,
     119,   157,     2,   139,  -263,    13,   163,   118,   250,  -263,
     138,    64,   112,   202,  -263,   -33,   170,   142,  -263,  -263,
      68,   174,  -263,  -263,  -263,  -263,  -263,   -29,   144,   176,
     178,   -56,   121,   181,   180,  -263,  -263,  -263,  -263,    86,
     217,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,   168,
     169,   173,   -31,  -263,   184,   173,     2,  -263,   -56,   126,
     189,   158,  -263,   120,   201,   186,   154,   207,  -263,   191,
     211,  -263,   215,   144,   119,   214,   157,  -263,  -263,    13,
     216,  -263,  -263,     2,  -263,   -56,  -263,     2,  -263,  -263,
    -263,   -56,   223,  -263,  -263,   219,   170,   229,   112,   201,
    -263,  -263,  -263,  -263,   204,   144,   234,   215,   178,  -263,
    -263,  -263,  -263,   235,   238,   -56,  -263,  -263,  -263,   220,
     257,  -263,  -263,   251,   215,   256,   253,  -263,  -263,   119,
     254,   272,   265,   276,  -263,  -263,  -263,   271,   238,  -263,
     199,   119,   119,   279,  -263,  -263,    32,   118,   275,   274,
     -56,   275,   280,  -263,  -263,  -263,  -263,   199,   173,   173,
     119,  -263,   119,   119,    32,  -263,   -56,  -263,   -56,   274,
     -56,   281,    10,  -263,  -263,   119,  -263,  -263,  -263,  -263,
     281,  -263
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
      98,    99,   100,   101,   102,     0,    60,    61,   149,    62,
      88,   148,    93,   151,     0,    90,     0,     0,     0,     0,
       0,    30,    29,     0,     0,   117,     0,     0,     0,   142,
       0,     0,     0,     0,     0,     0,     0,     0,    91,     0,
      89,     0,     0,     0,    28,    36,     0,     0,     0,     0,
       0,    68,     0,   147,   150,    93,     0,     0,     0,    92,
     146,   143,   144,   145,    52,    39,     0,     0,     0,    37,
       0,    58,     0,     0,   134,   119,     0,     0,     0,    64,
       0,     0,   117,     0,    94,    90,   104,     0,    95,    97,
       0,     0,    47,    48,    49,    50,    51,    43,     0,     0,
      56,    55,     0,     0,     0,   135,   121,   122,   118,     0,
       0,   127,   152,   153,   154,   155,   156,   157,   158,     0,
     160,     0,     0,   136,     0,     0,     0,    67,    66,    68,
       0,     0,   103,     0,   106,     0,    39,     0,    44,     0,
      42,    33,    34,     0,     0,     0,    58,    53,   140,   119,
       0,   159,   161,     0,   126,   125,   137,     0,   129,   128,
     124,   123,     0,    69,    65,     0,   104,     0,   117,   106,
      96,    40,    38,    45,     0,     0,     0,    34,    56,    54,
      59,   120,   139,     0,   132,   131,   138,   162,   105,     0,
      74,   107,    46,     0,    34,     0,     0,    57,   141,     0,
       0,     0,     0,    72,    41,    35,    31,     0,   132,   130,
       0,     0,     0,    79,    32,   133,   109,     0,     0,    77,
      76,     0,     0,    71,   111,   112,   108,     0,     0,     0,
       0,    75,     0,     0,   109,   116,   115,   114,   113,    77,
      73,    82,    84,   110,    78,     0,    80,    86,    85,    81,
      82,    83
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -194,  -230,  -263,  -263,  -263,   129,   167,
    -263,  -263,  -263,  -263,  -263,   160,   117,    99,   130,  -263,
    -263,  -263,   183,   149,  -263,     1,  -263,  -263,    49,    41,
    -263,    37,    31,  -263,  -263,   255,   203,   232,  -263,  -263,
     156,   127,   131,  -263,    58,  -263,    69,  -138,   141,  -263,
     185,  -263,    96,    89,  -263,  -263,  -263,   175,  -262,  -184,
     -37,  -135,  -263
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   202,   236,    29,    30,    31,   151,   125,
     200,   253,   157,   126,    32,   131,   160,   205,   163,    71,
      33,    34,   111,   142,    35,   210,   273,   263,   279,   291,
     283,   301,   306,   309,    37,    72,   100,    92,    73,    74,
     146,   194,   228,   229,   286,   287,   276,   109,   168,   169,
     135,   218,   244,   260,   136,   184,   187,   171,   137,   214,
      88,   181,    38
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      75,   220,    36,   185,   190,    94,    94,   256,   277,   237,
       5,    44,    95,    96,    97,    47,    39,    48,    40,   307,
      99,    95,   198,   113,   265,   277,    49,   211,    89,    99,
     199,   216,    45,    46,    95,    96,    97,   166,   167,    98,
      98,   254,    99,    50,    41,    58,   308,    95,    96,    97,
     117,    56,    59,   118,    75,    99,   284,   285,   120,   121,
     122,   147,   123,    51,   148,    60,    61,    62,    63,    64,
      52,   138,    65,    66,    67,    68,    76,    69,    95,    96,
      97,   152,   153,   154,   155,   156,    99,    58,    53,    42,
     250,    43,    54,   161,    59,    55,    57,    77,    78,    81,
      79,    80,    82,   188,   295,   297,    84,    60,    61,    62,
      63,    64,    83,    85,    65,    66,    67,    68,    86,    69,
      70,    90,    93,    87,    91,   102,   101,   103,   104,   132,
     106,   107,   138,   164,   105,   108,    59,   110,   112,   114,
     119,   124,   288,   289,   215,   133,   292,   134,   221,    60,
      61,    62,    63,    64,   116,   128,    65,    66,    67,    68,
     127,    69,    58,   129,   130,   139,   140,   161,   141,    59,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   143,
     245,   186,    60,    61,    62,    63,    64,   222,    59,    65,
      66,    67,    68,   145,    69,   149,   150,   159,   158,   162,
     165,    60,    61,    62,    63,    64,   170,   191,    65,    66,
      67,    68,   193,    69,   243,   195,   213,   201,   197,   203,
     204,   207,   245,    59,   208,     5,   211,   217,   212,   224,
     230,   225,   227,   278,   280,   281,    60,    61,    62,    63,
      64,   233,   132,    65,    66,    67,    68,   232,    69,    59,
     278,   296,   298,   280,   234,   300,   302,   235,   239,   247,
     242,   249,    60,    61,    62,    63,    64,   246,   302,    65,
      66,    67,    68,     2,    69,   252,     3,     4,   255,   258,
     259,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,   261,   262,   264,   266,   267,   269,   270,
     271,    17,   172,   173,   174,   175,   176,   177,   178,   182,
     180,   274,   183,   282,   272,   293,   290,   196,    95,    96,
      97,   238,   206,   305,   189,   231,    99,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   240,   257,   223,   299,
     304,   311,   310,    95,    96,    97,   115,   144,   192,   226,
     241,    99,   303,   248,   209,   268,   294,   275,     0,   219,
     251
};

static const yytype_int16 yycheck[] =
{
      37,   185,     1,   138,   142,    39,    39,   237,   270,   203,
       8,    73,    68,    69,    70,    40,     5,    20,     7,     9,
      76,    68,    51,    44,   254,   287,    22,    58,    65,    76,
      59,    62,     6,     7,    68,    69,    70,    24,    25,    73,
      73,   235,    76,    73,    33,    43,    36,    68,    69,    70,
      73,    29,    50,    76,    91,    76,    24,    25,    95,    96,
      97,    41,    99,    40,    44,    63,    64,    65,    66,    67,
      40,   108,    70,    71,    72,    73,    73,    75,    68,    69,
      70,    45,    46,    47,    48,    49,    76,    43,    40,     5,
     228,     7,    40,   130,    50,    40,    40,    73,     7,    40,
      73,    73,    40,   140,   288,   289,    73,    63,    64,    65,
      66,    67,    22,    73,    70,    71,    72,    73,    26,    75,
      76,    41,    43,    30,    42,    27,    43,    73,    40,    43,
      73,    21,   169,   132,    40,    23,    50,    73,    75,    73,
      73,    73,   277,   278,   181,    59,   281,    61,   185,    63,
      64,    65,    66,    67,    22,    27,    70,    71,    72,    73,
      73,    75,    43,    40,    43,    40,    52,   204,    42,    50,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    20,
     217,    43,    63,    64,    65,    66,    67,   186,    50,    70,
      71,    72,    73,    73,    75,    44,    42,    73,    43,    42,
      61,    63,    64,    65,    66,    67,    43,     5,    70,    71,
      72,    73,    42,    75,   213,    73,    43,    73,    44,    43,
      42,    40,   259,    50,    44,     8,    58,    43,    59,    40,
      44,    73,    31,   270,   271,   272,    63,    64,    65,    66,
      67,    50,    43,    70,    71,    72,    73,    40,    75,    50,
     287,   288,   289,   290,    43,   292,   293,    42,    44,    40,
      44,    32,    63,    64,    65,    66,    67,    44,   305,    70,
      71,    72,    73,     0,    75,    71,     3,     4,    44,    44,
      42,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    73,    37,    44,    40,    44,    44,    27,
      35,    28,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    40,    62,    34,    38,    35,    42,   150,    68,    69,
      70,   204,   162,    42,   141,   196,    76,    52,    53,    54,
      55,    56,    57,    58,    59,    60,   206,   238,   189,   290,
     299,   310,   305,    68,    69,    70,    91,   115,   145,   193,
     209,    76,   294,   226,   169,   259,   287,   268,    -1,   184,
     229
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    79,     0,     3,     4,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    28,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    93,
      94,    95,   102,   108,   109,   112,   113,   122,   150,     5,
       7,    33,     5,     7,    73,     6,     7,    40,    20,    22,
      73,    40,    40,    40,    40,    40,    29,    40,    43,    50,
      63,    64,    65,    66,    67,    70,    71,    72,    73,    75,
      76,   107,   123,   126,   127,   148,    73,    73,     7,    73,
      73,    40,    40,    22,    73,    73,    26,    30,   148,   148,
      41,    42,   125,    43,    39,    68,    69,    70,    73,    76,
     124,    43,    27,    73,    40,    40,    73,    21,    23,   135,
      73,   110,    75,    44,    73,   123,    22,    73,    76,    73,
     148,   148,   148,   148,    73,    97,   101,    73,    27,    40,
      43,   103,    43,    59,    61,   138,   142,   146,   148,    40,
      52,    42,   111,    20,   125,    73,   128,    41,    44,    44,
      42,    96,    45,    46,    47,    48,    49,   100,    43,    73,
     104,   148,    42,   106,   113,    61,    24,    25,   136,   137,
      43,   145,    52,    53,    54,    55,    56,    57,    58,    59,
      60,   149,    59,    62,   143,   149,    43,   144,   148,   110,
     135,     5,   124,    42,   129,    73,    97,    44,    51,    59,
      98,    73,    91,    43,    42,   105,   103,    40,    44,   138,
     113,    58,    59,    43,   147,   148,    62,    43,   139,   145,
     147,   148,   113,   111,    40,    73,   128,    31,   130,   131,
      44,    96,    40,    50,    43,    42,    92,    91,   104,    44,
     106,   136,    44,   113,   140,   148,    44,    40,   129,    32,
     135,   130,    71,    99,    91,    44,    92,   105,    44,    42,
     141,    73,    37,   115,    44,    92,    40,    44,   140,    44,
      27,    35,    38,   114,    40,   141,   134,   146,   148,   116,
     148,   148,    34,   118,    24,    25,   132,   133,   149,   149,
      42,   117,   149,    35,   134,   147,   148,   147,   148,   116,
     148,   119,   148,   132,   117,    42,   120,     9,    36,   121,
     119,   120
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    79,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    90,    91,    92,    92,    93,    94,    95,    96,
      96,    97,    97,    98,    98,    98,    99,   100,   100,   100,
     100,   100,   101,   102,   103,   104,   105,   105,   106,   106,
     107,   107,   107,   107,   108,   109,   110,   110,   111,   111,
     112,   113,   114,   114,   115,   115,   116,   117,   117,   118,
     118,   119,   120,   120,   121,   121,   121,   122,   123,   123,
     124,   124,   124,   125,   125,   126,   126,   126,   127,   127,
     127,   127,   127,   128,   129,   129,   130,   130,   131,   132,
     132,   133,   133,   134,   134,   134,   134,   135,   135,   136,
     136,   137,   137,   138,   138,   138,   138,   138,   138,   138,
     139,   140,   141,   141,   142,   142,   143,   143,   144,   145,
     146,   147,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   150
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
       4,     2,     0,     3,     0,     1,     1,     1,     1,     2,
       0,     1,     2,     0,     3,     4,     6,     4,     1,     1,
       1,     1,     1,     2,     0,     3,     0,     2,     6,     0,
       3,     1,     1,     3,     3,     3,     3,     0,     3,     0,
       3,     1,     1,     3,     3,     3,     3,     2,     3,     3,
       4,     1,     0,     3,     1,     2,     1,     2,     3,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     8
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
#line 191 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1748 "yacc_sql.tab.c"
    break;

  case 23:
#line 196 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1756 "yacc_sql.tab.c"
    break;

  case 24:
#line 201 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1764 "yacc_sql.tab.c"
    break;

  case 25:
#line 207 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1772 "yacc_sql.tab.c"
    break;

  case 26:
#line 213 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1780 "yacc_sql.tab.c"
    break;

  case 27:
#line 219 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1788 "yacc_sql.tab.c"
    break;

  case 28:
#line 225 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1797 "yacc_sql.tab.c"
    break;

  case 29:
#line 231 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1805 "yacc_sql.tab.c"
    break;

  case 30:
#line 237 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1814 "yacc_sql.tab.c"
    break;

  case 31:
#line 244 "yacc_sql.y"
                                                                   {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
		}
#line 1823 "yacc_sql.tab.c"
    break;

  case 32:
#line 248 "yacc_sql.y"
                                                                                        {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
		}
#line 1832 "yacc_sql.tab.c"
    break;

  case 33:
#line 255 "yacc_sql.y"
                   {
			create_index_append_attributes(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
		}
#line 1840 "yacc_sql.tab.c"
    break;

  case 36:
#line 267 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1849 "yacc_sql.tab.c"
    break;

  case 37:
#line 274 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1858 "yacc_sql.tab.c"
    break;

  case 38:
#line 281 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
		}
#line 1867 "yacc_sql.tab.c"
    break;

  case 41:
#line 293 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-1].number), (yyvsp[-3].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1877 "yacc_sql.tab.c"
    break;

  case 42:
#line 299 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, (yyvsp[0].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1887 "yacc_sql.tab.c"
    break;

  case 43:
#line 306 "yacc_sql.y"
                            {
			(yyval.number) = 0;
		}
#line 1895 "yacc_sql.tab.c"
    break;

  case 44:
#line 309 "yacc_sql.y"
                           {
			(yyval.number) = 1;
		}
#line 1903 "yacc_sql.tab.c"
    break;

  case 45:
#line 312 "yacc_sql.y"
                             {
			(yyval.number) = 0;
		}
#line 1911 "yacc_sql.tab.c"
    break;

  case 46:
#line 317 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1917 "yacc_sql.tab.c"
    break;

  case 47:
#line 320 "yacc_sql.y"
                           { (yyval.number)=INTS;   }
#line 1923 "yacc_sql.tab.c"
    break;

  case 48:
#line 321 "yacc_sql.y"
                           { (yyval.number)=CHARS;  }
#line 1929 "yacc_sql.tab.c"
    break;

  case 49:
#line 322 "yacc_sql.y"
                           { (yyval.number)=FLOATS; }
#line 1935 "yacc_sql.tab.c"
    break;

  case 50:
#line 323 "yacc_sql.y"
                           { (yyval.number)=DATES;  }
#line 1941 "yacc_sql.tab.c"
    break;

  case 51:
#line 324 "yacc_sql.y"
                           { (yyval.number)=TEXTS;  }
#line 1947 "yacc_sql.tab.c"
    break;

  case 52:
#line 327 "yacc_sql.y"
                   {
			char *temp=(yyvsp[0].string); 
			snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
		}
#line 1956 "yacc_sql.tab.c"
    break;

  case 53:
#line 335 "yacc_sql.y"
                                                                 {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
#line 1965 "yacc_sql.tab.c"
    break;

  case 54:
#line 341 "yacc_sql.y"
                                                           {
			insert_append_exprs(&CONTEXT->ssql->sstr.insertion, CONTEXT->exprs[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
			CONTEXT->expr_length[CUR_SEL] = 0;
		}
#line 1974 "yacc_sql.tab.c"
    break;

  case 55:
#line 348 "yacc_sql.y"
                    {
			CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 1982 "yacc_sql.tab.c"
    break;

  case 60:
#line 363 "yacc_sql.y"
           {
			Value value;
			value_init_integer(&value, (yyvsp[0].number));
			(yyval.ast1) = new_value_node(&value);
		}
#line 1992 "yacc_sql.tab.c"
    break;

  case 61:
#line 368 "yacc_sql.y"
           {
			Value value;
			value_init_float(&value, (yyvsp[0].floats));
			(yyval.ast1) = new_value_node(&value);
		}
#line 2002 "yacc_sql.tab.c"
    break;

  case 62:
#line 373 "yacc_sql.y"
         {
			Value value;
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&value, (yyvsp[0].string));
			(yyval.ast1) = new_value_node(&value);
		}
#line 2013 "yacc_sql.tab.c"
    break;

  case 63:
#line 379 "yacc_sql.y"
                        {
			Value value;
			value_init_null(&value);
			(yyval.ast1) = new_value_node(&value);
		}
#line 2023 "yacc_sql.tab.c"
    break;

  case 64:
#line 388 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			deletes_set_condition_ops(&CONTEXT->ssql->sstr.deletion, CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			CONTEXT->condition_length[CUR_SEL] = 0;	
    }
#line 2036 "yacc_sql.tab.c"
    break;

  case 65:
#line 399 "yacc_sql.y"
                                                               {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			updates_set_condition_ops(&CONTEXT->ssql->sstr.update, CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			CONTEXT->condition_length[CUR_SEL] = 0;
		}
#line 2047 "yacc_sql.tab.c"
    break;

  case 66:
#line 408 "yacc_sql.y"
                          {
			UpdatePair pair;
			update_pair_init(&pair, (yyvsp[-2].string), 0, NULL, (yyvsp[0].ast1));
			update_append_pair(&CONTEXT->ssql->sstr.update, &pair);
		}
#line 2057 "yacc_sql.tab.c"
    break;

  case 67:
#line 413 "yacc_sql.y"
                                      {
			UpdatePair pair;
			update_pair_init(&pair, (yyvsp[-2].string), 1, &CONTEXT->update_select, NULL);
			update_append_pair(&CONTEXT->ssql->sstr.update, &pair);
		}
#line 2067 "yacc_sql.tab.c"
    break;

  case 70:
#line 427 "yacc_sql.y"
                                      {
			CONTEXT->ssql->sstr.selection = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2077 "yacc_sql.tab.c"
    break;

  case 71:
#line 436 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			selects_append_conditions(&CONTEXT->selects[CUR_SEL], CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			selects_set_condition_ops(&CONTEXT->selects[CUR_SEL], CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			selects_append_joins(&CONTEXT->selects[CUR_SEL], CONTEXT->joins[CUR_SEL], CONTEXT->join_length[CUR_SEL]);
			selects_append_exprs(&CONTEXT->selects[CUR_SEL], CONTEXT->exprs[CUR_SEL], CONTEXT->expr_alias[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
			selects_set_order_info(&CONTEXT->selects[CUR_SEL], CONTEXT->orders[CUR_SEL], CONTEXT->order_attrs[CUR_SEL], CONTEXT->order_attr_length[CUR_SEL]);
			selects_set_group_by(&CONTEXT->selects[CUR_SEL], CONTEXT->group_bys[CUR_SEL], CONTEXT->group_by_length[CUR_SEL]);
	}
#line 2092 "yacc_sql.tab.c"
    break;

  case 73:
#line 450 "yacc_sql.y"
                               {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
		selects_set_having(&CONTEXT->selects[CUR_SEL], &condition);
	}
#line 2102 "yacc_sql.tab.c"
    break;

  case 76:
#line 463 "yacc_sql.y"
                    {
			CONTEXT->group_bys[CUR_SEL][CONTEXT->group_by_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 2110 "yacc_sql.tab.c"
    break;

  case 81:
#line 479 "yacc_sql.y"
                                 {
			CONTEXT->order_attrs[CUR_SEL][CONTEXT->order_attr_length[CUR_SEL]] = (yyvsp[-1].ast1);
			CONTEXT->orders[CUR_SEL][CONTEXT->order_attr_length[CUR_SEL]] = (yyvsp[0].order_policy1);
			CONTEXT->order_attr_length[CUR_SEL]++;
		}
#line 2120 "yacc_sql.tab.c"
    break;

  case 84:
#line 492 "yacc_sql.y"
                            {
			(yyval.order_policy1) = ORDER_ASC;
		}
#line 2128 "yacc_sql.tab.c"
    break;

  case 85:
#line 495 "yacc_sql.y"
                      {
			(yyval.order_policy1) = ORDER_ASC;
		}
#line 2136 "yacc_sql.tab.c"
    break;

  case 86:
#line 498 "yacc_sql.y"
                       {
			(yyval.order_policy1) = ORDER_DESC;
		}
#line 2144 "yacc_sql.tab.c"
    break;

  case 87:
#line 504 "yacc_sql.y"
                       {
			CONTEXT->select_length++;
		}
#line 2152 "yacc_sql.tab.c"
    break;

  case 88:
#line 510 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = new_attr_node(&attr);
	}
#line 2162 "yacc_sql.tab.c"
    break;

  case 89:
#line 515 "yacc_sql.y"
                       {
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]] = (yyvsp[-1].ast1);
		CONTEXT->expr_alias[CUR_SEL][CONTEXT->expr_length[CUR_SEL]] = (yyvsp[0].string);
		CONTEXT->expr_length[CUR_SEL]++;
	}
#line 2172 "yacc_sql.tab.c"
    break;

  case 90:
#line 523 "yacc_sql.y"
                            {
			(yyval.string) = NULL;
		}
#line 2180 "yacc_sql.tab.c"
    break;

  case 91:
#line 527 "yacc_sql.y"
                   {
			(yyval.string) = strdup((yyvsp[0].string));
		}
#line 2188 "yacc_sql.tab.c"
    break;

  case 92:
#line 530 "yacc_sql.y"
                        {
			(yyval.string) = strdup((yyvsp[0].string));
		}
#line 2196 "yacc_sql.tab.c"
    break;

  case 95:
#line 541 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 2208 "yacc_sql.tab.c"
    break;

  case 96:
#line 548 "yacc_sql.y"
                                                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 2220 "yacc_sql.tab.c"
    break;

  case 97:
#line 555 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 2232 "yacc_sql.tab.c"
    break;

  case 98:
#line 565 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = MAXS; }
#line 2238 "yacc_sql.tab.c"
    break;

  case 99:
#line 566 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = MINS; }
#line 2244 "yacc_sql.tab.c"
    break;

  case 100:
#line 567 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = AVGS; }
#line 2250 "yacc_sql.tab.c"
    break;

  case 101:
#line 568 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = SUMS; }
#line 2256 "yacc_sql.tab.c"
    break;

  case 102:
#line 569 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = COUNTS; }
#line 2262 "yacc_sql.tab.c"
    break;

  case 103:
#line 573 "yacc_sql.y"
                            {
			selects_append_relation(&CONTEXT->selects[CUR_SEL], (yyvsp[-1].string), (yyvsp[0].string));
		}
#line 2270 "yacc_sql.tab.c"
    break;

  case 108:
#line 589 "yacc_sql.y"
                                                                    {
			Join join;
			join_init(&join, (yyvsp[-3].string), CONTEXT->join_conditions[CUR_SEL], CONTEXT->join_condition_length[CUR_SEL]);
			CONTEXT->joins[CUR_SEL][CONTEXT->join_length[CUR_SEL]++] = join;
			CONTEXT->join_condition_length[CUR_SEL] = 0;
		}
#line 2281 "yacc_sql.tab.c"
    break;

  case 111:
#line 603 "yacc_sql.y"
                    {
			CONTEXT->join_condition_ops[CUR_SEL][CONTEXT->join_condition_op_length[CUR_SEL]++] = COND_AND;
		}
#line 2289 "yacc_sql.tab.c"
    break;

  case 112:
#line 606 "yacc_sql.y"
                     {
			CONTEXT->join_condition_ops[CUR_SEL][CONTEXT->join_condition_op_length[CUR_SEL]++] = COND_OR;
		}
#line 2297 "yacc_sql.tab.c"
    break;

  case 113:
#line 612 "yacc_sql.y"
                              {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->join_condition_length[CUR_SEL]++] = condition;
		}
#line 2307 "yacc_sql.tab.c"
    break;

  case 114:
#line 617 "yacc_sql.y"
                                             {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, NULL, &CONTEXT->right_sub_select);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2317 "yacc_sql.tab.c"
    break;

  case 115:
#line 622 "yacc_sql.y"
                                            {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, NULL, &CONTEXT->left_sub_select, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2327 "yacc_sql.tab.c"
    break;

  case 116:
#line 627 "yacc_sql.y"
                                                         {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, NULL, &CONTEXT->left_sub_select, 0, NULL, &CONTEXT->right_sub_select);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2337 "yacc_sql.tab.c"
    break;

  case 121:
#line 643 "yacc_sql.y"
                    {
			CONTEXT->condition_ops[CUR_SEL][CONTEXT->condition_op_length[CUR_SEL]++] = COND_AND;
		}
#line 2345 "yacc_sql.tab.c"
    break;

  case 122:
#line 646 "yacc_sql.y"
                     {
			CONTEXT->condition_ops[CUR_SEL][CONTEXT->condition_op_length[CUR_SEL]++] = COND_OR;
		}
#line 2353 "yacc_sql.tab.c"
    break;

  case 123:
#line 651 "yacc_sql.y"
                              {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2363 "yacc_sql.tab.c"
    break;

  case 124:
#line 656 "yacc_sql.y"
                                             {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 1, NULL, &CONTEXT->right_sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2373 "yacc_sql.tab.c"
    break;

  case 125:
#line 661 "yacc_sql.y"
                                            {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 1, NULL, &CONTEXT->left_sub_select, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2383 "yacc_sql.tab.c"
    break;

  case 126:
#line 666 "yacc_sql.y"
                                                         {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 1, NULL, &CONTEXT->left_sub_select, 1, NULL, &CONTEXT->right_sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2393 "yacc_sql.tab.c"
    break;

  case 127:
#line 671 "yacc_sql.y"
                                      {
			Condition condition;
			condition_init_exists(&condition, (yyvsp[-1].number), &CONTEXT->sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2403 "yacc_sql.tab.c"
    break;

  case 128:
#line 676 "yacc_sql.y"
                                       {
			Condition condition;
			condition_init_in(&condition, (yyvsp[-1].number), (yyvsp[-2].ast1), &CONTEXT->sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2413 "yacc_sql.tab.c"
    break;

  case 129:
#line 681 "yacc_sql.y"
                                    {
			Condition condition;
			condition_init_in_exprs(&condition, (yyvsp[-1].number), (yyvsp[-2].ast1), CONTEXT->in_exprs[CUR_SEL], CONTEXT->in_expr_length[CUR_SEL]);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
			CONTEXT->in_expr_length[CUR_SEL] = 0;
		}
#line 2424 "yacc_sql.tab.c"
    break;

  case 131:
#line 695 "yacc_sql.y"
                    {
			CONTEXT->in_exprs[CUR_SEL][CONTEXT->in_expr_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 2432 "yacc_sql.tab.c"
    break;

  case 134:
#line 706 "yacc_sql.y"
                        {
			(yyval.number) = 1;
		}
#line 2440 "yacc_sql.tab.c"
    break;

  case 135:
#line 709 "yacc_sql.y"
                              {
			(yyval.number) = 0;
		}
#line 2448 "yacc_sql.tab.c"
    break;

  case 136:
#line 714 "yacc_sql.y"
                    {
			(yyval.number) = 1;
		}
#line 2456 "yacc_sql.tab.c"
    break;

  case 137:
#line 717 "yacc_sql.y"
                          {
			(yyval.number) = 0;
		}
#line 2464 "yacc_sql.tab.c"
    break;

  case 138:
#line 723 "yacc_sql.y"
                                          {
			CONTEXT->update_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2474 "yacc_sql.tab.c"
    break;

  case 139:
#line 731 "yacc_sql.y"
                                          {
			CONTEXT->sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2484 "yacc_sql.tab.c"
    break;

  case 140:
#line 739 "yacc_sql.y"
                                          {
			CONTEXT->left_sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2494 "yacc_sql.tab.c"
    break;

  case 141:
#line 747 "yacc_sql.y"
                                          {
			CONTEXT->right_sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2504 "yacc_sql.tab.c"
    break;

  case 142:
#line 755 "yacc_sql.y"
                          {
			(yyval.ast1) = new_op_node(MATH_SUB, NULL, (yyvsp[0].ast1));
		}
#line 2512 "yacc_sql.tab.c"
    break;

  case 143:
#line 758 "yacc_sql.y"
                               {
			(yyval.ast1) = new_op_node(MATH_ADD, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2520 "yacc_sql.tab.c"
    break;

  case 144:
#line 761 "yacc_sql.y"
                                {
			(yyval.ast1) = new_op_node(MATH_SUB, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2528 "yacc_sql.tab.c"
    break;

  case 145:
#line 764 "yacc_sql.y"
                               {
			(yyval.ast1) = new_op_node(MATH_MUL, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2536 "yacc_sql.tab.c"
    break;

  case 146:
#line 767 "yacc_sql.y"
                                {
			(yyval.ast1) = new_op_node(MATH_DIV, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2544 "yacc_sql.tab.c"
    break;

  case 147:
#line 770 "yacc_sql.y"
                                    {
			(yyval.ast1) = (yyvsp[-1].ast1);
			(yyval.ast1)->l_brace++;
			(yyval.ast1)->r_brace++;
		}
#line 2554 "yacc_sql.tab.c"
    break;

  case 148:
#line 775 "yacc_sql.y"
                        {
			(yyval.ast1) = (yyvsp[0].ast1);
		}
#line 2562 "yacc_sql.tab.c"
    break;

  case 149:
#line 778 "yacc_sql.y"
                     {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			(yyval.ast1) = new_attr_node(&attr);
		}
#line 2572 "yacc_sql.tab.c"
    break;

  case 150:
#line 783 "yacc_sql.y"
                            {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			(yyval.ast1) = new_attr_node(&attr);
		}
#line 2582 "yacc_sql.tab.c"
    break;

  case 151:
#line 788 "yacc_sql.y"
                            {
			(yyval.ast1) = (yyvsp[0].ast1);
		}
#line 2590 "yacc_sql.tab.c"
    break;

  case 152:
#line 794 "yacc_sql.y"
             { CONTEXT->comp[CUR_SEL] = EQUAL_TO; }
#line 2596 "yacc_sql.tab.c"
    break;

  case 153:
#line 795 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = LESS_THAN; }
#line 2602 "yacc_sql.tab.c"
    break;

  case 154:
#line 796 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = GREAT_THAN; }
#line 2608 "yacc_sql.tab.c"
    break;

  case 155:
#line 797 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = LESS_EQUAL; }
#line 2614 "yacc_sql.tab.c"
    break;

  case 156:
#line 798 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = GREAT_EQUAL; }
#line 2620 "yacc_sql.tab.c"
    break;

  case 157:
#line 799 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = NOT_EQUAL; }
#line 2626 "yacc_sql.tab.c"
    break;

  case 158:
#line 800 "yacc_sql.y"
                       { CONTEXT->comp[CUR_SEL] = STR_LIKE; }
#line 2632 "yacc_sql.tab.c"
    break;

  case 159:
#line 801 "yacc_sql.y"
                           { CONTEXT->comp[CUR_SEL] = STR_NOT_LIKE; }
#line 2638 "yacc_sql.tab.c"
    break;

  case 160:
#line 802 "yacc_sql.y"
                      { CONTEXT->comp[CUR_SEL] = IS; }
#line 2644 "yacc_sql.tab.c"
    break;

  case 161:
#line 803 "yacc_sql.y"
                          { CONTEXT->comp[CUR_SEL] = IS_NOT; }
#line 2650 "yacc_sql.tab.c"
    break;

  case 162:
#line 808 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2659 "yacc_sql.tab.c"
    break;


#line 2663 "yacc_sql.tab.c"

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
#line 813 "yacc_sql.y"

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
