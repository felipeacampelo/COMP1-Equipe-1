%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%union{
    int intValue;
    double floatValue;
    char *id;
}

%token <intValue> INT_NUM
%token <floatValue> FLOAT_NUM
%token <id> ID
%token PLUS PLUS_ATRIBUTION MINUS MINUS_ATRIBUTION TIMES TIMES_ATRIBUTION DIV DIV_ATRIBUTION INT_DIV INT_DIV_ATRIBUTION INCREMENT
%token ASSIGN
%token LPAREN RPAREN
%token PRINT
%token IF ELSE WHILE FOR COLON
%token MT LT EQ DIFF NOT
%token IMPORT FROM AS
%token INPUT 
%token INT DOUBLE FLOAT COMPLEX

%left MT LT EQ
%left PLUS MINUS
%left TIMES DIV

%type <floatValue> expr term factor

%%

program:
    program stmt  
    | stmt
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
    | expr '\n'
;

expr:
    expr PLUS term { $$ = $1 + $3; }
    | expr MINUS term { $$ = $1 - $3; }
    | expr MT expr { $$ = $1 > $3; }
    | expr LT expr { $$ = $1 < $3; } 
    | expr EQ expr { $$ = $1 == $3; }
    | term { $$ = $1; }
;

term:
    term TIMES factor { $$ = $1 * $3; }
    | term DIV factor { $$ = $1 / $3; }
    | factor { $$ = $1; }
;

factor:
    FLOAT_NUM { $$ = $1; }
    | INT_NUM { $$ = (double)$1; }
    | ID { $$ = 0; }
    | LPAREN expr RPAREN { $$ = $2; }
;

%%

void yyerror(const char *s){
    printf("Erro sintatico\n");
}