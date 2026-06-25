#ifndef AST_H
#define AST_H

typedef enum {
    NODE_INT,      
    NODE_BOOL,
    NODE_STRING, 
    NODE_ID,        
    NODE_OP,        
    NODE_PRINT,     
    NODE_ASSIGN,    
    NODE_IF,        
    NODE_IF_ELSE,   
    NODE_WHILE,     
    NODE_FOR,       
    NODE_RANGE,     
    NODE_BLOCK,
    NODE_INPUT,
    NODE_FLOAT,     
} NodeType;

typedef struct no_ast {
    NodeType type;
    int int_val;
    int bool_val;
    char *str_val;
    double float_val;            
    char *id_val;           
    char *op_val;
    struct no_ast *left;  
    struct no_ast *right; 
    struct no_ast *else_body;

} NoAST;

// Funções para criar os nós
NoAST* create_int_node(int val);
NoAST* create_bool_node(int value);
NoAST* create_id_node(char *id);
NoAST* create_float_node(double valor);
NoAST* create_string_node(char *val);
NoAST* create_op_node(NodeType type, char *op, NoAST *left, NoAST *right);
NoAST* create_print_node(NoAST *expr);
NoAST* create_if_node(NoAST *codition, NoAST *body);
NoAST* create_if_else_node(NoAST *condition, NoAST *if_body, NoAST *else_body);
NoAST* create_while_node(NoAST *codition, NoAST *body);
NoAST* create_block_node(NoAST *v1, NoAST *v2);
NoAST* create_range_node(NoAST *start, NoAST *end);
NoAST* create_for_node(NoAST *iter_var, NoAST *body, NoAST *iterable);
NoAST* create_string_node(char *str);

void print_tree(NoAST *node, int level);
void optimize_ast(NoAST *node);
void compile_program(NoAST *root);

#endif
