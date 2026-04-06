%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%union{
    int intValue;
    char *id;
}

%token <intValue> NUM
%token <id> ID
%token PLUS MINUS TIMES DIV
%token ASSIGN
%token LPAREN RPAREN
%token PRINT
%left PLUS MINUS
%left TIMES DIV