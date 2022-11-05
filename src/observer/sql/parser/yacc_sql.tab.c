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
#define YYLAST   401

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  167
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
     428,   436,   449,   451,   458,   460,   464,   469,   471,   474,
     476,   480,   487,   489,   493,   496,   499,   505,   511,   516,
     521,   526,   534,   537,   540,   547,   551,   554,   559,   561,
     565,   572,   579,   589,   590,   591,   592,   593,   597,   602,
     604,   607,   609,   613,   621,   623,   627,   630,   636,   641,
     646,   651,   658,   660,   662,   664,   667,   670,   675,   680,
     685,   690,   695,   700,   705,   715,   719,   724,   726,   730,
     733,   738,   741,   747,   755,   763,   771,   779,   782,   785,
     788,   791,   794,   799,   802,   807,   812,   818,   819,   820,
     821,   822,   823,   824,   825,   826,   827,   831
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
    -281,   315,  -281,    12,    59,  -281,   -54,    41,   -13,    17,
      31,   -27,    36,    49,    71,    73,    77,    56,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,    82,    62,  -281,    29,
      50,   126,    58,    63,    99,   100,   122,  -281,    69,    76,
     121,  -281,  -281,  -281,  -281,  -281,   123,  -281,   112,   113,
     114,   138,  -281,  -281,  -281,  -281,  -281,  -281,   138,  -281,
    -281,   118,  -281,  -281,  -281,   111,   -32,  -281,   117,   -33,
     127,   140,    98,   136,   142,  -281,  -281,   124,   166,   165,
     125,   119,   138,   138,   138,   146,   -38,   -56,   -47,    62,
     176,   133,  -281,  -281,    42,   138,   138,   138,   138,  -281,
     134,   139,   175,  -281,  -281,   177,   172,   102,   178,   164,
     180,   202,    18,   -21,    22,   147,  -281,  -281,  -281,   111,
     150,  -281,    80,   181,  -281,   -56,   -56,  -281,  -281,   182,
     144,   183,   154,  -281,   138,   186,     8,   169,  -281,    35,
     188,   237,   289,  -281,   171,   125,   165,   230,  -281,   138,
     138,  -281,   -32,   191,   174,  -281,  -281,   134,   195,  -281,
    -281,  -281,  -281,  -281,   -36,   184,   205,   203,   -59,   172,
     209,   206,  -281,  -281,  -281,  -281,   102,   249,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,   198,   199,   212,   -40,
    -281,   216,   212,     8,  -281,   -59,   180,   220,   190,    40,
     110,  -281,   150,   233,   221,   182,   224,  -281,   217,   223,
    -281,   256,   184,   138,   228,   186,  -281,  -281,    35,   236,
    -281,  -281,     8,  -281,   -59,  -281,     8,  -281,  -281,  -281,
     -59,   255,  -281,  -281,   260,  -281,  -281,   191,   277,   165,
     233,  -281,  -281,  -281,  -281,   243,   184,   263,   256,   203,
    -281,  -281,  -281,  -281,   273,   276,   -59,  -281,  -281,  -281,
     246,   298,  -281,  -281,   290,   256,   293,   291,  -281,  -281,
     138,   292,   313,   306,   304,  -281,  -281,  -281,   310,   276,
    -281,   238,   138,   138,   321,  -281,  -281,    48,   237,   314,
     311,   -59,   314,   322,  -281,  -281,  -281,  -281,   238,   212,
     212,   138,  -281,   138,   138,    48,  -281,   -59,  -281,   -59,
     311,   -59,   318,    27,  -281,  -281,   138,  -281,  -281,  -281,
    -281,   318,  -281
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
       0,    25,    26,    27,    23,    22,     0,    70,     0,     0,
       0,     0,    63,   103,   104,   105,   106,   107,     0,    60,
      61,   154,    62,    88,   153,    98,    95,   156,     0,    95,
       0,     0,     0,     0,     0,    30,    29,     0,     0,   122,
       0,     0,     0,     0,     0,   154,     0,   147,     0,     0,
       0,     0,    96,    91,     0,     0,     0,     0,     0,    90,
       0,     0,     0,    28,    36,     0,     0,     0,     0,     0,
      68,     0,     0,     0,     0,     0,   152,   155,    89,    98,
       0,    97,     0,     0,   151,   148,   149,   150,    52,    39,
       0,     0,     0,    37,     0,    58,     0,     0,   139,   124,
       0,     0,     0,    64,     0,     0,   122,     0,    92,     0,
       0,    99,    95,   109,     0,   100,   102,     0,     0,    47,
      48,    49,    50,    51,    43,     0,     0,    56,    55,     0,
       0,     0,   140,   126,   127,   123,     0,     0,   132,   157,
     158,   159,   160,   161,   162,   163,     0,   165,     0,     0,
     141,     0,     0,     0,    67,    66,    68,     0,     0,     0,
       0,   108,     0,   111,     0,    39,     0,    44,     0,    42,
      33,    34,     0,     0,     0,    58,    53,   145,   124,     0,
     164,   166,     0,   131,   130,   142,     0,   134,   133,   129,
     128,     0,    69,    65,     0,    93,    94,   109,     0,   122,
     111,   101,    40,    38,    45,     0,     0,     0,    34,    56,
      54,    59,   125,   144,     0,   137,   136,   143,   167,   110,
       0,    74,   112,    46,     0,    34,     0,     0,    57,   146,
       0,     0,     0,     0,    72,    41,    35,    31,     0,   137,
     135,     0,     0,     0,    79,    32,   138,   114,     0,     0,
      77,    76,     0,     0,    71,   116,   117,   113,     0,     0,
       0,     0,    75,     0,     0,   114,   121,   120,   119,   118,
      77,    73,    82,    84,   115,    78,     0,    80,    86,    85,
      81,    82,    83
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,  -214,  -248,  -281,  -281,  -281,   143,   192,
    -281,  -281,  -281,  -281,  -281,   185,   155,   106,   141,  -281,
    -281,  -281,   225,   161,  -281,     0,  -281,  -281,    68,    61,
    -281,    57,    51,  -281,  -281,   285,  -281,   -74,   259,  -281,
    -281,   179,   145,   148,  -281,    74,  -281,    86,  -153,   162,
    -281,   210,  -281,   115,   108,  -281,  -281,  -281,   200,  -280,
    -200,   -37,  -148,  -281
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   221,   257,    29,    30,    31,   168,   139,
     219,   274,   174,   140,    32,   145,   177,   224,   180,    74,
      33,    34,   120,   156,    35,   229,   294,   284,   300,   312,
     304,   322,   327,   330,    37,    75,    76,   103,   100,    77,
      78,   163,   213,   249,   250,   307,   308,   297,   118,   185,
     186,   149,   237,   265,   281,   150,   201,   204,   188,   151,
     233,    96,   198,    38
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      79,    36,   239,   207,   202,   109,   101,   101,   258,   126,
     277,   298,   105,   106,   107,   105,     5,    39,   217,    40,
     108,   230,    44,   108,   159,   235,   218,   286,   298,   127,
      47,    97,   128,   105,   106,   107,   328,    48,   105,   106,
     107,   108,   275,   102,   102,    41,   108,    45,    46,    50,
     105,   106,   107,    49,    61,   122,   123,   124,   108,   183,
     184,    62,    79,   329,    42,   158,    43,   160,   134,   135,
     136,   137,   305,   306,    63,    64,    65,    66,    67,    51,
     152,    68,    69,    70,    95,    56,    72,   245,   211,   105,
     106,   107,    52,   105,   106,   107,   271,   108,   105,   106,
     107,   108,    58,    59,    60,    80,   108,   178,    61,   316,
     318,   105,   106,   107,    53,    62,    54,   205,   132,   108,
      55,   133,   209,   210,   164,    57,    81,   165,    63,    64,
      65,    66,    67,    82,    83,    68,    69,    70,    71,    84,
      72,    73,    85,    86,    87,    88,   181,    90,   146,   152,
     309,   310,    89,    91,   313,    62,    99,   246,    92,    93,
      94,   234,    98,   104,   147,   240,   148,   111,    63,    64,
      65,    66,    67,   110,   112,    68,    69,    70,    95,   113,
      72,   105,   106,   107,    61,   114,   178,   116,   117,   108,
     125,    62,   169,   170,   171,   172,   173,   121,   130,   266,
     115,   119,   142,   241,    63,    64,    65,    66,    67,   131,
     138,    68,    69,    70,    95,   141,    72,   203,   144,   154,
     143,   153,   157,   127,    62,   155,   162,   167,   166,   175,
     176,   179,   264,   182,   187,   208,   212,    63,    64,    65,
      66,    67,   216,   266,    68,    69,    70,    95,   223,    72,
     214,   222,   226,   227,   299,   301,   302,     5,   232,   230,
     220,   231,   236,   243,   248,    62,   244,   253,   251,   255,
     254,   299,   317,   319,   301,   260,   321,   323,    63,    64,
      65,    66,    67,   263,   146,    68,    69,    70,    95,   323,
      72,    62,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   256,   267,   268,    63,    64,    65,    66,    67,   270,
     276,    68,    69,    70,    95,     2,    72,   273,     3,     4,
     279,   280,   282,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,   283,   287,   285,   288,   290,
     291,   292,   293,    17,   189,   190,   191,   192,   193,   194,
     195,   199,   197,   295,   200,   303,   311,   314,   252,   215,
     105,   106,   107,   326,   225,   278,   261,   242,   108,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   259,   320,
     206,   325,   332,   331,   129,   105,   106,   107,   161,   324,
     262,   247,   269,   108,   315,   289,   228,   296,   272,     0,
       0,   238
};

static const yytype_int16 yycheck[] =
{
      37,     1,   202,   156,   152,    79,    39,    39,   222,    47,
     258,   291,    71,    72,    73,    71,     8,     5,    54,     7,
      79,    61,    76,    79,    45,    65,    62,   275,   308,    76,
      43,    68,    79,    71,    72,    73,     9,    20,    71,    72,
      73,    79,   256,    76,    76,    33,    79,     6,     7,    76,
      71,    72,    73,    22,    46,    92,    93,    94,    79,    24,
      25,    53,    99,    36,     5,    47,     7,    45,   105,   106,
     107,   108,    24,    25,    66,    67,    68,    69,    70,    43,
     117,    73,    74,    75,    76,    29,    78,    47,   162,    71,
      72,    73,    43,    71,    72,    73,   249,    79,    71,    72,
      73,    79,    40,    41,    42,    76,    79,   144,    46,   309,
     310,    71,    72,    73,    43,    53,    43,   154,    76,    79,
      43,    79,   159,   160,    44,    43,    76,    47,    66,    67,
      68,    69,    70,     7,    76,    73,    74,    75,    76,    76,
      78,    79,    43,    43,    22,    76,   146,    26,    46,   186,
     298,   299,    76,    30,   302,    53,    45,    47,    46,    46,
      46,   198,    44,    46,    62,   202,    64,    27,    66,    67,
      68,    69,    70,    46,    76,    73,    74,    75,    76,    43,
      78,    71,    72,    73,    46,    43,   223,    21,    23,    79,
      44,    53,    48,    49,    50,    51,    52,    78,    22,   236,
      76,    76,    27,   203,    66,    67,    68,    69,    70,    76,
      76,    73,    74,    75,    76,    76,    78,    46,    46,    55,
      43,    43,    20,    76,    53,    45,    76,    45,    47,    46,
      76,    45,   232,    64,    46,     5,    45,    66,    67,    68,
      69,    70,    47,   280,    73,    74,    75,    76,    45,    78,
      76,    46,    43,    47,   291,   292,   293,     8,    46,    61,
      76,    62,    46,    43,    31,    53,    76,    43,    47,    46,
      53,   308,   309,   310,   311,    47,   313,   314,    66,    67,
      68,    69,    70,    47,    46,    73,    74,    75,    76,   326,
      78,    53,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    45,    47,    43,    66,    67,    68,    69,    70,    32,
      47,    73,    74,    75,    76,     0,    78,    74,     3,     4,
      47,    45,    76,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    37,    43,    47,    47,    47,
      27,    35,    38,    28,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    43,    65,    34,    45,    35,   215,   167,
      71,    72,    73,    45,   179,   259,   225,   206,    79,    55,
      56,    57,    58,    59,    60,    61,    62,    63,   223,   311,
     155,   320,   331,   326,    99,    71,    72,    73,   129,   315,
     228,   212,   247,    79,   308,   280,   186,   289,   250,    -1,
      -1,   201
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
     129,    39,    76,   128,    46,    71,    72,    73,    79,   128,
      46,    27,    76,    43,    43,    76,    21,    23,   139,    76,
     113,    78,   152,   152,   152,    44,    47,    76,    79,   126,
      22,    76,    76,    79,   152,   152,   152,   152,    76,   100,
     104,    76,    27,    43,    46,   106,    46,    62,    64,   142,
     146,   150,   152,    43,    55,    45,   114,    20,    47,    45,
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
     115,   116,   117,   117,   118,   118,   119,   120,   120,   121,
     121,   122,   123,   123,   124,   124,   124,   125,   126,   126,
     126,   126,   127,   127,   127,   128,   128,   128,   129,   129,
     130,   130,   130,   131,   131,   131,   131,   131,   132,   133,
     133,   134,   134,   135,   136,   136,   137,   137,   138,   138,
     138,   138,   139,   139,   140,   140,   141,   141,   142,   142,
     142,   142,   142,   142,   142,   143,   144,   145,   145,   146,
     146,   147,   147,   148,   149,   150,   151,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   154
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
       4,     2,     0,     3,     0,     1,     1,     1,     1,     3,
       2,     2,     4,     6,     6,     0,     1,     2,     0,     3,
       4,     6,     4,     1,     1,     1,     1,     1,     2,     0,
       3,     0,     2,     6,     0,     3,     1,     1,     3,     3,
       3,     3,     0,     3,     0,     3,     1,     1,     3,     3,
       3,     3,     2,     3,     3,     4,     1,     0,     3,     1,
       2,     1,     2,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     3,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     8
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
#line 1766 "yacc_sql.tab.c"
    break;

  case 23:
#line 197 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1774 "yacc_sql.tab.c"
    break;

  case 24:
#line 202 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1782 "yacc_sql.tab.c"
    break;

  case 25:
#line 208 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1790 "yacc_sql.tab.c"
    break;

  case 26:
#line 214 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1798 "yacc_sql.tab.c"
    break;

  case 27:
#line 220 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1806 "yacc_sql.tab.c"
    break;

  case 28:
#line 226 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1815 "yacc_sql.tab.c"
    break;

  case 29:
#line 232 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1823 "yacc_sql.tab.c"
    break;

  case 30:
#line 238 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1832 "yacc_sql.tab.c"
    break;

  case 31:
#line 245 "yacc_sql.y"
                                                                   {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
		}
#line 1841 "yacc_sql.tab.c"
    break;

  case 32:
#line 249 "yacc_sql.y"
                                                                                        {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
		}
#line 1850 "yacc_sql.tab.c"
    break;

  case 33:
#line 256 "yacc_sql.y"
                   {
			create_index_append_attributes(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
		}
#line 1858 "yacc_sql.tab.c"
    break;

  case 36:
#line 268 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1867 "yacc_sql.tab.c"
    break;

  case 37:
#line 275 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1876 "yacc_sql.tab.c"
    break;

  case 38:
#line 282 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
		}
#line 1885 "yacc_sql.tab.c"
    break;

  case 41:
#line 294 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-1].number), (yyvsp[-3].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1895 "yacc_sql.tab.c"
    break;

  case 42:
#line 300 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, (yyvsp[0].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1905 "yacc_sql.tab.c"
    break;

  case 43:
#line 307 "yacc_sql.y"
                            {
			(yyval.number) = 0;
		}
#line 1913 "yacc_sql.tab.c"
    break;

  case 44:
#line 310 "yacc_sql.y"
                           {
			(yyval.number) = 1;
		}
#line 1921 "yacc_sql.tab.c"
    break;

  case 45:
#line 313 "yacc_sql.y"
                             {
			(yyval.number) = 0;
		}
#line 1929 "yacc_sql.tab.c"
    break;

  case 46:
#line 318 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1935 "yacc_sql.tab.c"
    break;

  case 47:
#line 321 "yacc_sql.y"
                           { (yyval.number)=INTS;   }
#line 1941 "yacc_sql.tab.c"
    break;

  case 48:
#line 322 "yacc_sql.y"
                           { (yyval.number)=CHARS;  }
#line 1947 "yacc_sql.tab.c"
    break;

  case 49:
#line 323 "yacc_sql.y"
                           { (yyval.number)=FLOATS; }
#line 1953 "yacc_sql.tab.c"
    break;

  case 50:
#line 324 "yacc_sql.y"
                           { (yyval.number)=DATES;  }
#line 1959 "yacc_sql.tab.c"
    break;

  case 51:
#line 325 "yacc_sql.y"
                           { (yyval.number)=TEXTS;  }
#line 1965 "yacc_sql.tab.c"
    break;

  case 52:
#line 328 "yacc_sql.y"
                   {
			char *temp=(yyvsp[0].string); 
			snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
		}
#line 1974 "yacc_sql.tab.c"
    break;

  case 53:
#line 336 "yacc_sql.y"
                                                                 {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
#line 1983 "yacc_sql.tab.c"
    break;

  case 54:
#line 342 "yacc_sql.y"
                                                           {
			insert_append_exprs(&CONTEXT->ssql->sstr.insertion, CONTEXT->exprs[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
			CONTEXT->expr_length[CUR_SEL] = 0;
		}
#line 1992 "yacc_sql.tab.c"
    break;

  case 55:
#line 349 "yacc_sql.y"
                    {
			CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 2000 "yacc_sql.tab.c"
    break;

  case 60:
#line 364 "yacc_sql.y"
           {
			Value value;
			value_init_integer(&value, (yyvsp[0].number));
			(yyval.ast1) = new_value_node(&value);
		}
#line 2010 "yacc_sql.tab.c"
    break;

  case 61:
#line 369 "yacc_sql.y"
           {
			Value value;
			value_init_float(&value, (yyvsp[0].floats));
			(yyval.ast1) = new_value_node(&value);
		}
#line 2020 "yacc_sql.tab.c"
    break;

  case 62:
#line 374 "yacc_sql.y"
         {
			Value value;
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&value, (yyvsp[0].string));
			(yyval.ast1) = new_value_node(&value);
		}
#line 2031 "yacc_sql.tab.c"
    break;

  case 63:
#line 380 "yacc_sql.y"
                        {
			Value value;
			value_init_null(&value);
			(yyval.ast1) = new_value_node(&value);
		}
#line 2041 "yacc_sql.tab.c"
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
#line 2054 "yacc_sql.tab.c"
    break;

  case 65:
#line 400 "yacc_sql.y"
                                                               {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			updates_set_condition_ops(&CONTEXT->ssql->sstr.update, CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			CONTEXT->condition_length[CUR_SEL] = 0;
		}
#line 2065 "yacc_sql.tab.c"
    break;

  case 66:
#line 409 "yacc_sql.y"
                          {
			UpdatePair pair;
			update_pair_init(&pair, (yyvsp[-2].string), 0, NULL, (yyvsp[0].ast1));
			update_append_pair(&CONTEXT->ssql->sstr.update, &pair);
		}
#line 2075 "yacc_sql.tab.c"
    break;

  case 67:
#line 414 "yacc_sql.y"
                                      {
			UpdatePair pair;
			update_pair_init(&pair, (yyvsp[-2].string), 1, &CONTEXT->update_select, NULL);
			update_append_pair(&CONTEXT->ssql->sstr.update, &pair);
		}
#line 2085 "yacc_sql.tab.c"
    break;

  case 70:
#line 428 "yacc_sql.y"
                                      {
			CONTEXT->ssql->sstr.selection = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2095 "yacc_sql.tab.c"
    break;

  case 71:
#line 437 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			selects_append_conditions(&CONTEXT->selects[CUR_SEL], CONTEXT->conditions[CUR_SEL], CONTEXT->condition_length[CUR_SEL]);
			selects_set_condition_ops(&CONTEXT->selects[CUR_SEL], CONTEXT->condition_ops[CUR_SEL], CONTEXT->condition_op_length[CUR_SEL]);
			selects_append_joins(&CONTEXT->selects[CUR_SEL], CONTEXT->joins[CUR_SEL], CONTEXT->join_length[CUR_SEL]);
			selects_append_exprs(&CONTEXT->selects[CUR_SEL], CONTEXT->exprs[CUR_SEL], CONTEXT->expr_alias[CUR_SEL], CONTEXT->expr_length[CUR_SEL]);
			selects_set_order_info(&CONTEXT->selects[CUR_SEL], CONTEXT->orders[CUR_SEL], CONTEXT->order_attrs[CUR_SEL], CONTEXT->order_attr_length[CUR_SEL]);
			selects_set_group_by(&CONTEXT->selects[CUR_SEL], CONTEXT->group_bys[CUR_SEL], CONTEXT->group_by_length[CUR_SEL]);
	}
#line 2110 "yacc_sql.tab.c"
    break;

  case 73:
#line 451 "yacc_sql.y"
                               {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
		selects_set_having(&CONTEXT->selects[CUR_SEL], &condition);
	}
#line 2120 "yacc_sql.tab.c"
    break;

  case 76:
#line 464 "yacc_sql.y"
                    {
			CONTEXT->group_bys[CUR_SEL][CONTEXT->group_by_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 2128 "yacc_sql.tab.c"
    break;

  case 81:
#line 480 "yacc_sql.y"
                                 {
			CONTEXT->order_attrs[CUR_SEL][CONTEXT->order_attr_length[CUR_SEL]] = (yyvsp[-1].ast1);
			CONTEXT->orders[CUR_SEL][CONTEXT->order_attr_length[CUR_SEL]] = (yyvsp[0].order_policy1);
			CONTEXT->order_attr_length[CUR_SEL]++;
		}
#line 2138 "yacc_sql.tab.c"
    break;

  case 84:
#line 493 "yacc_sql.y"
                            {
			(yyval.order_policy1) = ORDER_ASC;
		}
#line 2146 "yacc_sql.tab.c"
    break;

  case 85:
#line 496 "yacc_sql.y"
                      {
			(yyval.order_policy1) = ORDER_ASC;
		}
#line 2154 "yacc_sql.tab.c"
    break;

  case 86:
#line 499 "yacc_sql.y"
                       {
			(yyval.order_policy1) = ORDER_DESC;
		}
#line 2162 "yacc_sql.tab.c"
    break;

  case 87:
#line 505 "yacc_sql.y"
                       {
			CONTEXT->select_length++;
		}
#line 2170 "yacc_sql.tab.c"
    break;

  case 88:
#line 511 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = new_attr_node(&attr);
	}
#line 2180 "yacc_sql.tab.c"
    break;

  case 89:
#line 516 "yacc_sql.y"
                      {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), "*");
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]++] = new_attr_node(&attr);
	}
#line 2190 "yacc_sql.tab.c"
    break;

  case 90:
#line 521 "yacc_sql.y"
                       {
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]] = (yyvsp[-1].ast1);
		CONTEXT->expr_alias[CUR_SEL][CONTEXT->expr_length[CUR_SEL]] = (yyvsp[0].string);
		CONTEXT->expr_length[CUR_SEL]++;
	}
#line 2200 "yacc_sql.tab.c"
    break;

  case 91:
#line 526 "yacc_sql.y"
                        {
		CONTEXT->exprs[CUR_SEL][CONTEXT->expr_length[CUR_SEL]] = (yyvsp[-1].ast1);
		CONTEXT->expr_alias[CUR_SEL][CONTEXT->expr_length[CUR_SEL]] = (yyvsp[0].string);
		CONTEXT->expr_length[CUR_SEL]++;
	}
#line 2210 "yacc_sql.tab.c"
    break;

  case 92:
#line 534 "yacc_sql.y"
                                 {
		(yyval.ast1) = new_func_node(LENGTHF, (yyvsp[-1].ast1), NULL);
	}
#line 2218 "yacc_sql.tab.c"
    break;

  case 93:
#line 537 "yacc_sql.y"
                                            {
		(yyval.ast1) = new_func_node(ROUNDF, (yyvsp[-3].ast1), (yyvsp[-1].ast1));
	}
#line 2226 "yacc_sql.tab.c"
    break;

  case 94:
#line 540 "yacc_sql.y"
                                                  {
		(yyval.ast1) = new_func_node(DATE_FORMATF, (yyvsp[-3].ast1), (yyvsp[-1].ast1));
	}
#line 2234 "yacc_sql.tab.c"
    break;

  case 95:
#line 547 "yacc_sql.y"
                            {
			(yyval.string) = NULL;
		}
#line 2242 "yacc_sql.tab.c"
    break;

  case 96:
#line 551 "yacc_sql.y"
                   {
			(yyval.string) = strdup((yyvsp[0].string));
		}
#line 2250 "yacc_sql.tab.c"
    break;

  case 97:
#line 554 "yacc_sql.y"
                        {
			(yyval.string) = strdup((yyvsp[0].string));
		}
#line 2258 "yacc_sql.tab.c"
    break;

  case 100:
#line 565 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 2270 "yacc_sql.tab.c"
    break;

  case 101:
#line 572 "yacc_sql.y"
                                                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 2282 "yacc_sql.tab.c"
    break;

  case 102:
#line 579 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			Aggregate aggr;
			aggregate_init(&aggr, CONTEXT->aggr_type[CUR_SEL], 1, &attr, NULL);
			(yyval.ast1) = new_aggr_node(&aggr);
		}
#line 2294 "yacc_sql.tab.c"
    break;

  case 103:
#line 589 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = MAXS; }
#line 2300 "yacc_sql.tab.c"
    break;

  case 104:
#line 590 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = MINS; }
#line 2306 "yacc_sql.tab.c"
    break;

  case 105:
#line 591 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = AVGS; }
#line 2312 "yacc_sql.tab.c"
    break;

  case 106:
#line 592 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = SUMS; }
#line 2318 "yacc_sql.tab.c"
    break;

  case 107:
#line 593 "yacc_sql.y"
                        { CONTEXT->aggr_type[CUR_SEL] = COUNTS; }
#line 2324 "yacc_sql.tab.c"
    break;

  case 108:
#line 597 "yacc_sql.y"
                            {
			selects_append_relation(&CONTEXT->selects[CUR_SEL], (yyvsp[-1].string), (yyvsp[0].string));
		}
#line 2332 "yacc_sql.tab.c"
    break;

  case 113:
#line 613 "yacc_sql.y"
                                                                    {
			Join join;
			join_init(&join, (yyvsp[-3].string), CONTEXT->join_conditions[CUR_SEL], CONTEXT->join_condition_length[CUR_SEL]);
			CONTEXT->joins[CUR_SEL][CONTEXT->join_length[CUR_SEL]++] = join;
			CONTEXT->join_condition_length[CUR_SEL] = 0;
		}
#line 2343 "yacc_sql.tab.c"
    break;

  case 116:
#line 627 "yacc_sql.y"
                    {
			CONTEXT->join_condition_ops[CUR_SEL][CONTEXT->join_condition_op_length[CUR_SEL]++] = COND_AND;
		}
#line 2351 "yacc_sql.tab.c"
    break;

  case 117:
#line 630 "yacc_sql.y"
                     {
			CONTEXT->join_condition_ops[CUR_SEL][CONTEXT->join_condition_op_length[CUR_SEL]++] = COND_OR;
		}
#line 2359 "yacc_sql.tab.c"
    break;

  case 118:
#line 636 "yacc_sql.y"
                              {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->join_condition_length[CUR_SEL]++] = condition;
		}
#line 2369 "yacc_sql.tab.c"
    break;

  case 119:
#line 641 "yacc_sql.y"
                                             {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, NULL, &CONTEXT->right_sub_select);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2379 "yacc_sql.tab.c"
    break;

  case 120:
#line 646 "yacc_sql.y"
                                            {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, NULL, &CONTEXT->left_sub_select, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2389 "yacc_sql.tab.c"
    break;

  case 121:
#line 651 "yacc_sql.y"
                                                         {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, NULL, &CONTEXT->left_sub_select, 0, NULL, &CONTEXT->right_sub_select);
			CONTEXT->join_conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2399 "yacc_sql.tab.c"
    break;

  case 126:
#line 667 "yacc_sql.y"
                    {
			CONTEXT->condition_ops[CUR_SEL][CONTEXT->condition_op_length[CUR_SEL]++] = COND_AND;
		}
#line 2407 "yacc_sql.tab.c"
    break;

  case 127:
#line 670 "yacc_sql.y"
                     {
			CONTEXT->condition_ops[CUR_SEL][CONTEXT->condition_op_length[CUR_SEL]++] = COND_OR;
		}
#line 2415 "yacc_sql.tab.c"
    break;

  case 128:
#line 675 "yacc_sql.y"
                              {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2425 "yacc_sql.tab.c"
    break;

  case 129:
#line 680 "yacc_sql.y"
                                             {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 0, (yyvsp[-2].ast1), NULL, 1, NULL, &CONTEXT->right_sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2435 "yacc_sql.tab.c"
    break;

  case 130:
#line 685 "yacc_sql.y"
                                            {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 1, NULL, &CONTEXT->left_sub_select, 0, (yyvsp[0].ast1), NULL);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2445 "yacc_sql.tab.c"
    break;

  case 131:
#line 690 "yacc_sql.y"
                                                         {
			Condition condition;
			condition_init(&condition, CONTEXT->comp[CUR_SEL], 1, NULL, &CONTEXT->left_sub_select, 1, NULL, &CONTEXT->right_sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2455 "yacc_sql.tab.c"
    break;

  case 132:
#line 695 "yacc_sql.y"
                                      {
			Condition condition;
			condition_init_exists(&condition, (yyvsp[-1].number), &CONTEXT->sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2465 "yacc_sql.tab.c"
    break;

  case 133:
#line 700 "yacc_sql.y"
                                       {
			Condition condition;
			condition_init_in(&condition, (yyvsp[-1].number), (yyvsp[-2].ast1), &CONTEXT->sub_select);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
		}
#line 2475 "yacc_sql.tab.c"
    break;

  case 134:
#line 705 "yacc_sql.y"
                                    {
			Condition condition;
			condition_init_in_exprs(&condition, (yyvsp[-1].number), (yyvsp[-2].ast1), CONTEXT->in_exprs[CUR_SEL], CONTEXT->in_expr_length[CUR_SEL]);
			CONTEXT->conditions[CUR_SEL][CONTEXT->condition_length[CUR_SEL]++] = condition;
			CONTEXT->in_expr_length[CUR_SEL] = 0;
		}
#line 2486 "yacc_sql.tab.c"
    break;

  case 136:
#line 719 "yacc_sql.y"
                    {
			CONTEXT->in_exprs[CUR_SEL][CONTEXT->in_expr_length[CUR_SEL]++] = (yyvsp[0].ast1);
		}
#line 2494 "yacc_sql.tab.c"
    break;

  case 139:
#line 730 "yacc_sql.y"
                        {
			(yyval.number) = 1;
		}
#line 2502 "yacc_sql.tab.c"
    break;

  case 140:
#line 733 "yacc_sql.y"
                              {
			(yyval.number) = 0;
		}
#line 2510 "yacc_sql.tab.c"
    break;

  case 141:
#line 738 "yacc_sql.y"
                    {
			(yyval.number) = 1;
		}
#line 2518 "yacc_sql.tab.c"
    break;

  case 142:
#line 741 "yacc_sql.y"
                          {
			(yyval.number) = 0;
		}
#line 2526 "yacc_sql.tab.c"
    break;

  case 143:
#line 747 "yacc_sql.y"
                                          {
			CONTEXT->update_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2536 "yacc_sql.tab.c"
    break;

  case 144:
#line 755 "yacc_sql.y"
                                          {
			CONTEXT->sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2546 "yacc_sql.tab.c"
    break;

  case 145:
#line 763 "yacc_sql.y"
                                          {
			CONTEXT->left_sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2556 "yacc_sql.tab.c"
    break;

  case 146:
#line 771 "yacc_sql.y"
                                          {
			CONTEXT->right_sub_select = CONTEXT->selects[CUR_SEL];
			clear_selection(CONTEXT, CUR_SEL);
			CONTEXT->select_length--;
		}
#line 2566 "yacc_sql.tab.c"
    break;

  case 147:
#line 779 "yacc_sql.y"
                          {
			(yyval.ast1) = new_op_node(MATH_SUB, NULL, (yyvsp[0].ast1));
		}
#line 2574 "yacc_sql.tab.c"
    break;

  case 148:
#line 782 "yacc_sql.y"
                               {
			(yyval.ast1) = new_op_node(MATH_ADD, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2582 "yacc_sql.tab.c"
    break;

  case 149:
#line 785 "yacc_sql.y"
                                {
			(yyval.ast1) = new_op_node(MATH_SUB, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2590 "yacc_sql.tab.c"
    break;

  case 150:
#line 788 "yacc_sql.y"
                               {
			(yyval.ast1) = new_op_node(MATH_MUL, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2598 "yacc_sql.tab.c"
    break;

  case 151:
#line 791 "yacc_sql.y"
                                {
			(yyval.ast1) = new_op_node(MATH_DIV, (yyvsp[-2].ast1), (yyvsp[0].ast1));
		}
#line 2606 "yacc_sql.tab.c"
    break;

  case 152:
#line 794 "yacc_sql.y"
                                    {
			(yyval.ast1) = (yyvsp[-1].ast1);
			(yyval.ast1)->l_brace++;
			(yyval.ast1)->r_brace++;
		}
#line 2616 "yacc_sql.tab.c"
    break;

  case 153:
#line 799 "yacc_sql.y"
                        {
			(yyval.ast1) = (yyvsp[0].ast1);
		}
#line 2624 "yacc_sql.tab.c"
    break;

  case 154:
#line 802 "yacc_sql.y"
                     {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			(yyval.ast1) = new_attr_node(&attr);
		}
#line 2634 "yacc_sql.tab.c"
    break;

  case 155:
#line 807 "yacc_sql.y"
                            {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			(yyval.ast1) = new_attr_node(&attr);
		}
#line 2644 "yacc_sql.tab.c"
    break;

  case 156:
#line 812 "yacc_sql.y"
                            {
			(yyval.ast1) = (yyvsp[0].ast1);
		}
#line 2652 "yacc_sql.tab.c"
    break;

  case 157:
#line 818 "yacc_sql.y"
             { CONTEXT->comp[CUR_SEL] = EQUAL_TO; }
#line 2658 "yacc_sql.tab.c"
    break;

  case 158:
#line 819 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = LESS_THAN; }
#line 2664 "yacc_sql.tab.c"
    break;

  case 159:
#line 820 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = GREAT_THAN; }
#line 2670 "yacc_sql.tab.c"
    break;

  case 160:
#line 821 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = LESS_EQUAL; }
#line 2676 "yacc_sql.tab.c"
    break;

  case 161:
#line 822 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = GREAT_EQUAL; }
#line 2682 "yacc_sql.tab.c"
    break;

  case 162:
#line 823 "yacc_sql.y"
         { CONTEXT->comp[CUR_SEL] = NOT_EQUAL; }
#line 2688 "yacc_sql.tab.c"
    break;

  case 163:
#line 824 "yacc_sql.y"
                       { CONTEXT->comp[CUR_SEL] = STR_LIKE; }
#line 2694 "yacc_sql.tab.c"
    break;

  case 164:
#line 825 "yacc_sql.y"
                           { CONTEXT->comp[CUR_SEL] = STR_NOT_LIKE; }
#line 2700 "yacc_sql.tab.c"
    break;

  case 165:
#line 826 "yacc_sql.y"
                      { CONTEXT->comp[CUR_SEL] = IS; }
#line 2706 "yacc_sql.tab.c"
    break;

  case 166:
#line 827 "yacc_sql.y"
                          { CONTEXT->comp[CUR_SEL] = IS_NOT; }
#line 2712 "yacc_sql.tab.c"
    break;

  case 167:
#line 832 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2721 "yacc_sql.tab.c"
    break;


#line 2725 "yacc_sql.tab.c"

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
#line 837 "yacc_sql.y"

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
