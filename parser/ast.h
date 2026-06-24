#ifndef AST_H
#define AST_H

typedef enum {
    NODE_INT,       // Números
    NODE_ID,        // Variáveis
    NODE_OP,        // Operações (+, -, *, /)
    NODE_PRINT,     // Comando print
    NODE_ASSIGN,    // Atribuição (=)
    NODE_IF,        // Comando If
    NODE_IF_ELSE,    // Adicione mais tipos de nós conforme necessário
    NODE_WHILE,     // Comando while
    NODE_FOR,       // Comando for
    NODE_RANGE,     // Comando for e range
    NODE_BLOCK     // Comando para blocos de código (if, while, for)
    
} NodeType;

typedef struct no_ast {
    NodeType type;
    int int_val;
    double float_val;            
    char *id_val;           
    char *op_val;
    struct no_ast *left;  
    struct no_ast *right; 
    struct no_ast *else_body;

} NoAST;

// Funções para criar os nós
NoAST* create_int_node(int val);
NoAST* create_id_node(char *id);
NoAST* create_op_node(NodeType type, char *op, NoAST *left, NoAST *right);
NoAST* create_print_node(NoAST *expr);
NoAST* create_if_node(NoAST *codition, NoAST *body);
NoAST* create_if_else_node(NoAST *condition, NoAST *if_body, NoAST *else_body);
NoAST* create_while_node(NoAST *codition, NoAST *body);
NoAST* create_block_node(NoAST *v1, NoAST *v2);
NoAST* create_range_node(NoAST *start, NoAST *end);
NoAST* create_for_node(NoAST *iter_var, NoAST *body, NoAST *iterable);



void print_tree(NoAST *node, int level);
void optimize_ast(NoAST *node);
void compile_intermediate(NoAST *root);

#endif