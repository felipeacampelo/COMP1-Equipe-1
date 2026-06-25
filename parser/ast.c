#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "../java_gen.h"

NoAST* create_int_node(int val) {
    NoAST* node = malloc(sizeof(NoAST));
    node->type = NODE_INT;
    node->int_val = val;
    node->left = node->right = node->else_body = NULL;
    node->op_val = NULL;
    return node;
}

NoAST* create_bool_node(int value) {
    NoAST* node = malloc(sizeof(NoAST));
    node->type = NODE_BOOL;
    node->bool_val = value;
    node->left = node->right = node->else_body = NULL;
    return node;
}

NoAST* create_id_node(char *id) {
    NoAST* node = malloc(sizeof(NoAST));
    node->type = NODE_ID;
    node->id_val = strdup(id);
    node->left = node->right = node->else_body = NULL;
    node->op_val = NULL;
    return node;
}

NoAST* create_float_node(double val) {
    NoAST* node = malloc(sizeof(NoAST));
    node->type = NODE_FLOAT;
    node->float_val = val;
    node->left = node->right = node->else_body = NULL;
    return node;
}

NoAST* create_string_node(char *str) {
    NoAST* node = malloc(sizeof(NoAST));
    node->type = NODE_STRING;
    node->str_val = strdup(str);
    node->left = node->right = node->else_body = NULL;
    return node;
}

NoAST* create_op_node(NodeType type, char *op, NoAST *l, NoAST *r) {
    NoAST* node = malloc(sizeof(NoAST));
    node->type = type;
    node->op_val = op ? strdup(op) : NULL;
    node->left = l;
    node->right = r;
    node->else_body = NULL;
    return node;
}

NoAST* create_print_node(NoAST *expr) {
    NoAST* node = malloc(sizeof(NoAST));
    node->type = NODE_PRINT;
    node->left = expr;
    node->right = node->else_body = NULL;
    return node;
}

NoAST* create_if_node(NoAST *cond, NoAST *body) {
    NoAST* node = malloc(sizeof(NoAST));
    node->type = NODE_IF;
    node->left = cond;
    node->right = body;
    node->else_body = NULL;
    return node;
}

NoAST* create_if_else_node(NoAST *cond, NoAST *ifb, NoAST *elseb) {
    NoAST* node = malloc(sizeof(NoAST));
    node->type = NODE_IF_ELSE;
    node->left = cond;
    node->right = ifb;
    node->else_body = elseb;
    return node;
}

NoAST* create_while_node(NoAST *cond, NoAST *body) {
    NoAST* node = malloc(sizeof(NoAST));
    node->type = NODE_WHILE;
    node->left = cond;
    node->right = body;
    node->else_body = NULL;
    return node;
}

NoAST* create_block_node(NoAST *a, NoAST *b) {
    NoAST* node = malloc(sizeof(NoAST));
    node->type = NODE_BLOCK;
    node->left = a;
    node->right = b;
    node->else_body = NULL;
    return node;
}

NoAST* create_range_node(NoAST *start, NoAST *end) {
    NoAST* node = malloc(sizeof(NoAST));
    node->type = NODE_RANGE;
    node->left = start;
    node->right = end;
    return node;
}

NoAST* create_for_node(NoAST *iter, NoAST *body, NoAST *range) {
    NoAST* node = malloc(sizeof(NoAST));
    node->type = NODE_FOR;
    node->left = create_block_node(iter, range);
    node->right = body;
    return node;
}

void print_tree(NoAST *node, int level) {
    if (!node) return;

    for (int i = 0; i < level; i++) printf("  ");

    switch (node->type) {
        case NODE_INT:
            printf("NUM: %d\n", node->int_val);
            break;

        case NODE_BOOL:
            printf("BOOL: %s\n", node->bool_val ? "True" : "False");
            break;

        case NODE_FLOAT:
            printf("FLOAT: %f\n", node->float_val);
            break;

        case NODE_STRING:
            printf("STRING: %s\n", node->str_val);
            break;

        case NODE_ID:
            printf("ID: %s\n", node->id_val);
            break;

        case NODE_OP:
            printf("OP: %s\n", node->op_val);
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
            print_tree(node->left, level + 1);
            print_tree(node->right, level + 1);
            break;

        case NODE_IF_ELSE:
            printf("IF\n");
            print_tree(node->left, level + 1);
            print_tree(node->right, level + 1);
            printf("ELSE\n");
            print_tree(node->else_body, level + 1);
            break;

        case NODE_WHILE:
            printf("WHILE\n");
            print_tree(node->left, level + 1);
            print_tree(node->right, level + 1);
            break;

        case NODE_BLOCK:
            print_tree(node->left, level);
            print_tree(node->right, level);
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

        case NODE_INPUT:
            printf("INPUT()\n");
            break;

        default:
            printf("UNKNOWN\n");
    }
}

void optimize_ast(NoAST *node) {
    if (!node) return;

    optimize_ast(node->left);
    optimize_ast(node->right);
    optimize_ast(node->else_body);

    if (node->type == NODE_OP &&
        node->left && node->right &&
        node->left->type == NODE_INT &&
        node->right->type == NODE_INT) {

        int a = node->left->int_val;
        int b = node->right->int_val;
        int r = 0;

        if (strcmp(node->op_val, "+") == 0) r = a + b;
        else if (strcmp(node->op_val, "-") == 0) r = a - b;
        else if (strcmp(node->op_val, "*") == 0) r = a * b;
        else if (strcmp(node->op_val, "/") == 0 && b != 0) r = a / b;
        else return;

        node->type = NODE_INT;
        node->int_val = r;

        free(node->left);
        free(node->right);
        node->left = node->right = NULL;
    }
}

void compile_program(NoAST *root) {
    optimize_ast(root);
    compile_java(root, "Main.java");
}
