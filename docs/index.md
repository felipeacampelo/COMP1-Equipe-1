---
layout: default
title: Início
---
## Visão Geral

O objetivo do projeto é construir um compilador para um subconjunto de Python, cobrindo análise léxica, análise sintática, construção de árvore sintática abstrata e tradução inicial para Java.

O foco atual do projeto está em:

- reconhecer a entrada com Flex;
- validar a estrutura sintática com Bison;
- construir uma AST a partir do código de entrada;
- preparar a evolução para análise semântica e tradução mais completa.

## Integrantes do Grupo

| Nome | Matrícula |
|---|---|
| Marcus Vinicius Cunha Dantas | 211031403 |
| Isaac Menezes Pereira | 190088885 |
| Felipe de Aquino Campelo | 231011328 |
| Pablo Rodrigues Lima | 231029841 |
| Samuel Alves Silva | 202063462 |

## Estado Atual

### O parser aceita hoje

- atribuição com `=`
- `print(...)`
- `if (...) : bloco`
- `while (...) : bloco`
- `for ... in ... : bloco`
- `import id`
- `import id as id`
- `from id import id`
- `from id import id as id`
- expressões com `+`, `-`, `*`, `/`
- comparações com `==`, `>`, `<`
- blocos por indentação
- números inteiros e decimais

### O lexer já reconhece, mas o parser ainda não usa em regras completas

- `input`
- `int`, `double`, `float`, `complex`
- `++`
- `+=`, `-=`, `*=`, `/=`, `//=`
- `//`
- `!=`
- `!`

Esses tokens existem no scanner, mas ainda não fazem parte de uma gramática final.

### O que ainda não existe

- análise semântica
- verificação de tipos
- suporte completo a strings
- tradução Java completa para todos os nós da árvore

## Estrutura do Projeto

```
COMP1-Equipe-1/
├── lexer/          # Analisador léxico (Flex)
│   └── lexer.l     # Definições de tokens
├── parser/         # Analisador sintático (Bison)
│   ├── parser.y    # Regras gramaticais
│   ├── ast.h       # Estruturas da AST
│   └── ast.c       # Construção e visualização da AST
├── src/            # Programas Python de exemplo
│   ├── collatz.py
│   ├── ellipticCurveExemple.py
│   ├── paraboloideExemple.py
│   └── pdfLibExemple.py
├── Makefile        # Automação de build
└── docs/           # Documentação
```

## Como a documentação está organizada

- [Visão geral](./index.md): objetivo, estado atual e estrutura do projeto.
- [Sprints](./sprints.md): planejamento e registro da evolução do projeto.
- [Gramática](./grammar.md): referência do subconjunto aceito pelo parser.
- [Lexer](./lexer.md): tokens reconhecidos pelo analisador léxico.
- [Parser](./parser.md): regras sintáticas e observações sobre o comportamento atual.
- [Exemplos](./examples.md): entradas válidas, limitações e casos em preparação.

## Regras de uso atuais

- Cada comando precisa terminar com quebra de linha.
- Blocos são delimitados por indentação lógica.
- `if`, `while` e `for` aceitam blocos com múltiplos comandos.
- O projeto já constrói AST como etapa intermediária do compilador.

## Exemplo compatível com a gramática atual

```python
x = 10 + 2
if (x > 5):
    print(x)
```

## Arquitetura

### 1. Análise Léxica
O lexer (`lexer.l`) tokeniza o código fonte em tokens:
- Identificadores e palavras-chave
- Números (inteiros e floats)
- Operadores e símbolos
- Comentários (linha única `#` e bloco `/* */`)

### 2. Parsing
O parser (`parser.y`) valida a sintaxe e constrói a árvore sintática:
- Avaliação de expressões com precedência de operadores
- Parsing de comandos (atribuições, condicionais e loops)
- Organização de blocos por indentação
- Tratamento de importações

### 3. AST
A AST representa a estrutura do programa e organiza:

- números;
- identificadores;
- operações;
- atribuições;
- `print`;
- `if`;
- `while`;
- blocos.

### 4. Evolução Planejada
Depois da base léxica, sintática e estrutural, o projeto deve evoluir para:

- análise semântica;
- tabela de símbolos;
- verificação de tipos;
- geração de código intermediário;
- tradução final para Java.

### 5. Processo de Build
```
1. bison -d parser/parser.y -o parser/parser.tab.c
2. flex -o lexer/lex.yy.c lexer/lexer.l
3. gcc parser/parser.tab.c lexer/lex.yy.c -o compiladorpj -lfl
```

## Início Rápido

```bash
# Compilar o compilador
make all

# Executar o compilador
./compiladorpj src/collatz.py

# Limpar arquivos gerados
make clean
```
