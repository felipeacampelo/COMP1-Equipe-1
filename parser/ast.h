#ifndef AST_H
#define AST_H

typedef enum {
    NODE_INT,      
    NODE_ID,       
    NODE_OP,       
    NODE_PRINT,    
    NODE_ASSIGN,   
    NODE_IF,       
    NODE_WHILE,    
    NODE_BLOCK
} NodeType;

typedef struct ast_node {
    NodeType type;
    int int_val;
    double float_val;            
    char *id_val;           
    struct ast_node *left;  
    struct ast_node *right; 
} ASTNode;

ASTNode* create_int_node(int val);
ASTNode* create_id_node(char *id);
ASTNode* create_op_node(NodeType type, ASTNode *left, ASTNode *right);
ASTNode* create_print_node(ASTNode *expr);
ASTNode* create_if_node(ASTNode *codition, ASTNode *body);
ASTNode* create_while_node(ASTNode *codition, ASTNode *body);
ASTNode* create_block_node(ASTNode *v1, ASTNode *v2);
void print_tree(ASTNode *node, int level);

#endif