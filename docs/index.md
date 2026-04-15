---
layout: default
title: Início
---

# Compilador COMP1

Um compilador para linguagem de programação estilo Python construído com **Flex** (analisador léxico) e **Bison** (gerador de parser).

## Início Rápido

```bash
# Compilar o compilador
make all

# Executar o compilador
./compilador < input.py

# Limpar arquivos gerados
make clean
```

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

## Funcionalidades Suportadas

### Palavras-chave
| Palavra-chave | Descrição |
|---------|-------------|
| `print` | Comando de saída |
| `if` / `else` | Comandos condicionais |
| `while` | Comando de loop |
| `for` | Loop for |
| `import` / `from` / `as` | Importação de módulos |
| `input` | Entrada do usuário |
| `int`, `double`, `float`, `complex` | Declarações de tipo |

### Operadores
- **Aritméticos**: `+`, `-`, `*`, `/`, `//` (divisão inteira)
- **Atribuição**: `=`, `*=`, `/=`, `//=`
- **Comparação**: `==`, `!=`, `>`, `<`
- **Incremento**: `++`
- **Lógico**: `!` (não)

## Programas de Exemplo

### Conjetura de Collatz

```python
n = int(input())

while(n != 1):
    if n & 1:
        n = 3*n + 1
        print(n)
    else:
        n //= 2
        print(n)
```

Veja mais exemplos no diretório [src/](https://github.com/felipecampelo/COMP1-Equipe-1/tree/main/src).

## Arquitetura

### 1. Análise Léxica
O lexer (`lexer.l`) tokeniza o código fonte em tokens:
- Identificadores e palavras-chave
- Números (inteiros e floats)
- Operadores e símbolos
- Comentários (linha única `#` e bloco `/* */`)

### 2. Parsing
O parser (`parser.y`) valida a sintaxe e constrói a árvore de parsing:
- Avaliação de expressões com precedência de operadores
- Parsing de comandos (atribuições, condicionais, loops)
- Tratamento de importações

### 3. Processo de Build
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
