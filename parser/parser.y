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
%token IF
%token ELSE
%token WHILE
%token MT LT EQ
%token COLON
%token IMPORT
%token FROM
%token AS

%left MT LT EQ
%left PLUS MINUS
%left TIMES DIV

%type <intValue> expr term factor

%%

program:
    program stmt '\n'
    | stmt '\n'
;

stmt:
    ID ASSIGN term { }
    | PRINT LPAREN expr RPAREN { }
    | IF LPAREN expr RPAREN COLON stmt { }
    | IF LPAREN expr RPAREN COLON stmt ELSE stmt COLON { }
    | WHILE LPAREN expr RPAREN COLON stmt { }
    | expr { }
    | WHILE LPAREN expr RPAREN COLON { }
    | WHILE LPAREN term RPAREN COLON { }
    | IF LPAREN expr RPAREN COLON { }
    | IF LPAREN term RPAREN COLON { }
    | IMPORT ID { }
    | FROM ID IMPORT ID { }
    | FROM ID IMPORT ID AS ID { }
    | IMPORT ID AS ID { }
;

expr:
    expr PLUS term { $$ = $1 + $3; }
    | expr MINUS term { $$ = $1 - $3; }
    | term { $$ = $1; }
    | expr MT expr { $$ = $1 > $3; }
    | expr LT expr { $$ = $1 < $3; } 
    | expr EQ expr { $$ = $1 == $3; }
    | expr PLUS expr { $$ = $1 + $3; }
    | expr MINUS expr { $$ = $1 - $3; }
;

term:
    term TIMES factor { $$ = $1 * $3; }
    | term DIV factor { $$ = $1 / $3; }
    | factor { $$ = $1; }
;

factor:
    NUM { }
    | ID { }
    | LPAREN expr RPAREN { }
;

%%

void yyerror(const char *s){
    printf("Erro sintatico\n");
}