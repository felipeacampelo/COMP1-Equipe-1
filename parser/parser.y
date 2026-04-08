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
    program stmt
    | stmt
;

stmt:
    ID ASSIGN expr { printf("Atribuicao reconhecida\n"); }
    | PRINT LPAREN expr RPAREN { printf("Print reconhecido: %d\n", $3); }
    | IF LPAREN expr RPAREN stmt { printf("Comando IF reconhecido:"); }
    | IF LPAREN expr RPAREN stmt ELSE stmt { printf("Comando IF-ELSE reconhecido:"); }
    | WHILE LPAREN expr RPAREN stmt { printf("Comando WHILE reconhecido:"); }
;

expr:
     expr PLUS term { $$ = $1 + $3; }
    | expr MINUS term { $$ = $1 - $3; }
    | term { $$ = $1; }
    | expr MT expr { $$ = $1 > $3; }
    | expr LT expr { $$ = $1 < $3; } 
    | expr EQ expr { $$ = $1 == $3; }
;

term:
    term TIMES factor { $$ = $1 * $3; }
    | term DIV factor { $$ = $1 / $3; }
    | factor { $$ = $1; }
;

factor:
    NUM { $$ = $1; }
    | ID { $$ = 0; }
    | LPAREN expr RPAREN { $$ = $2; }
;

%%

void yyerror(const char *s){
    printf("Erro sintatico\n");
}