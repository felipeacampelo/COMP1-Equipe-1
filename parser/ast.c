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

ASTNode* create_op_node(NodeType type, ASTNode *left, ASTNode *right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
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

        default: printf("No que nao sabemos\n");
    }
    
}