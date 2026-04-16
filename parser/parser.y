%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int yylex();
void yyerror(const char *s);
%}

%union{
    int intValue;
    double floatValue;
    char *id;
    struct ast_node *node;
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

%type <node> expr term factor stmt program

%%

program:
    program stmt '\n' { print_tree($2, 0); printf("\n"); }
    | stmt '\n'       { print_tree($1, 0); printf("\n"); }
    | program error '\n' { 
        printf("[ERRO] Sintaxe invalida! Ignorando esta linha e continuando o programa...\n"); 
        yyerrok; 
        yyclearin; 
    }
    | error '\n' { 
        printf("[ERRO] Sintaxe invalida! Ignorando esta linha e continuando o programa...\n"); 
        yyerrok; 
        yyclearin; 
    }
;

stmt:
    stmt:
    ID ASSIGN expr { $$ = create_op_node(NODE_ASSIGN, create_id_node($1), $3); }
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
    expr PLUS term  { $$ = create_op_node(NODE_OP, $1, $3); }
    | expr MINUS term { $$ = create_op_node(NODE_OP, $1, $3); }
    | term          { $$ = $1; }
;

term:
    term TIMES factor { $$ = create_op_node(NODE_OP, $1, $3); }
    | term DIV factor { $$ = create_op_node(NODE_OP, $1, $3); }
    | factor          { $$ = $1; }
;

factor:
    NUM { $$ = create_int_node($1); }
    | ID  { $$ = create_id_node($1); }
    | LPAREN expr RPAREN { $$ = $2; }
;

%%

void yyerror(const char *s){
    printf("Erro sintatico\n");
}