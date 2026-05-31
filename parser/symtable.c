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

void insert_symbol(char *name) {
    if(lookup_symbol(name) != NULL) return; // Se já existe, sai
    
    unsigned int h = hash(name);
    Symbol *s = malloc(sizeof(Symbol));
    s->name = strdup(name);
    s->next = symtable[h];
    symtable[h] = s;

    printf("Tabela de Símbolos Variável: '%s' alocada no bucket [%d]\n", name, h);
}