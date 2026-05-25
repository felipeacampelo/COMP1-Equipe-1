#ifndef AST_H
#define AST_H

// Tipos de nós que o seu compilador Python reconhece
typedef enum {
    NODE_INT,      // Números
    NODE_ID,       // Variáveis
    NODE_OP,       // Operações (+, -, *, /)
    NODE_PRINT,    // Comando print
    NODE_ASSIGN,   // Atribuição (=)
    NODE_IF,        // Comando If
    NODE_WHILE,     // Comando while
    NODE_BLOCK,
    NODE_FOR,
    NODE_ARRAY,
    NODE_RANGE
} NodeType;

typedef struct ast_node {
    NodeType type;
    int int_val;
    double float_val;            
    char *id_val;           
    struct ast_node *left;  
    struct ast_node *right; 
} ASTNode;

// Funções para criar os nós
ASTNode* create_int_node(int val);
ASTNode* create_id_node(char *id);
ASTNode* create_op_node(char *op, ASTNode *left, ASTNode *right);
ASTNode* create_print_node(ASTNode *expr);
ASTNode* create_if_node(ASTNode *codition, ASTNode *body);
ASTNode* create_while_node(ASTNode *codition, ASTNode *body);
ASTNode* create_block_node(ASTNode *v1, ASTNode *v2);
ASTNode* create_for_node(char *v1, ASTNode *v2, ASTNode *loop_body);
ASTNode* create_array_node(ASTNode *resto_do_array, int valor);
ASTNode* create_range_node(ASTNode *v1);
void print_tree(ASTNode *node, int level);

#endif