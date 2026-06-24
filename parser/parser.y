%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "ast.h"
#include "symtable.h"

int yylex();
void yyerror(const char *s);

static int semantic_errors = 0;

static ExprInfo make_expr_info(NoAST *node, SymbolType type) {
    ExprInfo info;
    info.node = node;
    info.type = type;
    return info;
}

static void semantic_error(const char *fmt, ...) {
    va_list args;
    semantic_errors++;
    printf("Erro semantico: ");
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
}

static int is_numeric_type(SymbolType type) {
    return type == TYPE_INT || type == TYPE_FLOAT;
}

static SymbolType arithmetic_result_type(SymbolType left, SymbolType right, const char *op) {
    if(left == TYPE_ERROR || right == TYPE_ERROR) return TYPE_ERROR;

    if(!is_numeric_type(left) || !is_numeric_type(right)) {
        semantic_error(
            "operacao '%s' invalida entre tipos %s e %s",
            op,
            symbol_type_name(left),
            symbol_type_name(right)
        );
        return TYPE_ERROR;
    }

    if(left == TYPE_FLOAT || right == TYPE_FLOAT) return TYPE_FLOAT;
    return TYPE_INT;
}

static SymbolType comparison_result_type(SymbolType left, SymbolType right, const char *op) {
    if(left == TYPE_ERROR || right == TYPE_ERROR) return TYPE_ERROR;

    if(!is_numeric_type(left) || !is_numeric_type(right)) {
        semantic_error(
            "comparacao '%s' invalida entre tipos %s e %s",
            op,
            symbol_type_name(left),
            symbol_type_name(right)
        );
        return TYPE_ERROR;
    }

    return TYPE_BOOL;
}

static void validate_condition(SymbolType type, const char *context) {
    if(type == TYPE_ERROR) return;

    if(type != TYPE_BOOL && !is_numeric_type(type)) {
        semantic_error(
            "condicao invalida em %s: esperado bool, int ou float, recebido %s",
            context,
            symbol_type_name(type)
        );
    }
}
%}

%union{
    int intValue;
    double floatValue;
    char *id;
    struct no_ast *node;
    ExprInfo exprInfo;
}

%token <intValue> NUM
%token <floatValue> FLOAT_NUM
%token <id> ID
%token PLUS PLUS_ATRIBUTION MINUS MINUS_ATRIBUTION TIMES TIMES_ATRIBUTION DIV DIV_ATRIBUTION INT_DIV INT_DIV_ATRIBUTION INCREMENT
%token ASSIGN
%token LPAREN RPAREN
%token PRINT
%token MOD
%token IN IF ELSE WHILE FOR COLON
%token MT LT EQ DIFF NOT
%token IMPORT FROM AS
%token INPUT 
%token INT DOUBLE FLOAT COMPLEX

%token INDENT DEDENT NEWLINE

%left MT LT EQ
%left PLUS MINUS
%left TIMES DIV

%type <exprInfo> expr term factor
%type <node> stmt stmt_list program

%%

program:
    stmt_list{ 
        if($1){ 
            print_tree($1, 0); 
            printf("\n");

            if(semantic_errors == 0) {
                compile_intermediate($1);
            } else {
                printf(
                    "\nCompilacao interrompida: %d erro(s) semantico(s) encontrado(s).\n",
                    semantic_errors
                );
            }
        } 
    }
;

stmt_list:
    stmt { $$ = $1; }
    | stmt_list stmt { $$ = create_block_node($1, $2); }
    | stmt_list NEWLINE { $$ = $1; } /* Aceita quebras de linha normais */
    | NEWLINE { $$ = NULL; }
    | error NEWLINE { 
        yyerrok; 
        yyclearin; 
        printf("[ERRO] Sintaxe invalida nesta linha. Pulando para a proxima...\n"); 
        $$ = NULL; 
    }
;


stmt:
    ID ASSIGN expr {
        insert_symbol($1, $3.type);
        $$ = create_op_node(NODE_ASSIGN, "=", create_id_node($1), $3.node);
    }
    | PRINT LPAREN expr RPAREN { $$ = create_print_node($3.node); }
    | IF LPAREN expr RPAREN COLON INDENT stmt_list DEDENT {
        validate_condition($3.type, "if");
        $$ = create_if_node($3.node, $7);
    }
    | IF LPAREN expr RPAREN COLON stmt ELSE COLON stmt {
        validate_condition($3.type, "if/else");
        $$ = create_if_else_node($3.node, $6, $9);
    }
    | IF LPAREN expr RPAREN COLON INDENT stmt_list DEDENT ELSE COLON INDENT stmt_list DEDENT {
        validate_condition($3.type, "if/else");
        $$ = create_if_else_node($3.node, $7, $12);
    }
    | WHILE LPAREN expr RPAREN COLON INDENT stmt_list DEDENT {
        validate_condition($3.type, "while");
        $$ = create_while_node($3.node, $7);
    }
    | expr { $$ = $1.node; }
    | FOR ID IN expr COLON INDENT stmt_list DEDENT {
        if($4.type == TYPE_FLOAT) {
            semantic_error("iteracao em for exige valor inteiro, recebido %s", symbol_type_name($4.type));
        } else if($4.type != TYPE_INT && $4.type != TYPE_ERROR) {
            semantic_error("iteracao em for invalida para tipo %s", symbol_type_name($4.type));
        }

        insert_symbol($2, TYPE_INT);
        $$ = create_for_node(create_id_node($2), $7, $4.node);
    }
    | WHILE LPAREN expr RPAREN COLON stmt {
        validate_condition($3.type, "while");
        $$ = create_while_node($3.node, $6);
    }
    | IF LPAREN expr RPAREN COLON stmt {
        validate_condition($3.type, "if");
        $$ = create_if_node($3.node, $6);
    }
    | IMPORT ID { $$ = NULL; }
    | FROM ID IMPORT ID { $$ = NULL; }
    | FROM ID IMPORT ID AS ID { $$ = NULL; }
    | IMPORT ID AS ID { $$ = NULL; }
;

expr:
      term { $$ = $1; }
    | expr PLUS term  {
        $$ = make_expr_info(
            create_op_node(NODE_OP, "+", $1.node, $3.node),
            arithmetic_result_type($1.type, $3.type, "+")
        );
    }
    | expr MINUS term {
        $$ = make_expr_info(
            create_op_node(NODE_OP, "-", $1.node, $3.node),
            arithmetic_result_type($1.type, $3.type, "-")
        );
    }
    | expr MT term    {
        $$ = make_expr_info(
            create_op_node(NODE_OP, ">", $1.node, $3.node),
            comparison_result_type($1.type, $3.type, ">")
        );
    }
    | expr LT term    {
        $$ = make_expr_info(
            create_op_node(NODE_OP, "<", $1.node, $3.node),
            comparison_result_type($1.type, $3.type, "<")
        );
    }
    | expr EQ term    {
        $$ = make_expr_info(
            create_op_node(NODE_OP, "==", $1.node, $3.node),
            comparison_result_type($1.type, $3.type, "==")
        );
    }
    | expr DIFF term  {
        $$ = make_expr_info(
            create_op_node(NODE_OP, "!=", $1.node, $3.node),
            comparison_result_type($1.type, $3.type, "!=")
        );
    }
;

term:
    term TIMES factor {
        $$ = make_expr_info(
            create_op_node(NODE_OP, "*", $1.node, $3.node),
            arithmetic_result_type($1.type, $3.type, "*")
        );
    }
    | term DIV factor {
        $$ = make_expr_info(
            create_op_node(NODE_OP, "/", $1.node, $3.node),
            arithmetic_result_type($1.type, $3.type, "/")
        );
    }
    | term MOD factor {
        $$ = make_expr_info(
            create_op_node(NODE_OP, "%", $1.node, $3.node),
            arithmetic_result_type($1.type, $3.type, "%")
        );
    }
    | factor { $$ = $1; }
;


factor:
    NUM { $$ = make_expr_info(create_int_node($1), TYPE_INT); }
    | FLOAT_NUM { $$ = make_expr_info(create_float_node($1), TYPE_FLOAT); }
    | ID { 
        Symbol *symbol = lookup_symbol($1);

        if(symbol == NULL) {
            semantic_error("a variavel '%s' nao foi declarada", $1);
            $$ = make_expr_info(create_id_node($1), TYPE_ERROR);
        } else {
            $$ = make_expr_info(create_id_node($1), symbol->type);
        }
    }
    | LPAREN expr RPAREN { $$ = $2; }
;

%%

void yyerror(const char *s) {
    printf("Erro sintatico\n");
}
