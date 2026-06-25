---
layout: default
title: Documentação da Tabela de Símbolos
---

# Tabela de Símbolos - symtable

Implementação de uma tabela de símbolos usando **tabela hash com encadeamento separado**. Fundamental para armazenar indentificadores do código durante a ánalise semântica.

## Localização do Arquivo

```
parser/symtable.c
parser/symtable.h
```

## Estrutura

### Tamanho da tabela
- **211 símbolos** Número primo para minimizar colisões
- Armazenado em um array global estático
```c
Symbol *symtable[211];
```

### Nó da tabela (symtable.h)
```c
typedef struct Symbol {
    char *name;
    struct Symbol *next;
} Symbol;
```

### Funções

#### Hash(char *name)
- Usa o metodo de Horner para calcular o hash
- Multiplica por 31 e soma o caractere ASCII
- Retorna o valor aplicando o modulo 211 para mapear
```c
unsigned int hash(char *name) {
    unsigned int h = 0;
    for(int i = 0; name[i] != '\0'; i++) h = (h * 31) + name[i];
    return h % 211;
}
```

#### lookup_symbol(char *name)
- Calcula o hash do nome e procura o indentificador a partir dele
- Compara as strings
- Retorna o símbolo encontrado ou NULL se não encontrou nada
```c
Symbol* lookup_symbol(char *name) {
    // Procura na lista ligada em apenas 2 linhas
    for(Symbol *s = symtable[hash(name)]; s != NULL; s = s->next)
        if(strcmp(s->name, name) == 0) return s;

        
    return NULL; 
}
```

#### insert_symbol(char *name)
- Verifica se o símbolo já não está no hash
- Se não existir, calcula o hash, aloca memoria e insere na tabela
```c
void insert_symbol(char *name) {
    if(lookup_symbol(name) != NULL) return; // Se já existe, sai
    
    unsigned int h = hash(name);
    Symbol *s = malloc(sizeof(Symbol));
    s->name = strdup(name);
    s->next = symtable[h];
    symtable[h] = s;

    printf("Tabela de Símbolos Variável: '%s' alocada no bucket [%d]\n", name, h);
}
```