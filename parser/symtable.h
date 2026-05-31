#ifndef SYMTABLE_H
#define SYMTABLE_H

typedef struct Symbol {
    char *name;
    struct Symbol *next;
} Symbol;

void insert_symbol(char *name);
Symbol* lookup_symbol(char *name);

#endif