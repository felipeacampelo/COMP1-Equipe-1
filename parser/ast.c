#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

NoAST* create_int_node(int val) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_INT;
        node->int_val = val;
        node->op_val = NULL;
        node->left = node->right = NULL;
    return node;
}

NoAST* create_id_node(char *id) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_ID;
        node->id_val = strdup(id);
        node->op_val = NULL;
        node->left = node->right = NULL;
    return node;
}

NoAST* create_op_node(NodeType type, char *op, NoAST *left, NoAST *right) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = type;
        node->op_val = op ? strdup(op) : NULL;
        node->left = left;
        node->right = right;
    return node;
}

NoAST* create_if_node(NoAST *codition, NoAST *body) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_IF;
        node->left = codition;
        node->right = body;
    return node;
}

NoAST* create_while_node(NoAST *codition, NoAST *body) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_WHILE;
        node->left = codition;
        node->right = body;
    return node;
}

NoAST* create_print_node(NoAST *expr) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_PRINT;
        node->left = expr;
        node->right = NULL;
    return node;
}

NoAST* create_block_node(NoAST *v1, NoAST *v2) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_BLOCK;
        node->left = v1;
        node->right = v2;
    return node;
}

NoAST* create_for_node(NoAST *iter_var, NoAST *body, NoAST *iterable) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_FOR;
        node->left = create_block_node(iter_var, iterable);
        node->right = body;
    return node;

}

NoAST* create_range_node(NoAST *start, NoAST *end) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_RANGE;
        node->left = start; 
        node->right = end; 
    return node;
}

NoAST* create_if_else_node(NoAST *condition, NoAST *if_body, NoAST *else_body) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_IF_ELSE;
        node->left = condition;
        node->right = if_body;
        node->else_body = else_body;
    return node;
}

void print_tree(NoAST *node, int level) {
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
            // Agora imprime o símbolo junto
            if(node->op_val) printf("OPERADOR: %s\n", node->op_val); 
            else printf("OPERADOR\n");
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

void optimize_ast(NoAST *node) {
    if (node == NULL) return;

    optimize_ast(node->left);
    optimize_ast(node->right);
    optimize_ast(node->else_body);

    if (node->type == NODE_OP && node->left && node->right &&
        node->left->type == NODE_INT && node->right->type == NODE_INT) {
        
        int v_left = node->left->int_val;
        int v_right = node->right->int_val;
        int result = 0;

        if (strcmp(node->op_val, "+") == 0) result = v_left + v_right;
        else if (strcmp(node->op_val, "-") == 0) result = v_left - v_right;
        else if (strcmp(node->op_val, "*") == 0) result = v_left * v_right;
        else if (strcmp(node->op_val, "/") == 0 && v_right != 0) result = v_left / v_right;
        else return;

        node->type = NODE_INT;
        node->int_val = result;
        free(node->left); free(node->right);
        node->left = NULL; node->right = NULL;
    }
}

int temp_count = 0;
int label_count = 0;

int new_temp() { return ++temp_count; }
int new_label() { return ++label_count; }

char* generate_tac(NoAST *node) {
    if (node == NULL) return "";
    static char result[50]; 

    switch (node->type) {
        case NODE_INT: 
            sprintf(result, "%d", node->int_val);
            return strdup(result);
            
        case NODE_ID:
            return node->id_val;

        case NODE_BLOCK:
            generate_tac(node->left);
            generate_tac(node->right);
            return "";

        case NODE_ASSIGN: {
            char* right_side = generate_tac(node->right);
            printf("\t%s = %s\n", node->left->id_val, right_side);
            return "";
        }

        case NODE_OP: {
            char* left = generate_tac(node->left);
            char* right = generate_tac(node->right);
            int temp = new_temp();
            printf("\tt%d = %s %s %s\n", temp, left, node->op_val, right); 
            sprintf(result, "t%d", temp);
            return strdup(result);
        }

        case NODE_WHILE: {
            int l_start = new_label();
            int l_end = new_label();
            printf("L%d:\n", l_start);
            char* cond = generate_tac(node->left);
            printf("\tIf(False) %s JMP L%d\n", cond, l_end);
            generate_tac(node->right);
            printf("\tJMP L%d\n", l_start);
            printf("L%d:\n", l_end);
            return "";
        }

        case NODE_IF: {
            char* cond = generate_tac(node->left);
            int l_end = new_label();
            printf("\tIf(False) %s JMP L%d\n", cond, l_end);
            generate_tac(node->right);
            printf("L%d:\n", l_end);
            return "";
        }

        case NODE_IF_ELSE: {
            char* cond = generate_tac(node->left);
            int l_false = new_label();
            int l_end = new_label();
            printf("\tIf(False) %s JMP L%d\n", cond, l_false);
            generate_tac(node->right); 
            printf("\tJMP L%d\n", l_end);
            printf("L%d:\n", l_false);
            generate_tac(node->else_body); 
            printf("L%d:\n", l_end);
            return "";
        }

        case NODE_PRINT: {
            char* val = generate_tac(node->left);
            printf("\tprint %s\n", val);
            return "";
        }
        default: return "";
    }
}

void compile_intermediate(NoAST *root) {
    optimize_ast(root);
    printf("\n--- CODIGO INTERMEDIARIO (TAC) ---\n");
    generate_tac(root);
}