---
layout: default
title: Documentação do Parser
---

# Analisador Sintático (Parser)

O parser é implementado usando **Bison** (GNU Parser Generator). Ele valida a sintaxe dos fluxos de tokens de acordo com as regras gramaticais.

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
    char *id;
}
```

Define os tipos para valores semânticos passados entre lexer e parser.

### Declarações de Tokens
```c
%token <intValue> NUM
%token <id> ID
%token PLUS MINUS TIMES DIV DIV_ATRIBUTION TIMES_ATRIBUTION INT_DIV INT_DIV_ATRIBUTION INCREMENT
%token ASSIGN
%token LPAREN RPAREN
%token PRINT
%token IF ELSE WHILE FOR COLON
%token MT LT EQ DIFF NOT
%token IMPORT FROM AS
%token INPUT 
%token INT DOUBLE FLOAT COMPLEX
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
%type <intValue> expr term factor
```

Especifica que esses não-terminais retornam valores inteiros.

## Regras Gramaticais

### Programa
```yacc
program:
    program stmt '\n'
    | stmt '\n'
;
```

Um programa é uma sequência de comandos separados por novas linhas.

### Comandos
```yacc
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
```

### Expressões
```yacc
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
```

Ações semânticas realizam computação real durante o parsing.

### Termos
```yacc
term:
    term TIMES factor { $$ = $1 * $3; }
    | term DIV factor { $$ = $1 / $3; }
    | factor { $$ = $1; }
;
```

### Fatores
```yacc
factor:
    NUM { }
    | ID { }
    | LPAREN expr RPAREN { }
;
```

## Tratamento de Erros

```c
void yyerror(const char *s){
    printf("Erro sintatico\n");
}
```

Atualmente fornece relatório de erro mínimo. Mensagens de erro aprimoradas com números de linha seriam uma boa melhoria.

## Compilando o Parser

```bash
bison -d parser/parser.y -o parser/parser.tab.c
```

Isso gera:
- `parser.tab.c` - A implementação do parser
- `parser.tab.h` - Definições de tokens para o lexer

## Melhorias Futuras

1. **Ações Semânticas** - Preencher ações vazias `{}` com geração de código
2. **Recuperação de Erros** - Melhor tratamento de erros e sincronização
3. **Tabela de Símbolos** - Rastrear declarações e tipos de variáveis
4. **Verificação de Tipos** - Validar tipos de operandos em expressões
5. **Geração de Código** - Gerar código alvo (assembly, bytecode, etc.)
