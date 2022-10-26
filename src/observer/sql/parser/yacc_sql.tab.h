/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CREATE = 258,                  /* CREATE  */
    DROP = 259,                    /* DROP  */
    TABLE = 260,                   /* TABLE  */
    TABLES = 261,                  /* TABLES  */
    INDEX = 262,                   /* INDEX  */
    SELECT = 263,                  /* SELECT  */
    DESC = 264,                    /* DESC  */
    SHOW = 265,                    /* SHOW  */
    SYNC = 266,                    /* SYNC  */
    INSERT = 267,                  /* INSERT  */
    DELETE = 268,                  /* DELETE  */
    UPDATE = 269,                  /* UPDATE  */
    TRX_BEGIN = 270,               /* TRX_BEGIN  */
    TRX_COMMIT = 271,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 272,            /* TRX_ROLLBACK  */
    HELP = 273,                    /* HELP  */
    EXIT = 274,                    /* EXIT  */
    INTO = 275,                    /* INTO  */
    VALUES = 276,                  /* VALUES  */
    FROM = 277,                    /* FROM  */
    WHERE = 278,                   /* WHERE  */
    AND = 279,                     /* AND  */
    SET = 280,                     /* SET  */
    ON = 281,                      /* ON  */
    LOAD = 282,                    /* LOAD  */
    DATA = 283,                    /* DATA  */
    INFILE = 284,                  /* INFILE  */
    INNER = 285,                   /* INNER  */
    JOIN = 286,                    /* JOIN  */
    SEMICOLON = 287,               /* SEMICOLON  */
    DOT = 288,                     /* DOT  */
    COMMA = 289,                   /* COMMA  */
    LBRACE = 290,                  /* LBRACE  */
    RBRACE = 291,                  /* RBRACE  */
    INT_T = 292,                   /* INT_T  */
    STRING_T = 293,                /* STRING_T  */
    FLOAT_T = 294,                 /* FLOAT_T  */
    DATE_T = 295,                  /* DATE_T  */
    EQ = 296,                      /* EQ  */
    LT = 297,                      /* LT  */
    GT = 298,                      /* GT  */
    LE = 299,                      /* LE  */
    GE = 300,                      /* GE  */
    NE = 301,                      /* NE  */
    LIKE = 302,                    /* LIKE  */
    NOT = 303,                     /* NOT  */
    MAX = 304,                     /* MAX  */
    MIN = 305,                     /* MIN  */
    AVG = 306,                     /* AVG  */
    SUM = 307,                     /* SUM  */
    COUNT = 308,                   /* COUNT  */
    SLASH = 309,                   /* SLASH  */
    PLUS = 310,                    /* PLUS  */
    MINUS = 311,                   /* MINUS  */
    NUMBER = 312,                  /* NUMBER  */
    FLOAT = 313,                   /* FLOAT  */
    ID = 314,                      /* ID  */
    PATH = 315,                    /* PATH  */
    SSS = 316,                     /* SSS  */
    STAR = 317,                    /* STAR  */
    STRING_V = 318                 /* STRING_V  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 93 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
	struct ast *ast1;
  char *string;
  int number;
  float floats;
	char *position;

#line 138 "yacc_sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (void *scanner);


#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
