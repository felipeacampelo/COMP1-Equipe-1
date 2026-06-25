---
layout: default
title: Documentação do gerador do codigo final
---

# Gerador de Código Java

## Visão Geral

Responsável por percorrer a Árvore Sintática Abstrata e gerar código final em Java.

# Estrutura de Controle de Variáveis

## Estrutura `JavaVar`

```c
typedef struct {
    char name[50];
    const char *type;
} JavaVar;
```

Armazena informações sobre variáveis já declaradas durante a geração do código.


## Tabela de Variáveis Declaradas

```c
static JavaVar declared[100];
static int n_decl = 0;
```

# Gerenciamento de Declarações

## find_declared()
- Procura uma variável na tabela de declarações.
```c
static int find_declared(char *name)
```

## was_declared()
- Verifica se uma variável já foi declarada.
```c
static int was_declared(char *name)
```




## declared_type()
- Obtém o tipo associado a uma variável previamente declarada.
- Caso a variável não exista, retorna `"int"` como tipo padrão.
```c
static const char* declared_type(char *name)
```


## mark_declared()
- Registra uma nova variável na tabela de declarações.
```c
static void mark_declared(char *name, const char *type)
```

# Controle de Indentação

## indent()
- Responsável pela formatação do código Java gerado.
- Cada nível corresponde a quatro espaços
```c
static void indent(FILE *out, int l)
```

# Operadores de Comparação

## is_comparison_op()
- Verifica se um operador produz um resultado booleano.
```c
static int is_comparison_op(const char *op)
```

# Inferência de Tipos

## infer_type()
- Determina automaticamente o tipo Java de uma expressão.
```c
static const char* infer_type(NoAST *node)
```

### Inferência para Identificadores

Quando encontra um identificador (`NODE_ID`), o tipo é recuperado da tabela de declarações.


# Verificação de Expressões Booleanas

## `is_boolean_expr()`
- Verifica se uma expressão possui tipo booleano.
```c
static int is_boolean_expr(NoAST *node)
```

# Conversão de Condições

## `generate_java_condition()`
- Garante que expressões usadas em estruturas condicionais sejam válidas em Java.
```c
static void generate_java_condition(NoAST *node, FILE *out)
```

# Geração de Código

## `generate_java()`
- Percorre recursivamente a AST e produz o código Java correspondente.
```c
static void generate_java(NoAST *node, FILE *out, int lvl)
```

# Nós Suportados

- Int
- Float
- Bool
- String
- Indentificadores
- Operações (a + b * c / d)
- Atribuições
- print()
- for()
- if()
- if else
- while()
- blocos de código


# Compilação Final

## compile_java()

```c
void compile_java(NoAST *root, const char *filename)
```

Função principal responsável pela geração do arquivo Java.

### Fluxo de Execução

#### 1. Criação do Arquivo
- Abre o arquivo de saída.
```c
FILE *out = fopen(filename, "w");
```

#### 2. Reinicialização da Tabela de Variáveis
- Remove informações de compilações anteriores.
```c
n_decl = 0;
```

#### 3. Geração da Estrutura Base

```java
public class Main {
    public static void main(String[] args) {

    }
}--
```

#### 4. Geração do Código
- Insere o código produzido pela AST dentro do método `main`.
```c
generate_java(root, out, 2);
```

#### 5. Finalização
- Fecha o arquivo gerado.
```c
fclose(out);
```

---

