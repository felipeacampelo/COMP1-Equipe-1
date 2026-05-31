---
layout: default
title: Referência da Gramática
---

# Referência da Gramática

Esta página documenta a gramática que o parser atual aceita.

## Estrutura do Programa

```
program := stmt_list

stmt_list := stmt
          | stmt_list stmt
          | stmt_list NEWLINE
          | NEWLINE

stmt := ID ASSIGN expr
      | PRINT LPAREN expr RPAREN
      | IF LPAREN expr RPAREN COLON INDENT stmt_list DEDENT
      | WHILE LPAREN expr RPAREN COLON INDENT stmt_list DEDENT
      | FOR ID IN expr COLON INDENT stmt_list DEDENT
      | expr
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
      | expr MT term        (greater than)
      | expr LT term        (less than)
      | expr EQ expr        (equal)
```

## Termos e Fatores

```
term := term TIMES factor
      | term DIV factor
      | factor

factor := NUM
        | FLOAT_NUM
        | ID
        | LPAREN expr RPAREN
```

## Precedência de Operadores

Os operadores são avaliados na seguinte precedência (maior para menor):

1. `(` `)` - Parênteses
2. `*` `/` - Multiplicação, Divisão
3. `+` `-` - Adição, Subtração
4. `>` `<` `==` - Operadores de comparação

## Observações importantes

- O parser trabalha com comandos separados por nova linha.
- `if`, `while` e `for` usam `INDENT` e `DEDENT` para delimitar blocos.
- O parser aceita números inteiros e decimais.
- `INPUT`, `INT`, `DOUBLE`, `FLOAT`, `COMPLEX`, `INT_DIV`, `INT_DIV_ATRIBUTION`, `TIMES_ATRIBUTION`, `DIV_ATRIBUTION`, `INCREMENT`, `DIFF` e `NOT` existem como tokens no lexer, mas ainda não aparecem em regras sintáticas completas.
- Ainda não existe tabela de símbolos.
- Ainda não existe fase semântica.

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
| `IN` | Palavra-chave do laço `for` |

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
| `INDENT` | recuo | Início de bloco |
| `DEDENT` | redução de recuo | Fim de bloco |
| `NEWLINE` | nova linha lógica | Separação de comandos |

## Comentários

```python
# Comentário de linha única

/*
   Comentário de bloco
   abrangendo várias linhas
*/
```
