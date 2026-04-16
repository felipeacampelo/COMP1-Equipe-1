#ifndef AST_H
#define AST_H

// Tipos de nós que o seu compilador Python reconhece
typedef enum {
    NODE_INT,      // Números
    NODE_ID,       // Variáveis
    NODE_OP,       // Operações (+, -, *, /)
    NODE_PRINT,    // Comando print
    NODE_ASSIGN,   // Atribuição (=)
    NODE_IF        // Comando If
} NodeType;

typedef struct ast_node {
    NodeType type;
    int int_val;            
    char *id_val;           
    struct ast_node *left;  
    struct ast_node *right; 
} ASTNode;

// Funções para criar os nós
ASTNode* create_int_node(int val);
ASTNode* create_id_node(char *id);
ASTNode* create_op_node(NodeType type, ASTNode *left, ASTNode *right);
void print_tree(ASTNode *node, int level);

#endif