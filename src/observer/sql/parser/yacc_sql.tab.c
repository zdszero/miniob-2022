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
    LENGTH = 295,
    ROUND = 296,
    DATE_FORMAT = 297,
    SEMICOLON = 298,
    DOT = 299,
    COMMA = 300,
    LBRACE = 301,
    RBRACE = 302,
    INT_T = 303,
    STRING_T = 304,
    FLOAT_T = 305,
    DATE_T = 306,
    TEXT_T = 307,
    NULL_T = 308,
    NULLABLE = 309,
    EQ = 310,
    LT = 311,
    GT = 312,
    LE = 313,
    GE = 314,
    NE = 315,
    LIKE = 316,
    NOT = 317,
    ISS = 318,
    EXISTSS = 319,
    INS = 320,
    MAX = 321,
    MIN = 322,
    AVG = 323,
    SUM = 324,
    COUNT = 325,
    SLASH = 326,
    PLUS = 327,
    MINUS = 328,
    NUMBER = 329,
    FLOAT = 330,
    ID = 331,
    PATH = 332,
    SSS = 333,
    STAR = 334,
    STRING_V = 335
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

#line 317 "yacc_sql.tab.c"

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
#define YYLAST   417

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  169
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  333

#define YYUNDEFTOK  2
#define YYMAXUTOK   335


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
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   165,   165,   167,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   192,   197,   202,   208,   214,   220,   226,   232,
     238,   245,   249,   256,   261,   263,   267,   274,   281,   287,
     289,   293,   299,   307,   310,   313,   318,   321,   322,   323,
     324,   325,   328,   336,   342,   349,   354,   356,   359,   361,
     364,   369,   374,   380,   388,   400,   409,   414,   421,   423,
     428,   436,   441,   454,   456,   463,   465,   469,   474,   476,
     479,   481,   485,   492,   494,   498,   501,   504,   510,   516,
     521,   526,   534,   537,   540,   543,   550,   554,   557,   562,
     564,   568,   575,   582,   592,   593,   594,   595,   596,   600,
     605,   607,   610,   612,   616,   624,   626,   630,   633,   639,
     644,   649,   654,   661,   663,   665,   667,   670,   673,   678,
     683,   688,   693,   698,   703,   708,   718,   722,   727,   729,
     733,   736,   741,   744,   750,   758,   766,   774,   782,   785,
     788,   791,   794,   797,   802,   805,   810,   815,   818,   824,
     825,   826,   827,   828,   829,   830,   831,   832,   833,   837
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
  "HAVING", "AS", "LENGTH", "ROUND", "DATE_FORMAT", "SEMICOLON", "DOT",
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
  "having", "group_by", "group_by_expr", "group_by_expr_list", "order_by",
  "order_attr", "order_attr_list", "order_policy", "begin_select",
  "select_expr", "func", "as_alias", "select_exprs", "aggr_func",
  "aggr_type", "rel", "rel_list", "inner_join_list", "inner_join",
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335
};
# endif

#define YYPACT_NINF (-281)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -281,   351,  -281,    13,    45,  -281,   -63,    58,   -17,    10,
      14,    -5,    11,    16,    35,    41,    60,    73,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,    61,    59,  -281,    31,
      32,   104,    37,    38,    72,    74,    96,  -281,    43,    44,
      98,  -281,  -281,  -281,  -281,  -281,    92,  -281,    90,    93,
      97,   139,  -281,  -281,  -281,  -281,  -281,  -281,   139,  -281,
    -281,    86,  -281,  -281,  -281,    99,  -281,  -281,   101,   -34,
     102,   132,    76,   117,   128,  -281,  -281,   112,   156,   164,
     113,   115,   139,   139,   139,   151,    84,   -52,   -62,    59,
     169,   -18,   124,   139,   139,   139,  -281,   139,  -281,   126,
     134,   174,  -281,  -281,   168,   170,   100,   184,   175,   183,
     209,   111,   -38,    18,   155,  -281,  -281,  -281,    99,   166,
      25,   206,  -281,  -281,   -52,   -52,  -281,  -281,   219,   173,
     220,   191,  -281,   139,   224,     7,   201,  -281,    68,   229,
     178,   325,  -281,   217,   113,   164,   273,  -281,   139,  -281,
     139,  -281,   -33,   234,   204,  -281,  -281,   126,   235,  -281,
    -281,  -281,  -281,  -281,   -22,   205,   242,   249,   -50,   170,
     257,   252,  -281,  -281,  -281,  -281,   100,   293,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,   243,   241,   256,   -49,
    -281,   259,   256,     7,  -281,   -50,   183,   263,   231,   125,
     147,  -281,   166,   277,   264,   219,   267,  -281,   260,   266,
    -281,   272,   205,   139,   271,   224,  -281,  -281,    68,   281,
    -281,  -281,     7,  -281,   -50,  -281,     7,  -281,  -281,  -281,
     -50,   286,  -281,  -281,   276,  -281,  -281,   234,   289,   164,
     277,  -281,  -281,  -281,  -281,   261,   205,   290,   272,   249,
    -281,  -281,  -281,  -281,   291,   294,   -50,  -281,  -281,  -281,
     269,   299,  -281,  -281,   306,   272,   303,   309,  -281,  -281,
     139,   310,   331,   336,   334,  -281,  -281,  -281,   330,   294,
    -281,   274,   139,   139,   340,  -281,  -281,    71,   178,   189,
     332,   -50,   189,   341,  -281,  -281,  -281,  -281,   274,   256,
     256,   139,  -281,   139,   139,    71,  -281,   -50,  -281,   -50,
     332,   -50,   333,    15,  -281,  -281,   139,  -281,  -281,  -281,
    -281,   333,  -281
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    88,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,     0,     0,    19,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,    25,    26,    27,    23,    22,     0,    70,     0,     0,
       0,     0,    63,   104,   105,   106,   107,   108,     0,    60,
      61,   155,    62,    89,   154,    99,   158,   157,     0,    96,
       0,     0,     0,     0,     0,    30,    29,     0,     0,   123,
       0,     0,     0,     0,     0,   155,     0,   148,     0,     0,
      71,     0,     0,     0,     0,     0,    97,     0,    91,     0,
       0,     0,    28,    36,     0,     0,     0,     0,     0,    68,
       0,     0,     0,     0,     0,   153,   156,    90,    99,     0,
       0,     0,    98,   152,   149,   150,   151,    52,    39,     0,
       0,     0,    37,     0,    58,     0,     0,   140,   125,     0,
       0,     0,    64,     0,     0,   123,     0,    92,     0,    93,
       0,   100,    96,   110,     0,   101,   103,     0,     0,    47,
      48,    49,    50,    51,    43,     0,     0,    56,    55,     0,
       0,     0,   141,   127,   128,   124,     0,     0,   133,   159,
     160,   161,   162,   163,   164,   165,     0,   167,     0,     0,
     142,     0,     0,     0,    67,    66,    68,     0,     0,     0,
       0,   109,     0,   112,     0,    39,     0,    44,     0,    42,
      33,    34,     0,     0,     0,    58,    53,   146,   125,     0,
     166,   168,     0,   132,   131,   143,     0,   135,   134,   130,
     129,     0,    69,    65,     0,    94,    95,   110,     0,   123,
     112,   102,    40,    38,    45,     0,     0,     0,    34,    56,
      54,    59,   126,   145,     0,   138,   137,   144,   169,   111,
       0,    75,   113,    46,     0,    34,     0,     0,    57,   147,
       0,     0,     0,     0,    73,    41,    35,    31,     0,   138,
     136,     0,     0,     0,    80,    32,   139,   115,     0,     0,
      78,    77,     0,     0,    72,   117,   118,   114,     0,     0,
       0,     0,    76,     0,     0,   115,   122,   121,   120,   119,
      78,    74,    83,    85,   116,    79,     0,    81,    87,    86,
      82,    83,    84
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,  -212,  -250,  -281,  -281,  -281,   160,   222,
    -281,  -281,  -281,  -281,  -281,   212,   171,   133,   176,  -281,
    -281,  -281,   239,   193,  -281,     0,  -281,  -281,    89,    75,
    -281,    77,    78,  -281,  -281,   307,  -281,   240,   279,  -281,
    -281,   196,   158,   161,  -281,    95,  -281,   105,  -151,   186,
    -281,   226,  -281,   135,   127,  -281,  -281,  -281,   216,  -280,
    -200,   -37,  -148,  -281
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   221,   257,    29,    30,    31,   168,   138,
     219,   274,   174,   139,    32,   144,   177,   224,   180,    74,
      33,    34,   119,   155,    35,   229,   294,   284,   300,   312,
     304,   322,   327,   330,    37,    75,    76,   108,   100,    77,
      78,   163,   213,   249,   250,   307,   308,   297,   117,   185,
     186,   148,   237,   265,   281,   149,   201,   204,   188,   150,
     233,    96,   198,    38
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      79,    36,   239,   202,   207,   102,   102,   158,   277,   159,
     258,   298,   230,    44,   126,     5,   235,   127,    39,   103,
      40,   103,   104,   105,   328,   286,    47,   107,   298,   107,
      48,    97,   217,   103,   104,   105,    49,   103,   104,   105,
     218,   107,   106,   106,   275,   107,    41,    58,    59,    60,
      42,   329,    43,    61,    51,   121,   122,   123,   130,    52,
      62,   131,    79,   160,    45,    46,   133,   134,   135,   164,
     136,    50,   165,    63,    64,    65,    66,    67,    53,   151,
      68,    69,    70,    95,    54,    72,   103,   104,   105,   103,
     104,   105,   183,   184,   107,   305,   306,   107,   271,    58,
      59,    60,    56,    55,    57,    61,   178,    80,    81,   316,
     318,    82,    62,    83,    84,    85,   205,    86,    87,    88,
      89,   209,    91,   210,    90,    63,    64,    65,    66,    67,
      98,   125,    68,    69,    70,    71,    92,    72,    73,    93,
      58,    59,    60,    94,    99,   181,   145,   101,   109,   151,
     309,   310,   111,    62,   313,   103,   104,   105,   157,   110,
     112,   234,   146,   107,   147,   240,    63,    64,    65,    66,
      67,   113,   245,    68,    69,    70,    95,   115,    72,    58,
      59,    60,   103,   104,   105,    61,   178,   116,   114,   118,
     107,   129,    62,   120,   246,   124,   103,   104,   105,   266,
     132,   141,   137,   241,   107,    63,    64,    65,    66,    67,
     140,   142,    68,    69,    70,    95,   143,    72,   103,   104,
     105,   169,   170,   171,   172,   173,   107,   152,   154,   156,
     153,   126,   264,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   162,   266,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   166,   299,   301,   302,    58,    59,    60,
     103,   104,   105,   203,   167,   182,   175,   176,   107,   179,
      62,   299,   317,   319,   301,   187,   321,   323,   208,   212,
     214,   220,   216,    63,    64,    65,    66,    67,   222,   323,
      68,    69,    70,    95,   223,    72,    58,    59,    60,   227,
     226,     5,   232,   231,   230,   236,   243,   244,   248,    62,
     253,   251,   255,   254,    58,    59,    60,   256,   260,   268,
     145,   270,    63,    64,    65,    66,    67,    62,   263,    68,
      69,    70,    95,   267,    72,   273,   283,   276,   279,   280,
      63,    64,    65,    66,    67,   282,   287,    68,    69,    70,
      95,     2,    72,   285,     3,     4,   288,   290,   291,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,   292,   293,   295,   303,   252,   314,   311,   326,    17,
     189,   190,   191,   192,   193,   194,   195,   199,   197,   215,
     200,   225,   278,   206,   259,   325,   103,   104,   105,   242,
     320,   261,   211,   331,   107,   269,   128,   161,   247,   332,
     324,   272,   228,   315,   262,   289,   296,   238
};

static const yytype_int16 yycheck[] =
{
      37,     1,   202,   151,   155,    39,    39,    45,   258,    47,
     222,   291,    61,    76,    76,     8,    65,    79,     5,    71,
       7,    71,    72,    73,     9,   275,    43,    79,   308,    79,
      20,    68,    54,    71,    72,    73,    22,    71,    72,    73,
      62,    79,    76,    76,   256,    79,    33,    40,    41,    42,
       5,    36,     7,    46,    43,    92,    93,    94,    76,    43,
      53,    79,    99,    45,     6,     7,   103,   104,   105,    44,
     107,    76,    47,    66,    67,    68,    69,    70,    43,   116,
      73,    74,    75,    76,    43,    78,    71,    72,    73,    71,
      72,    73,    24,    25,    79,    24,    25,    79,   249,    40,
      41,    42,    29,    43,    43,    46,   143,    76,    76,   309,
     310,     7,    53,    76,    76,    43,   153,    43,    22,    76,
      76,   158,    30,   160,    26,    66,    67,    68,    69,    70,
      44,    47,    73,    74,    75,    76,    46,    78,    79,    46,
      40,    41,    42,    46,    45,   145,    46,    46,    46,   186,
     298,   299,    76,    53,   302,    71,    72,    73,    47,    27,
      43,   198,    62,    79,    64,   202,    66,    67,    68,    69,
      70,    43,    47,    73,    74,    75,    76,    21,    78,    40,
      41,    42,    71,    72,    73,    46,   223,    23,    76,    76,
      79,    22,    53,    78,    47,    44,    71,    72,    73,   236,
      76,    27,    76,   203,    79,    66,    67,    68,    69,    70,
      76,    43,    73,    74,    75,    76,    46,    78,    71,    72,
      73,    48,    49,    50,    51,    52,    79,    43,    45,    20,
      55,    76,   232,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    76,   280,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    47,   291,   292,   293,    40,    41,    42,
      71,    72,    73,    46,    45,    64,    46,    76,    79,    45,
      53,   308,   309,   310,   311,    46,   313,   314,     5,    45,
      76,    76,    47,    66,    67,    68,    69,    70,    46,   326,
      73,    74,    75,    76,    45,    78,    40,    41,    42,    47,
      43,     8,    46,    62,    61,    46,    43,    76,    31,    53,
      43,    47,    46,    53,    40,    41,    42,    45,    47,    43,
      46,    32,    66,    67,    68,    69,    70,    53,    47,    73,
      74,    75,    76,    47,    78,    74,    37,    47,    47,    45,
      66,    67,    68,    69,    70,    76,    43,    73,    74,    75,
      76,     0,    78,    47,     3,     4,    47,    47,    27,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    35,    38,    43,    34,   215,    35,    45,    45,    28,
      55,    56,    57,    58,    59,    60,    61,    62,    63,   167,
      65,   179,   259,   154,   223,   320,    71,    72,    73,   206,
     311,   225,   162,   326,    79,   247,    99,   128,   212,   331,
     315,   250,   186,   308,   228,   280,   289,   201
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    82,     0,     3,     4,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    28,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    96,
      97,    98,   105,   111,   112,   115,   116,   125,   154,     5,
       7,    33,     5,     7,    76,     6,     7,    43,    20,    22,
      76,    43,    43,    43,    43,    43,    29,    43,    40,    41,
      42,    46,    53,    66,    67,    68,    69,    70,    73,    74,
      75,    76,    78,    79,   110,   126,   127,   130,   131,   152,
      76,    76,     7,    76,    76,    43,    43,    22,    76,    76,
      26,    30,    46,    46,    46,    76,   152,   152,    44,    45,
     129,    46,    39,    71,    72,    73,    76,    79,   128,    46,
      27,    76,    43,    43,    76,    21,    23,   139,    76,   113,
      78,   152,   152,   152,    44,    47,    76,    79,   126,    22,
      76,    79,    76,   152,   152,   152,   152,    76,   100,   104,
      76,    27,    43,    46,   106,    46,    62,    64,   142,   146,
     150,   152,    43,    55,    45,   114,    20,    47,    45,    47,
      45,   129,    76,   132,    44,    47,    47,    45,    99,    48,
      49,    50,    51,    52,   103,    46,    76,   107,   152,    45,
     109,   116,    64,    24,    25,   140,   141,    46,   149,    55,
      56,    57,    58,    59,    60,    61,    62,    63,   153,    62,
      65,   147,   153,    46,   148,   152,   113,   139,     5,   152,
     152,   128,    45,   133,    76,   100,    47,    54,    62,   101,
      76,    94,    46,    45,   108,   106,    43,    47,   142,   116,
      61,    62,    46,   151,   152,    65,    46,   143,   149,   151,
     152,   116,   114,    43,    76,    47,    47,   132,    31,   134,
     135,    47,    99,    43,    53,    46,    45,    95,    94,   107,
      47,   109,   140,    47,   116,   144,   152,    47,    43,   133,
      32,   139,   134,    74,   102,    94,    47,    95,   108,    47,
      45,   145,    76,    37,   118,    47,    95,    43,    47,   144,
      47,    27,    35,    38,   117,    43,   145,   138,   150,   152,
     119,   152,   152,    34,   121,    24,    25,   136,   137,   153,
     153,    45,   120,   153,    35,   138,   151,   152,   151,   152,
     119,   152,   122,   152,   136,   120,    45,   123,     9,    36,
     124,   122,   123
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    82,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    93,    94,    95,    95,    96,    97,    98,    99,
      99,   100,   100,   101,   101,   101,   102,   103,   103,   103,
     103,   103,   104,   105,   106,   107,   108,   108,   109,   109,
     110,   110,   110,   110,   111,   112,   113,   113,   114,   114,
     115,   116,   116,   117,   117,   118,   118,   119,   120,   120,
     121,   121,   122,   123,   123,   124,   124,   124,   125,   126,
     126,   126,   127,   127,   127,   127,   128,   128,   128,   129,
     129,   130,   130,   130,   131,   131,   131,   131,   131,   132,
     133,   133,   134,   134,   135,   136,   136,   137,   137,   138,
     138,   138,   138,   139,   139,   140,   140,   141,   141,   142,
     142,   142,   142,   142,   142,   142,   143,   144,   145,   145,
     146,   146,   147,   147,   148,   149,   150,   151,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   154
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
       2,     3,    11,     0,     4,     0,     4,     1,     0,     3,
       0,     4,     2,     0,     3,     0,     1,     1,     1,     1,
       3,     2,     4,     4,     6,     6,     0,     1,     2,     0,
       3,     4,     6,     4,     1,     1,     1,     1,     1,     2,
       0,     3,     0,     2,     6,     0,     3,     1,     1,     3,
       3,     3,     3,     0,     3,     0,     3,     1,     1,     3,
       3,     3,     3,     2,     3,     3,     4,     1,     0,     3,
       1,     2,     1,     2,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     8
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
#line 192 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1768 "yacc_sql.tab.c"
    break;

  case 23:
#line 197 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1776 "yacc_sql.tab.c"
    break;

  case 24:
#line 202 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1784 "yacc_sql.tab.c"
    break;

  case 25:
#line 208 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1792 "yacc_sql.tab.c"
    break;

  case 26:
#line 214 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1800 "yacc_sql.tab.c"
    break;

  case 27:
#line 220 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1808 "yacc_sql.tab.c"
    break;

  case 28:
#line 226 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1817 "yacc_sql.tab.c"
    break;

  case 29:
#line 232 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1825 "yacc_sql.tab.c"
    break;

  case 30:
#line 238 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1834 "yacc_sql.tab.c"
    break;

  case 31:
#line 245 "yacc_sql.y"
                                                                   {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
		}
#line 1843 "yacc_sql.tab.c"
    break;

  case 32:
#line 249 "yacc_sql.y"
                                                                                        {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
		}
#line 1852 "yacc_sql.tab.c"
    break;

  case 33:
#line 256 "yacc_sql.y"
                   {
			create_index_append_attributes(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
		}
#line 1860 "yacc_sql.tab.c"
    break;

  case 36:
#line 268 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1869 "yacc_sql.tab.c"
    break;

  case 37:
#line 275 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1878 "yacc_sql.tab.c"
    break;

  case 38:
#line 282 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
		}
#line 1887 "yacc_sql.tab.c"
    break;

  case 41:
#line 294 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-1].number), (yyvsp[-3].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1897 "yacc_sql.tab.c"
    break;

  case 42:
#line 300 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, (yyvsp[0].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1907 "yacc_sql.tab.c"
    break;

  case 43:
#line 307 "yacc_sql.y"
                            {
			(yyval.number) = 0;
		}
#line 1915 "yacc_sql.tab.c"
    break;

  case 44:
#line 310 "yacc_sql.y"
                           {
			(yyval.number) = 1;
		}
#line 1923 "yacc_sql.tab.c"
    break;

  case 45:
#line 313 "yacc_sql.y"
                             {
			(yyval.number) = 0;
		}
#line 1931 "yacc_sql.tab.c"
    break;

  case 46:
#line 318 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1937 "yacc_sql.tab.c"
    break;

  case 47:
#line 321 "yacc_sql.y"
                           { (yyval.number)=INTS;   }
#line 1943 "yacc_sql.tab.c"
    break;

  case 48:
#line 322 "yacc_sql.y"
                           { (yyval.number)=CHARS;  }
#line 1949 "yacc_sql.tab.c"
    break;

  case 49:
#line 323 "yacc_sql.y"
                           { (yyval.number)=FLOATS; }
#line 1955 "yacc_sql.tab.c"
    break;

  case 50:
#line 324 "yacc_sql.y"
                           { (yyval.number)=DATES;  }
#line 1961 "yacc_sql.tab.c"
    break;

  case 51:
#line 325 "yacc_sql.y"
                           { (yyval.number)=TEXTS;  }
#line 1967 "yacc_sql.tab.c"
    break;

  case 52:
#line 328 "yacc_sql.y"
                   {
			char *temp=(yyvsp[0].string); 
			snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
		}
#line 1976 "yacc_sql.tab.c"
    break;

  case 53:
#line 336 "yacc_sql.y"
                                                                 {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
#line 1985 "yacc_sql.tab.c"
    break;

  case 54:
#line 342 "yacc_sql.y"
                                                           {
			insert_append_exprs(&CONTEXT->ssql->sstr.insertion, CONTEXT->exprs[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
			CONTEXT->expr_length[CUR_SEL] = 0;
		}
#line 1994 "yacc_sql.tab.c"
    break;

  case 55:
#line 349 "yacc_sql.y"
                    {
			CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 2002 "yacc_sql.tab.c"
    break;

  case 60:
#line 364 "yacc_sql.y"
           {
			Value value;
			value_init_integer(&value, (yyvsp[0].number));
			(yyval.ast1) = new_value_node(&value);
		}
#line 2012 "yacc_sql.tab.c"
    break;

  case 61:
#line 369 "yacc_sql.y"
           {
			Value value;
			value_init_float(&value, (yyvsp[0].floats));
			(yyval.ast1) = new_value_node(&value);
		}
#line 2022 "yacc_sql.tab.c"
    break;

  case 62:
#line 374 "yacc_sql.y"
         {
			Value value;
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&value, (yyvsp[0].string));
			(yyval.ast1) = new_value_node(&value);
		}
#line 2033 "yacc_sql.tab.c"
    break;

  case 63:
#line 380 "yacc_sql.y"
                        {
			Value value;
			value_init_null(&value);
			(yyval.ast1) = new_value_node(&value);
		}
#line 2043 "yacc_sql.tab.c"
    break;

  case 64:
#line 389 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			deletes_set_condition_ops(&CONTEXT->ssql->sstr.deletion, CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			CONTEXT->condition_length[CUR_SEL] = 0;	
    }
#line 2056 "yacc_sql.tab.c"
    break;

  case 65:
#line 400 "yacc_sql.y"
                                                               {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			updates_set_condition_ops(&CONTEXT->ssql->sstr.update, CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			CONTEXT->condition_length[CUR_SEL] = 0;
		}
#line 2067 "yacc_sql.tab.c"
    break;

  case 66:
#line 409 "yacc_sql.y"
                          {
			UpdatePair pair;
			update_pair_init(&pair, (yyvsp[-2].string), 0, NULL, (yyvsp[0].ast1));
			update_append_pair(&CONTEXT->ssql->sstr.update, &pair);
		}
#line 2077 "yacc_sql.tab.c"
    break;

  case 67:
#line 414 "yacc_sql.y"
                                      {
			UpdatePair pair;
			update_pair_init(&pair, (yyvsp[-2].string), 1, &CONTEXT->update_select, NULL);
			update_append_pair(&CONTEXT->ssql->sstr.update, &pair);
		}
#line 2087 "yacc_sql.tab.c"
    break;

  case 70:
#line 428 "yacc_sql.y"
                                      {
			CONTEXT->ssql->sstr.selection = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2097 "yacc_sql.tab.c"
    break;

  case 71:
#line 436 "yacc_sql.y"
                                        {
		CONTEXT->ssql->flag=SCF_SELECT;//"select";

		selects_append_exprs(&CONTEXT->selects[CUR_SEL], CONTEXT->exprs[CUR_SEL], CONTEXT->expr_alias[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
	}
#line 2107 "yacc_sql.tab.c"
    break;

  case 72:
#line 442 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			selects_append_conditions(&CONTEXT->selects[CUR_SEL], CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			selects_set_condition_ops(&CONTEXT->selects[CUR_SEL], CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			selects_append_joins(&CONTEXT->selects[CUR_SEL], CONTEXT->joins[CUR_SEL], CONTEXT->join_length[CUR_SEL]);
			selects_append_exprs(&CONTEXT->selects[CUR_SEL], CONTEXT->exprs[CUR_SEL], CONTEXT->expr_alias[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
			selects_set_order_info(&CONTEXT->selects[CUR_SEL], CONTEXT->orders[CUR_SEL], CONTEXT->order_attrs[CUR_SEL], CONTEXT->order_attr_length[CUR_SEL]);
			selects_set_group_by(&CONTEXT->selects[CUR_SEL], CONTEXT->group_bys[CUR_SEL], CONTEXT->group_by_length[CUR_SEL]);
	}
#line 2122 "yacc_sql.tab.c"
    break;

  case 74:
#line 456 "yacc_sql.y"
                               {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
		selects_set_having(&CONTEXT->selects[CUR_SEL], &condition);
	}
#line 2132 "yacc_sql.tab.c"
    break;

  case 77:
#line 469 "yacc_sql.y"
                    {
			CONTEXT->group_bys[CUR_SEL][CONTEXT->group_by_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 2140 "yacc_sql.tab.c"
    break;

  case 82:
#line 485 "yacc_sql.y"
                                 {
			CONTEXT->order_attrs[CUR_SEL][CONTEXT->order_attr_length[CUR_SEL]] = (yyvsp[-1].ast1);
			CONTEXT->orders[CUR_SEL][CONTEXT->order_attr_length[CUR_SEL]] = (yyvsp[0].order_policy1);
			CONTEXT->order_attr_length[CUR_SEL]++;
		}
#line 2150 "yacc_sql.tab.c"
    break;

  case 85:
#line 498 "yacc_sql.y"
                            {
			(yyval.order_policy1) = ORDER_ASC;
		}
#line 2158 "yacc_sql.tab.c"
    break;

  case 86:
#line 501 "yacc_sql.y"
                      {
			(yyval.order_policy1) = ORDER_ASC;
		}
#line 2166 "yacc_sql.tab.c"
    break;

  case 87:
#line 504 "yacc_sql.y"
                       {
			(yyval.order_policy1) = ORDER_DESC;
		}
#line 2174 "yacc_sql.tab.c"
    break;

  case 88:
#line 510 "yacc_sql.y"
                       {
			CONTEXT->select_length++;
		}
#line 2182 "yacc_sql.tab.c"
    break;

  case 89:
#line 516 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = new_attr_node(&attr);
	}
#line 2192 "yacc_sql.tab.c"
    break;

  case 90:
#line 521 "yacc_sql.y"
                      {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), "*");
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = new_attr_node(&attr);
	}
#line 2202 "yacc_sql.tab.c"
    break;

  case 91:
#line 526 "yacc_sql.y"
                       {
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]] = (yyvsp[-1].ast1);
		CONTEXT->expr_alias[CUR_SEL][CONTEXT->expr_length[CUR_SEL]] = (yyvsp[0].string);
		CONTEXT->expr_length[CUR_SEL]++;
	}
#line 2212 "yacc_sql.tab.c"
    break;

  case 92:
#line 534 "yacc_sql.y"
                                 {
		(yyval.ast1) = new_func_node(LENGTHF, (yyvsp[-1].ast1), NULL);
	}
#line 2220 "yacc_sql.tab.c"
    break;

  case 93:
#line 537 "yacc_sql.y"
                                  {
		(yyval.ast1) = new_func_node(ROUNDF, (yyvsp[-1].ast1), NULL);
	}
#line 2228 "yacc_sql.tab.c"
    break;

  case 94:
#line 540 "yacc_sql.y"
                                            {
		(yyval.ast1) = new_func_node(ROUNDF, (yyvsp[-3].ast1), (yyvsp[-1].ast1));
	}
#line 2236 "yacc_sql.tab.c"
    break;

  case 95:
#line 543 "yacc_sql.y"
                                                  {
		(yyval.ast1) = new_func_node(DATE_FORMATF, (yyvsp[-3].ast1), (yyvsp[-1].ast1));
	}
#line 2244 "yacc_sql.tab.c"
    break;

  case 96:
#line 550 "yacc_sql.y"
                            {
			(yyval.string) = NULL;
		}
#line 2252 "yacc_sql.tab.c"
    break;

  case 97:
#line 554 "yacc_sql.y"
                   {
			(yyval.string) = strdup((yyvsp[0].string));
		}
#line 2260 "yacc_sql.tab.c"
    break;

  case 98:
#line 557 "yacc_sql.y"
                        {
			(yyval.string) = strdup((yyvsp[0].string));
		}
#line 2268 "yacc_sql.tab.c"
    break;

  case 101:
#line 568 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 2280 "yacc_sql.tab.c"
    break;

  case 102:
#line 575 "yacc_sql.y"
                                                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 2292 "yacc_sql.tab.c"
    break;

  case 103:
#line 582 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 2304 "yacc_sql.tab.c"
    break;

  case 104:
#line 592 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = MAXS; }
#line 2310 "yacc_sql.tab.c"
    break;

  case 105:
#line 593 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = MINS; }
#line 2316 "yacc_sql.tab.c"
    break;

  case 106:
#line 594 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = AVGS; }
#line 2322 "yacc_sql.tab.c"
    break;

  case 107:
#line 595 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = SUMS; }
#line 2328 "yacc_sql.tab.c"
    break;

  case 108:
#line 596 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = COUNTS; }
#line 2334 "yacc_sql.tab.c"
    break;

  case 109:
#line 600 "yacc_sql.y"
                            {
			selects_append_relation(&CONTEXT->selects[CUR_SEL], (yyvsp[-1].string), (yyvsp[0].string));
		}
#line 2342 "yacc_sql.tab.c"
    break;

  case 114:
#line 616 "yacc_sql.y"
                                                                    {
			Join join;
			join_init(&join, (yyvsp[-3].string), CONTEXT->join_conditions[CUR_SEL], CONTEXT->join_condition_length[CUR_SEL]);
			CONTEXT->joins[CUR_SEL][CONTEXT->join_length[CUR_SEL]++] = join;
			CONTEXT->join_condition_length[CUR_SEL] = 0;
		}
#line 2353 "yacc_sql.tab.c"
    break;

  case 117:
#line 630 "yacc_sql.y"
                    {
			CONTEXT->join_condition_ops[CUR_SEL][CONTEXT->join_condition_op_length[CUR_SEL]++] = COND_AND;
		}
#line 2361 "yacc_sql.tab.c"
    break;

  case 118:
#line 633 "yacc_sql.y"
                     {
			CONTEXT->join_condition_ops[CUR_SEL][CONTEXT->join_condition_op_length[CUR_SEL]++] = COND_OR;
		}
#line 2369 "yacc_sql.tab.c"
    break;

  case 119:
#line 639 "yacc_sql.y"
                              {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->join_condition_length[CUR_SEL]++] = condition;
		}
#line 2379 "yacc_sql.tab.c"
    break;

  case 120:
#line 644 "yacc_sql.y"
                                             {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, NULL, &CONTEXT->right_sub_select);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2389 "yacc_sql.tab.c"
    break;

  case 121:
#line 649 "yacc_sql.y"
                                            {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, NULL, &CONTEXT->left_sub_select, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2399 "yacc_sql.tab.c"
    break;

  case 122:
#line 654 "yacc_sql.y"
                                                         {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, NULL, &CONTEXT->left_sub_select, 0, NULL, &CONTEXT->right_sub_select);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2409 "yacc_sql.tab.c"
    break;

  case 127:
#line 670 "yacc_sql.y"
                    {
			CONTEXT->condition_ops[CUR_SEL][CONTEXT->condition_op_length[CUR_SEL]++] = COND_AND;
		}
#line 2417 "yacc_sql.tab.c"
    break;

  case 128:
#line 673 "yacc_sql.y"
                     {
			CONTEXT->condition_ops[CUR_SEL][CONTEXT->condition_op_length[CUR_SEL]++] = COND_OR;
		}
#line 2425 "yacc_sql.tab.c"
    break;

  case 129:
#line 678 "yacc_sql.y"
                              {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2435 "yacc_sql.tab.c"
    break;

  case 130:
#line 683 "yacc_sql.y"
                                             {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 1, NULL, &CONTEXT->right_sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2445 "yacc_sql.tab.c"
    break;

  case 131:
#line 688 "yacc_sql.y"
                                            {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 1, NULL, &CONTEXT->left_sub_select, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2455 "yacc_sql.tab.c"
    break;

  case 132:
#line 693 "yacc_sql.y"
                                                         {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 1, NULL, &CONTEXT->left_sub_select, 1, NULL, &CONTEXT->right_sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2465 "yacc_sql.tab.c"
    break;

  case 133:
#line 698 "yacc_sql.y"
                                      {
			Condition condition;
			condition_init_exists(&condition, (yyvsp[-1].number), &CONTEXT->sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2475 "yacc_sql.tab.c"
    break;

  case 134:
#line 703 "yacc_sql.y"
                                       {
			Condition condition;
			condition_init_in(&condition, (yyvsp[-1].number), (yyvsp[-2].ast1), &CONTEXT->sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2485 "yacc_sql.tab.c"
    break;

  case 135:
#line 708 "yacc_sql.y"
                                    {
			Condition condition;
			condition_init_in_exprs(&condition, (yyvsp[-1].number), (yyvsp[-2].ast1), CONTEXT->in_exprs[CUR_SEL], CONTEXT->in_expr_length[CUR_SEL]);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
			CONTEXT->in_expr_length[CUR_SEL] = 0;
		}
#line 2496 "yacc_sql.tab.c"
    break;

  case 137:
#line 722 "yacc_sql.y"
                    {
			CONTEXT->in_exprs[CUR_SEL][CONTEXT->in_expr_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 2504 "yacc_sql.tab.c"
    break;

  case 140:
#line 733 "yacc_sql.y"
                        {
			(yyval.number) = 1;
		}
#line 2512 "yacc_sql.tab.c"
    break;

  case 141:
#line 736 "yacc_sql.y"
                              {
			(yyval.number) = 0;
		}
#line 2520 "yacc_sql.tab.c"
    break;

  case 142:
#line 741 "yacc_sql.y"
                    {
			(yyval.number) = 1;
		}
#line 2528 "yacc_sql.tab.c"
    break;

  case 143:
#line 744 "yacc_sql.y"
                          {
			(yyval.number) = 0;
		}
#line 2536 "yacc_sql.tab.c"
    break;

  case 144:
#line 750 "yacc_sql.y"
                                          {
			CONTEXT->update_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2546 "yacc_sql.tab.c"
    break;

  case 145:
#line 758 "yacc_sql.y"
                                          {
			CONTEXT->sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2556 "yacc_sql.tab.c"
    break;

  case 146:
#line 766 "yacc_sql.y"
                                          {
			CONTEXT->left_sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2566 "yacc_sql.tab.c"
    break;

  case 147:
#line 774 "yacc_sql.y"
                                          {
			CONTEXT->right_sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2576 "yacc_sql.tab.c"
    break;

  case 148:
#line 782 "yacc_sql.y"
                          {
			(yyval.ast1) = new_op_node(MATH_SUB, NULL, (yyvsp[0].ast1));
		}
#line 2584 "yacc_sql.tab.c"
    break;

  case 149:
#line 785 "yacc_sql.y"
                               {
			(yyval.ast1) = new_op_node(MATH_ADD, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2592 "yacc_sql.tab.c"
    break;

  case 150:
#line 788 "yacc_sql.y"
                                {
			(yyval.ast1) = new_op_node(MATH_SUB, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2600 "yacc_sql.tab.c"
    break;

  case 151:
#line 791 "yacc_sql.y"
                               {
			(yyval.ast1) = new_op_node(MATH_MUL, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2608 "yacc_sql.tab.c"
    break;

  case 152:
#line 794 "yacc_sql.y"
                                {
			(yyval.ast1) = new_op_node(MATH_DIV, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2616 "yacc_sql.tab.c"
    break;

  case 153:
#line 797 "yacc_sql.y"
                                    {
			(yyval.ast1) = (yyvsp[-1].ast1);
			(yyval.ast1)->l_brace++;
			(yyval.ast1)->r_brace++;
		}
#line 2626 "yacc_sql.tab.c"
    break;

  case 154:
#line 802 "yacc_sql.y"
                        {
			(yyval.ast1) = (yyvsp[0].ast1);
		}
#line 2634 "yacc_sql.tab.c"
    break;

  case 155:
#line 805 "yacc_sql.y"
                     {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			(yyval.ast1) = new_attr_node(&attr);
		}
#line 2644 "yacc_sql.tab.c"
    break;

  case 156:
#line 810 "yacc_sql.y"
                            {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			(yyval.ast1) = new_attr_node(&attr);
		}
#line 2654 "yacc_sql.tab.c"
    break;

  case 157:
#line 815 "yacc_sql.y"
                            {
			(yyval.ast1) = (yyvsp[0].ast1);
		}
#line 2662 "yacc_sql.tab.c"
    break;

  case 158:
#line 818 "yacc_sql.y"
                       {
			(yyval.ast1) = (yyvsp[0].ast1);
		}
#line 2670 "yacc_sql.tab.c"
    break;

  case 159:
#line 824 "yacc_sql.y"
             { CONTEXT->comp[CUR_SEL] = EQUAL_TO; }
#line 2676 "yacc_sql.tab.c"
    break;

  case 160:
#line 825 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = LESS_THAN; }
#line 2682 "yacc_sql.tab.c"
    break;

  case 161:
#line 826 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = GREAT_THAN; }
#line 2688 "yacc_sql.tab.c"
    break;

  case 162:
#line 827 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = LESS_EQUAL; }
#line 2694 "yacc_sql.tab.c"
    break;

  case 163:
#line 828 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = GREAT_EQUAL; }
#line 2700 "yacc_sql.tab.c"
    break;

  case 164:
#line 829 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = NOT_EQUAL; }
#line 2706 "yacc_sql.tab.c"
    break;

  case 165:
#line 830 "yacc_sql.y"
                       { CONTEXT->comp[CUR_SEL] = STR_LIKE; }
#line 2712 "yacc_sql.tab.c"
    break;

  case 166:
#line 831 "yacc_sql.y"
                           { CONTEXT->comp[CUR_SEL] = STR_NOT_LIKE; }
#line 2718 "yacc_sql.tab.c"
    break;

  case 167:
#line 832 "yacc_sql.y"
                      { CONTEXT->comp[CUR_SEL] = IS; }
#line 2724 "yacc_sql.tab.c"
    break;

  case 168:
#line 833 "yacc_sql.y"
                          { CONTEXT->comp[CUR_SEL] = IS_NOT; }
#line 2730 "yacc_sql.tab.c"
    break;

  case 169:
#line 838 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2739 "yacc_sql.tab.c"
    break;


#line 2743 "yacc_sql.tab.c"

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
#line 843 "yacc_sql.y"

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
