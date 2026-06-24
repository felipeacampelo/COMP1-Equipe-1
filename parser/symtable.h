#ifndef SYMTABLE_H
#define SYMTABLE_H

typedef enum SymbolType {
    TYPE_UNKNOWN,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_ERROR
} SymbolType;

typedef struct no_ast NoAST;

typedef struct ExprInfo {
    NoAST *node;
    SymbolType type;
} ExprInfo;

typedef struct Symbol {
    char *name;
    SymbolType type;
    struct Symbol *next;
} Symbol;

Symbol* lookup_symbol(char *name);
Symbol* insert_symbol(char *name, SymbolType type);
void update_symbol_type(char *name, SymbolType type);
const char* symbol_type_name(SymbolType type);

#endif
