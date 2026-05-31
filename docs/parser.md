---
layout: default
title: Documentação do Parser
---

# Analisador Sintático (Parser)

O parser é implementado usando **Bison** (GNU Parser Generator). Ele valida a sintaxe dos fluxos de tokens de acordo com as regras gramaticais.
Além da validação sintática, ele constrói uma AST para representar a estrutura do programa.

## Localização do Arquivo

```
parser/parser.y
```

## Estrutura

### Seção de Cabeçalho
```c
%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}
```

### Declaração Union
```c
%union{
    int intValue;
    double floatValue;
    char *id;
    struct ast_node *node;
}
```

Define os tipos para valores semânticos passados entre lexer e parser.

### Declarações de Tokens
```c
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
```

### Precedência de Operadores
```c
%left MT LT EQ
%left PLUS MINUS
%left TIMES DIV
```

Operadores de menor precedência são listados primeiro. Isso resolve ambiguidades em expressões.

### Declarações de Tipo
```c
%type <node> expr term factor stmt stmt_list program
```

Especifica que esses não-terminais retornam nós da AST.

## Regras Gramaticais

### Programa
```yacc
program:
    stmt_list
;
```

Um programa é tratado como uma lista de comandos e blocos.

### Lista de comandos
```yacc
stmt_list:
      stmt
    | stmt_list stmt
    | stmt_list NEWLINE
    | NEWLINE
;
```

### Comandos
```yacc
stmt:
    ID ASSIGN expr { $$ = create_op_node(NODE_ASSIGN, create_id_node($1), $3); }
    | PRINT LPAREN expr RPAREN { $$ = create_print_node($3); }
    | IF LPAREN expr RPAREN COLON INDENT stmt_list DEDENT { $$ = create_if_node($3, $7); }
    | WHILE LPAREN expr RPAREN COLON INDENT stmt_list DEDENT { $$ = create_while_node($3, $7); }
    | expr { $$ = $1; }
    | IMPORT ID { }
    | FROM ID IMPORT ID { }
    | FROM ID IMPORT ID AS ID { }
    | IMPORT ID AS ID { }
;
```

Esse conjunto cobre a forma atual do projeto: programas compostos por uma sequência de linhas, com uma instrução por linha.

### Expressões
```yacc
expr:
    term
    | expr PLUS term { $$ = create_op_node(NODE_OP, $1, $3); }
    | expr MINUS term { $$ = create_op_node(NODE_OP, $1, $3); }
    | expr MT term { $$ = create_op_node(NODE_OP, $1, $3); }
;
```

Ações semânticas já constroem nós da AST durante o parsing.

### Termos
```yacc
term:
    term TIMES factor { $$ = create_op_node(NODE_OP, $1, $3); }
    | term DIV factor { $$ = create_op_node(NODE_OP, $1, $3); }
    | factor { $$ = $1; }
;
```

### Fatores
```yacc
factor:
    NUM { $$ = create_int_node($1); }
    | FLOAT_NUM { $$ = create_int_node((int)$1); }
    | ID { $$ = create_id_node($1); }
    | LPAREN expr RPAREN { $$ = $2; }
;
```

## AST

O parser trabalha junto com `parser/ast.h` e `parser/ast.c` para montar a árvore sintática abstrata.

Os principais tipos de nó usados hoje são:

- número
- identificador
- operação
- atribuição
- `print`
- `if`
- `while`
- bloco

## Tratamento de Erros

```c
void yyerror(const char *s){
    printf("Erro sintatico\n");
}
```

Atualmente fornece relatório de erro mínimo.

## Compilando o Parser

```bash
bison -d parser/parser.y -o parser/parser.tab.c
```

Isso gera:
- `parser.tab.c` - A implementação do parser
- `parser.tab.h` - Definições de tokens para o lexer
