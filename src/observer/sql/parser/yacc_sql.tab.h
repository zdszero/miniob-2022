/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 147 "yacc_sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
