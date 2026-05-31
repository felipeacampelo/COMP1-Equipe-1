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

ASTNode* create_block_node(ASTNode *v1, ASTNode *v2) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = NODE_BLOCK;
        node->left = v1;
        node->right = v2;
    return node;
}

ASTNode* create_for_node(ASTNode *iter_var, ASTNode *body, ASTNode *iterable) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = NODE_FOR;
        node->left = create_block_node(iter_var, iterable);
        node->right = body;
    return node;

}

ASTNode* create_range_node(ASTNode *start, ASTNode *end) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = NODE_RANGE;
        node->left = start; 
        node->right = end; 
    return node;
}

ASTNode* create_if_else_node(ASTNode *condition, ASTNode *if_body, ASTNode *else_body) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = NODE_IF_ELSE;
        node->left = condition;
        node->right = if_body;
        node->else_body = else_body;
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
        
        case NODE_IF_ELSE:
            printf("IF\n");
            print_tree(node->left, level + 1);  // Condição
            print_tree(node->right, level + 1); // Corpo do IF
            for (int i = 0; i < level; i++) printf("  "); // Mantém o alinhamento
            printf("ELSE\n");
            print_tree(node->else_body, level + 1); // Corpo do ELSE
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
            printf("FOR\n");
            print_tree(node->left, level + 1);
            print_tree(node->right, level + 1);
            break;
        
        case NODE_RANGE:
            printf("RANGE\n");
            print_tree(node->left, level + 1);
            print_tree(node->right, level + 1);
            break;    

        default: printf("No que nao sabemos\n");
    }
    
}