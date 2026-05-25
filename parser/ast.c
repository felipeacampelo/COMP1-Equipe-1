#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode* create_int_node(int val) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_INT;
    node->int_val = val;
    node->left = node->right = NULL;
    return node;
}

ASTNode* create_id_node(char *id) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_ID;
    node->id_val = strdup(id);
    node->left = node->right = NULL;

    
    return node;
}

ASTNode* create_op_node(char *op, ASTNode *left, ASTNode *right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_OP;
    node->id_val = strdup(op);
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* create_if_node(ASTNode *codition, ASTNode *body) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_IF;
    node->left = codition;
    node->right = body;
    return node;
}

ASTNode* create_while_node(ASTNode *codition, ASTNode *body) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_WHILE;
    node->left = codition;
    node->right = body;
    return node;
}

ASTNode* create_print_node(ASTNode *expr) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_PRINT;
    node->left = expr;
    node->right = NULL;
    return node;
}

ASTNode* create_block_node(ASTNode *v1, ASTNode *v2) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_BLOCK;
    node->left = v1;
    node->right = v2;
    return node;
}

ASTNode* create_for_node(char *var, ASTNode *loop_limit, ASTNode *loop_body){
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_FOR;
    node->id_val = strdup(var);
    node->left = loop_limit;
    node->right = loop_body;
    return node;
}

ASTNode* create_range_node(ASTNode*de_num){
    //if(de_num > ate_num) return NULL;
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_RANGE;
    node->right = de_num;
    return node;
}

ASTNode* create_array_node(ASTNode*resto_do_array, int valor){
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY;
    node->left = resto_do_array;
    node->int_val = valor;
    return node;
}


// Visualizador da árvore no terminal
void print_tree(ASTNode *node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) printf("  ");

    switch (node->type) {
        case NODE_INT: 
            printf("NUM: %d\n", node->int_val); 
            break;

        case NODE_ID:  
            printf("ID: %s\n", node->id_val); 
            break;

        case NODE_OP:  
            printf("OPERADOR\n"); 
            print_tree(node->left, level + 1);
            print_tree(node->right, level + 1);
            break;

        case NODE_ASSIGN: 
            printf("=\n"); 
            print_tree(node->left, level + 1);
            print_tree(node->right, level + 1);
            break;

        case NODE_PRINT:
            printf("PRINT\n");
            print_tree(node->left, level + 1);
            break;

        case NODE_IF:
            printf("IF\n");
            print_tree(node->left, level + 1); // Condição
            print_tree(node->right, level + 1); // Corpo
            break;

        case NODE_WHILE:
            printf("WHILE\n");
            print_tree(node->left, level + 1);
            print_tree(node->right, level + 1);
            break;

        case NODE_BLOCK:
            if (node->left) print_tree(node->left, level);
            if (node->right) print_tree(node->right, level);
            break;        

        case NODE_FOR:
            printf("FOR: %s\n", node->id_val);
            if (node->left){
                //printf("no range = %d\n", node->left->type);
                print_tree(node->left, level);
            }
            if (node->right) print_tree(node->right, level+1);
            break;
        
        case NODE_RANGE:
            printf("RANGE %d\n", node->right->int_val);
            print_tree(node->right, level);
            break;

        default: printf("No que nao sabemos\n");
    }
    
}