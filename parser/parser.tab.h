/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     FLOAT_NUM = 259,
     ID = 260,
     PLUS = 261,
     PLUS_ATRIBUTION = 262,
     MINUS = 263,
     MINUS_ATRIBUTION = 264,
     TIMES = 265,
     TIMES_ATRIBUTION = 266,
     DIV = 267,
     DIV_ATRIBUTION = 268,
     INT_DIV = 269,
     INT_DIV_ATRIBUTION = 270,
     INCREMENT = 271,
     ASSIGN = 272,
     LPAREN = 273,
     RPAREN = 274,
     PRINT = 275,
     MOD = 276,
     IN = 277,
     IF = 278,
     ELSE = 279,
     WHILE = 280,
     FOR = 281,
     COLON = 282,
     MT = 283,
     LT = 284,
     EQ = 285,
     DIFF = 286,
     NOT = 287,
     IMPORT = 288,
     FROM = 289,
     AS = 290,
     INPUT = 291,
     INT = 292,
     DOUBLE = 293,
     FLOAT = 294,
     COMPLEX = 295,
     INDENT = 296,
     DEDENT = 297,
     NEWLINE = 298
   };
#endif
/* Tokens.  */
#define NUM 258
#define FLOAT_NUM 259
#define ID 260
#define PLUS 261
#define PLUS_ATRIBUTION 262
#define MINUS 263
#define MINUS_ATRIBUTION 264
#define TIMES 265
#define TIMES_ATRIBUTION 266
#define DIV 267
#define DIV_ATRIBUTION 268
#define INT_DIV 269
#define INT_DIV_ATRIBUTION 270
#define INCREMENT 271
#define ASSIGN 272
#define LPAREN 273
#define RPAREN 274
#define PRINT 275
#define MOD 276
#define IN 277
#define IF 278
#define ELSE 279
#define WHILE 280
#define FOR 281
#define COLON 282
#define MT 283
#define LT 284
#define EQ 285
#define DIFF 286
#define NOT 287
#define IMPORT 288
#define FROM 289
#define AS 290
#define INPUT 291
#define INT 292
#define DOUBLE 293
#define FLOAT 294
#define COMPLEX 295
#define INDENT 296
#define DEDENT 297
#define NEWLINE 298




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 80 "parser/parser.y"
{
    int intValue;
    double floatValue;
    char *id;
    struct no_ast *node;
    ExprInfo exprInfo;
}
/* Line 1529 of yacc.c.  */
#line 143 "parser/parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

