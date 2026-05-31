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

#ifndef YY_YY_PARSER_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_PARSER_TAB_H_INCLUDED
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
    NUM = 258,                     /* NUM  */
    FLOAT_NUM = 259,               /* FLOAT_NUM  */
    ID = 260,                      /* ID  */
    PLUS = 261,                    /* PLUS  */
    PLUS_ATRIBUTION = 262,         /* PLUS_ATRIBUTION  */
    MINUS = 263,                   /* MINUS  */
    MINUS_ATRIBUTION = 264,        /* MINUS_ATRIBUTION  */
    TIMES = 265,                   /* TIMES  */
    TIMES_ATRIBUTION = 266,        /* TIMES_ATRIBUTION  */
    DIV = 267,                     /* DIV  */
    DIV_ATRIBUTION = 268,          /* DIV_ATRIBUTION  */
    INT_DIV = 269,                 /* INT_DIV  */
    INT_DIV_ATRIBUTION = 270,      /* INT_DIV_ATRIBUTION  */
    INCREMENT = 271,               /* INCREMENT  */
    ASSIGN = 272,                  /* ASSIGN  */
    LPAREN = 273,                  /* LPAREN  */
    RPAREN = 274,                  /* RPAREN  */
    PRINT = 275,                   /* PRINT  */
    MOD = 276,                     /* MOD  */
    IN = 277,                      /* IN  */
    IF = 278,                      /* IF  */
    ELSE = 279,                    /* ELSE  */
    WHILE = 280,                   /* WHILE  */
    FOR = 281,                     /* FOR  */
    COLON = 282,                   /* COLON  */
    MT = 283,                      /* MT  */
    LT = 284,                      /* LT  */
    EQ = 285,                      /* EQ  */
    DIFF = 286,                    /* DIFF  */
    NOT = 287,                     /* NOT  */
    IMPORT = 288,                  /* IMPORT  */
    FROM = 289,                    /* FROM  */
    AS = 290,                      /* AS  */
    INPUT = 291,                   /* INPUT  */
    INT = 292,                     /* INT  */
    DOUBLE = 293,                  /* DOUBLE  */
    FLOAT = 294,                   /* FLOAT  */
    COMPLEX = 295,                 /* COMPLEX  */
    INDENT = 296,                  /* INDENT  */
    DEDENT = 297,                  /* DEDENT  */
    NEWLINE = 298                  /* NEWLINE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "parser/parser.y"

    int intValue;
    double floatValue;
    char *id;
    struct ast_node *node;

#line 114 "parser/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_PARSER_TAB_H_INCLUDED  */
