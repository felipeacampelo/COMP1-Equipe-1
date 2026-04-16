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
%token INDENT DEDENT NEWLINE

%left MT LT EQ
%left PLUS MINUS
%left TIMES DIV

%type <node> expr term factor stmt stmt_list program

%%

program:
    stmt_list { 
        if ($1) { 
            print_tree($1, 0); 
            printf("\n"); 
        } 
    }
;

stmt_list:
      stmt               { $$ = $1; }
    | stmt_list stmt     { $$ = create_block_node($1, $2); }
    | stmt_list NEWLINE  { $$ = $1; } /* Aceita quebras de linha normais */
    | NEWLINE            { $$ = NULL; }
;

stmt:
    ID ASSIGN expr { $$ = create_op_node(NODE_ASSIGN, create_id_node($1), $3); }
    | PRINT LPAREN expr RPAREN { $$ = create_print_node($3); }
    | IF LPAREN expr RPAREN COLON INDENT stmt_list DEDENT { $$ = create_if_node($3, $7); }
    // | IF LPAREN expr RPAREN COLON stmt ELSE stmt COLON { }
    | WHILE LPAREN expr RPAREN COLON INDENT stmt_list DEDENT { $$ = create_while_node($3, $7); }
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