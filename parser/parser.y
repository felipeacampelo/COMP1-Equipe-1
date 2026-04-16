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

%token <intValue> NUM
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
      /* vazio */ { $$ = NULL; }
    | program stmt '\n' { if ($2) { print_tree($2, 0); printf("\n"); } }
    | program stmt      { if ($2) { print_tree($2, 0); printf("\n"); } }
    | program '\n'      { /* ignora linhas vazias */ }
    | program error '\n' { 
        yyerrok; 
        yyclearin; 
        printf("[ERRO] Sintaxe invalida nesta linha\n"); 
    }
;

stmt:
    ID ASSIGN expr { $$ = create_op_node(NODE_ASSIGN, create_id_node($1), $3); }
    | PRINT LPAREN expr RPAREN { $$ = create_print_node($3); }
    | IF LPAREN expr RPAREN COLON stmt { $$ = create_if_node($3, $6); }
    // | IF LPAREN expr RPAREN COLON stmt ELSE stmt COLON { }
    | WHILE LPAREN expr RPAREN COLON stmt { $$ = create_while_node($3, $6);}
    | expr { $$ = $1; }
    // | WHILE LPAREN expr RPAREN COLON { }
    // | WHILE LPAREN term RPAREN COLON { }
    // | IF LPAREN expr RPAREN COLON { }
    // | IF LPAREN term RPAREN COLON { }
    | IMPORT ID { }
    | FROM ID IMPORT ID { }
    | FROM ID IMPORT ID AS ID { }
    | IMPORT ID AS ID { }
;

expr:
      term
    | expr PLUS term  { $$ = create_op_node(NODE_OP, $1, $3); }
    | expr MINUS term { $$ = create_op_node(NODE_OP, $1, $3); }
    | expr MT term    { $$ = create_op_node(NODE_OP, $1, $3); }
;

term:
    term TIMES factor { $$ = create_op_node(NODE_OP, $1, $3); }
    | term DIV factor { $$ = create_op_node(NODE_OP, $1, $3); }
    | factor          { $$ = $1; }
;

factor:
    NUM         { $$ = create_int_node($1); }
    | FLOAT_NUM { $$ = create_int_node((int)$1); } // Aceita o decimal na árvore
    | ID        { $$ = create_id_node($1); }
    | LPAREN expr RPAREN { $$ = $2; }
;

%%

void yyerror(const char *s){
    printf("Erro sintatico\n");
}