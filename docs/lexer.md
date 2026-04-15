---
layout: default
title: Documentação do Lexer
---

# Analisador Léxico (Lexer)

O lexer é implementado usando **Flex** (Fast Lexical Analyzer Generator). Ele lê o código fonte e converte em um fluxo de tokens.

## Localização do Arquivo

```
lexer/lexer.l
```

## Definições de Tokens

### Palavras-chave
```flex
"print"     { printf("PRINT(%s)\n", yytext); return PRINT; }
"if"        { printf("IF(%s)\n", yytext); return IF; }
"else"      { printf("ELSE(%s)\n", yytext); return ELSE; }
"while"     { printf("WHILE(%s)\n", yytext); return WHILE; }
"for"       { printf("FOR(%s)\n", yytext); return FOR; }
"import"    { printf("IMPORT(%s)\n", yytext); return IMPORT; }
"as"        { printf("AS(%s)\n", yytext); return AS; }
"from"      { printf("FROM(%s)\n", yytext); return FROM; }
"input"     { printf("INPUT(%s)\n", yytext); return INPUT; }
"int"       { printf("INT(%s)\n", yytext); return INT; }
"double"    { printf("DOUBLE(%s)\n", yytext); return DOUBLE; }
"float"     { printf("FLOAT(%s)\n", yytext); return FLOAT; }
"complex"   { printf("COMPLEX(%s)\n", yytext); return COMPLEX; }
```

### Operadores de Comparação
```flex
"=="        { printf("EQ(%s)\n", yytext); return EQ; }
"!="        { printf("DIFF(%s)\n", yytext); return DIFF; }
">"         { printf("MT(%s)\n", yytext); return MT; }
"<"         { printf("LT(%s)\n", yytext); return LT; }
"!"         { printf("NOT(%s)\n", yytext); return NOT; }
```

### Comentários

**Comentários de linha única:**
```flex
"#".*      { /* Ignorar comentário de linha */ }
```

**Comentários de bloco:**
```flex
"/*"([^*]|\*+[^*/])*\*+\/    { /* Ignorar comentários de bloco */ }
```

### Identificadores
```flex
[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.id = strdup(yytext); 
    printf("ID(%s)\n", yytext);
    return ID; 
}
```

Corresponde a nomes de variáveis e funções começando com letra ou underscore.

### Números
```flex
[0-9]+(\.[0-9]+)? { 
    yylval.intValue = atoi(yytext); 
    printf("NUM(%s)\n", yytext);
    return NUM; 
}
```

Corresponde a números inteiros e de ponto flutuante.

### Operadores Aritméticos
```flex
"="         { printf("ASSING(%s)\n", yytext); return ASSIGN; }
"+"         { printf("PLUS(%s)\n", yytext); return PLUS; }
"++"        { printf("INCREMENT(%s)\n", yytext); return INCREMENT; }
"-"         { printf("MINUS(%s)\n", yytext); return MINUS; }
"*"         { printf("TIMES(%s)\n", yytext); return TIMES; }
"*="        { printf("TIMES_ATRIBUTION(%s)\n", yytext); return TIMES_ATRIBUTION; }
"/"         { printf("DIV(%s)\n", yytext); return DIV; }
"/="        { printf("DIV_ATRIBUTION(%s)\n", yytext); return DIV_ATRIBUTION; }
"//"        { printf("INT_DIV(%s)\n", yytext); return INT_DIV; }
"//="       { printf("INT_DIV_ATRIBUTION(%s)\n", yytext); return INT_DIV_ATRIBUTION; }
```

### Delimitadores
```flex
"("         { printf("LPAREN(%s)\n", yytext); return LPAREN; }
")"         { printf("RPAREN(%s)\n", yytext); return RPAREN; }
":"         { printf("COLON(%s)\n", yytext); return COLON; }
"\n"        { printf("NLINE\n"); return '\n'; }
```

### Espaços em Branco
```flex
[ \t]+      { /* Ignorar espaços e tabs */ }
```

## Modo de Debug

O lexer inclui saída de debug que imprime cada token conforme é reconhecido:
```
PRINT(print)
LPAREN(()
ID(n)
RPAREN())
NLINE
```

Isso ajuda no desenvolvimento e na depuração de problemas de reconhecimento de tokens.

## Integração com o Parser

O lexer inclui as definições de tokens do parser:
```c
#include "../parser/parser.tab.h"
```

A função main simplesmente chama o parser:
```c
int main(void) {
    return yyparse();
}
```

## Compilando o Lexer

```bash
flex -o lexer/lex.yy.c lexer/lexer.l
```

Isso gera `lex.yy.c` que é então compilado com o parser.
