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

typedef struct ast_node {
    NodeType type;
    int int_val;
    double float_val;            
    char *id_val;           
    struct ast_node *left;  
    struct ast_node *right; 
    struct ast_node *else_body;
} ASTNode;

// Funções para criar os nós
ASTNode* create_int_node(int val);
ASTNode* create_id_node(char *id);
ASTNode* create_op_node(NodeType type, ASTNode *left, ASTNode *right);
ASTNode* create_print_node(ASTNode *expr);
ASTNode* create_if_node(ASTNode *codition, ASTNode *body);
ASTNode* create_if_else_node(ASTNode *condition, ASTNode *if_body, ASTNode *else_body);
ASTNode* create_while_node(ASTNode *codition, ASTNode *body);
ASTNode* create_block_node(ASTNode *v1, ASTNode *v2);
ASTNode* create_range_node(ASTNode *start, ASTNode *end);
ASTNode* create_for_node(ASTNode *iter_var, ASTNode *body, ASTNode *iterable);



void print_tree(ASTNode *node, int level);

#endif