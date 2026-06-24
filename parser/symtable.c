#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"

// O array global já nasce todo com NULL automaticamente em C!
Symbol *symtable[211]; 

unsigned int hash(char *name) {
    unsigned int h = 0;
    for(int i = 0; name[i] != '\0'; i++) h = (h * 31) + name[i];
    return h % 211;
}

Symbol* lookup_symbol(char *name) {
    // Procura na lista ligada em apenas 2 linhas
    for(Symbol *s = symtable[hash(name)]; s != NULL; s = s->next)
        if(strcmp(s->name, name) == 0) return s;
    return NULL; 
}

const char* symbol_type_name(SymbolType type) {
    switch(type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_BOOL: return "bool";
        case TYPE_ERROR: return "erro";
        default: return "desconhecido";
    }
}

Symbol* insert_symbol(char *name, SymbolType type) {
    Symbol *existing = lookup_symbol(name);

    if(existing != NULL) {
        if(type != TYPE_UNKNOWN && type != TYPE_ERROR) {
            existing->type = type;
        }

        return existing;
    }

    unsigned int h = hash(name);
    Symbol *s = malloc(sizeof(Symbol));
    s->name = strdup(name);
    s->type = type;
    s->next = symtable[h];
    symtable[h] = s;

    printf(
        "Tabela de Símbolos Variável: '%s' alocada no bucket [%d] com tipo [%s]\n",
        name,
        h,
        symbol_type_name(type)
    );

    return s;
}

void update_symbol_type(char *name, SymbolType type) {
    Symbol *symbol = lookup_symbol(name);

    if(symbol == NULL) {
        insert_symbol(name, type);
        return;
    }

    if(type != TYPE_UNKNOWN && type != TYPE_ERROR) {
        symbol->type = type;
    }
}
