---
layout: default
title: Referência da Gramática
---

# Referência da Gramática

Esta página documenta a gramática formal suportada pelo compilador COMP1.

## Estrutura do Programa

```
program := program stmt '\n'
         | stmt '\n'
```

## Comandos

```
stmt := ID ASSIGN term
      | PRINT LPAREN expr RPAREN
      | IF LPAREN expr RPAREN COLON stmt
      | IF LPAREN expr RPAREN COLON stmt ELSE stmt COLON
      | WHILE LPAREN expr RPAREN COLON stmt
      | expr
      | WHILE LPAREN expr RPAREN COLON
      | WHILE LPAREN term RPAREN COLON
      | IF LPAREN expr RPAREN COLON
      | IF LPAREN term RPAREN COLON
      | IMPORT ID
      | FROM ID IMPORT ID
      | FROM ID IMPORT ID AS ID
      | IMPORT ID AS ID
```

## Expressões

```
expr := expr PLUS term
      | expr MINUS term
      | term
      | expr MT expr        (greater than)
      | expr LT expr        (less than)
      | expr EQ expr        (equal)
      | expr PLUS expr
      | expr MINUS expr
```

## Termos e Fatores

```
term := term TIMES factor
      | term DIV factor
      | factor

factor := NUM
        | ID
        | LPAREN expr RPAREN
```

## Precedência de Operadores

Os operadores são avaliados na seguinte precedência (maior para menor):

1. `(` `)` - Parênteses
2. `*` `/` - Multiplicação, Divisão
3. `+` `-` - Adição, Subtração
4. `>` `<` `==` - Operadores de comparação

## Referência de Tokens

### Palavras-chave
| Token | Descrição |
|-------|-------------|
| `PRINT` | Comando print |
| `IF` | Condicional if |
| `ELSE` | Clausula else |
| `WHILE` | Loop while |
| `FOR` | Loop for |
| `IMPORT` | Importar módulo |
| `FROM` | Importar do módulo |
| `AS` | Alias de importação |
| `INPUT` | Função input |
| `INT` | Tipo inteiro |
| `DOUBLE` | Tipo double |
| `FLOAT` | Tipo float |
| `COMPLEX` | Tipo complex |

### Operadores
| Token | Símbolo | Descrição |
|-------|--------|-------------|
| `PLUS` | `+` | Adição |
| `MINUS` | `-` | Subtração |
| `TIMES` | `*` | Multiplicação |
| `DIV` | `/` | Divisão |
| `INT_DIV` | `//` | Divisão inteira |
| `ASSIGN` | `=` | Atribuição |
| `TIMES_ATRIBUTION` | `*=` | Multiplicar e atribuir |
| `DIV_ATRIBUTION` | `/=` | Dividir e atribuir |
| `INT_DIV_ATRIBUTION` | `//=` | Divisão inteira e atribuir |
| `INCREMENT` | `++` | Incremento |
| `MT` | `>` | Maior que |
| `LT` | `<` | Menor que |
| `EQ` | `==` | Igual |
| `DIFF` | `!=` | Diferente |
| `NOT` | `!` | Negação lógica |

### Símbolos
| Token | Símbolo | Descrição |
|-------|--------|-------------|
| `LPAREN` | `(` | Parêntese esquerdo |
| `RPAREN` | `)` | Parêntese direito |
| `COLON` | `:` | Separador de comandos |

## Comentários

```python
# Comentário de linha única

/*
   Comentário de bloco
   abrangendo várias linhas
*/
```
