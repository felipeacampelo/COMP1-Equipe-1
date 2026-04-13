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
    | IF LPAREN expr RPAREN stmt { }
    | IF LPAREN expr RPAREN stmt ELSE stmt { }
    | WHILE LPAREN expr RPAREN stmt { }
    | expr { }
    | WHILE LPAREN expr RPAREN { }
    | WHILE LPAREN term RPAREN { }
    | IF LPAREN expr RPAREN { }
    | IF LPAREN term RPAREN { }
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