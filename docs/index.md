---
layout: default
title: Início
---

# Compilador Python -> Java

Este repositório documenta o desenvolvimento de um compilador para um subconjunto de Python com saída planejada em Java. O projeto usa **Flex** para análise léxica e **Bison** para análise sintática, seguindo uma evolução incremental ao longo do semestre.

## Início Rápido

```bash
# Compilar o compilador
make all

# Executar o compilador
./compilador < input.py

# Limpar arquivos gerados
make clean
```

## Visão Geral

O objetivo do projeto é construir um compilador para um subconjunto de Python, começando pela leitura de tokens e validação sintática e evoluindo depois para análise semântica, representação intermediária e geração de código em Java.

O foco atual está na base do compilador:

- reconhecer a entrada com Flex;
- validar a estrutura sintática com Bison;
- manter a documentação coerente com o estado real do protótipo;
- preparar a transição para as próximas fases do semestre.

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
- `if (...) : stmt`
- `while (...) : stmt`
- `import id`
- `import id as id`
- `from id import id`
- `from id import id as id`
- expressões com `+`, `-`, `*`, `/`
- comparações com `==`, `!=`, `>` e `<`

### O lexer já reconhece, mas o parser ainda não usa em regras completas

- `for`
- `input`
- `int`, `double`, `float`, `complex`
- `++`
- `*=`, `/=`, `//=`
- `//`

Esses tokens existem no scanner, mas ainda não fazem parte de uma gramática final.

## Estrutura do Projeto

```
COMP1-Equipe-1/
├── lexer/          # Analisador léxico (Flex)
│   └── lexer.l     # Definições de tokens
├── parser/         # Analisador sintático (Bison)
│   └── parser.y    # Regras gramaticais
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
- Não há blocos indentados no estilo Python.
- `if` e `while` aceitam apenas um `stmt` como corpo.
- O projeto ainda está na etapa de base sintática, antes da geração de código Java.

## Exemplo compatível com a gramática atual

```python
x = 10 + 2
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
O parser (`parser.y`) valida a sintaxe de programas separados por linha:
- Avaliação de expressões com precedência de operadores
- Parsing de comandos (atribuições, condicionais, loops)
- Tratamento de importações

### 3. Evolução Planejada
Depois da base léxica e sintática, o projeto deve evoluir para:

- análise semântica;
- AST mais estruturada;
- geração de código intermediário;
- tradução final para Java.

### 4. Processo de Build
```
1. bison -d parser/parser.y -o parser/parser.tab.c
2. flex -o lexer/lex.yy.c lexer/lexer.l
3. gcc parser/parser.tab.c lexer/lex.yy.c -o compilador -lfl
```

## Contribuindo

1. Faça um fork do repositório
2. Crie uma branch de feature
3. Faça suas alterações
4. Envie um pull request

## Licença

Este projeto é parte de um curso universitário de compiladores (COMP1).
