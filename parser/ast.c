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

NoAST* create_float_node(double valor) {
    NoAST *node = (NoAST*) malloc(sizeof(NoAST));
    node->type = NODE_FLOAT;
    node->float_val = valor;
    node->left = NULL;
    node->right = NULL;
    return node;
}

NoAST* create_string_node(char* valor) {
    NoAST *node = (NoAST*) malloc(sizeof(NoAST));
    node->type = NODE_STRING;
    node->str_val = strdup(valor);
    node->left = NULL;
    node->right = NULL;
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

NoAST* create_print_node(NoAST *expr) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_PRINT;
        node->left = expr;
        node->right = NULL;
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

        case NODE_FLOAT:
            printf("FLOAT: %f\n", node->float_val);
            break;    

        case NODE_ID:  
            printf("ID: %s\n", node->id_val); 
            break;
        
        case NODE_STRING:
            printf("STRING: %s\n", node->str_val);
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

// Funciona JAVAAA

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

// Controle do java para as variaveis 
char declaradas[100][50];
int num_declaradas = 0;

int foi_declarada(char* nome) {
    for(int i = 0; i < num_declaradas; i++) {
        if(strcmp(declaradas[i], nome) == 0) return 1;
    }
    return 0;
}

void marca_declarada(char* nome) {
    strcpy(declaradas[num_declaradas++], nome);
}

void print_indent(FILE *output, int level) {
    for(int i = 0; i < level; i++) fprintf(output, "    ");
}

const char* inferir_tipo(NoAST *node) {
    if (node == NULL) return "int";
    if (node->type == NODE_STRING) return "String";
    if (node->type == NODE_FLOAT) return "double";
    if (node->type == NODE_OP) {
        const char* tipo_esq = inferir_tipo(node->left);
        const char* tipo_dir = inferir_tipo(node->right);
        
        // Se qualquer lado for texto, o Java transforma tudo em String (ex: "Idade: " + 10)
        if (strcmp(tipo_esq, "String") == 0 || strcmp(tipo_dir, "String") == 0) {
            return "String";
        }
        if (strcmp(tipo_esq, "double") == 0 || strcmp(tipo_dir, "double") == 0) {
            return "double";
        }
    }
    return "int"; 
}



// Ou vai ou nao vai, agora esse java tem que sair
// Codigo principal para gerar o java a partir da AST
void generate_java(NoAST *node, FILE *saida_java, int indent_level) {
    if (node == NULL) return;

    switch (node->type) {
        case NODE_INT: 
            fprintf(saida_java, "%d", node->int_val);
            break;
        
        case NODE_FLOAT: 
        fprintf(saida_java, "%f", node->float_val);
        break;
            
        case NODE_ID:
            fprintf(saida_java, "%s", node->id_val);
            break;
        
        case NODE_STRING: 
            fprintf(saida_java, "%s", node->str_val);
            break;    

        case NODE_BLOCK:
            generate_java(node->left, saida_java, indent_level);
            generate_java(node->right, saida_java, indent_level);
            break;

        case NODE_ASSIGN:
            print_indent(saida_java, indent_level);
            if (!foi_declarada(node->left->id_val)) {
                fprintf(saida_java, "%s ", inferir_tipo(node->right)); 
                marca_declarada(node->left->id_val);
            }
            fprintf(saida_java, "%s = ", node->left->id_val);
            generate_java(node->right, saida_java, 0);
            fprintf(saida_java, ";\n");
            break;

        case NODE_OP:
            generate_java(node->left, saida_java, 0);
            fprintf(saida_java, " %s ", node->op_val);
            generate_java(node->right, saida_java, 0);
            break;

        case NODE_WHILE:
            print_indent(saida_java, indent_level);
            fprintf(saida_java, "while (");
            generate_java(node->left, saida_java, 0);
            fprintf(saida_java, ") {\n");
            generate_java(node->right, saida_java, indent_level + 1);
            print_indent(saida_java, indent_level);
            fprintf(saida_java, "}\n");
            break;

        case NODE_IF:
            print_indent(saida_java, indent_level);
            fprintf(saida_java, "if (");
            generate_java(node->left, saida_java, 0);
            fprintf(saida_java, ") {\n");
            generate_java(node->right, saida_java, indent_level + 1);
            print_indent(saida_java, indent_level);
            fprintf(saida_java, "}\n");
            break;

        case NODE_IF_ELSE:
            print_indent(saida_java, indent_level);
            fprintf(saida_java, "if (");
            generate_java(node->left, saida_java, 0);
            fprintf(saida_java, ") {\n");
            generate_java(node->right, saida_java, indent_level + 1);
            print_indent(saida_java, indent_level);
            fprintf(saida_java, "} else {\n");
            generate_java(node->else_body, saida_java, indent_level + 1);
            print_indent(saida_java, indent_level);
            fprintf(saida_java, "}\n");
            break;

        case NODE_PRINT:
            print_indent(saida_java, indent_level);
            fprintf(saida_java, "System.out.println(");
            generate_java(node->left, saida_java, 0);
            fprintf(saida_java, ");\n");
            break;
            
        default: 
            break;
    }
}

// Compilação Final
void compile_intermediate(NoAST *root) {
    optimize_ast(root);

    FILE *saida_java = fopen("Main.java", "w");  
    if (!saida_java) {
        printf("Erro ao criar arquivo de saida!\n");
        return;
    }

    num_declaradas = 0; 
    fprintf(saida_java, "public class Main {\n"); // Escreve o "esqueleto" do Java
    fprintf(saida_java, "    public static void main(String[] args) {\n");
    
  
    generate_java(root, saida_java, 2);   // Vai gerar o nosso código dentro do main
    
    // Fecha as chaves da classe e do main
    fprintf(saida_java, "    }\n");
    fprintf(saida_java, "}\n");

    fclose(saida_java);
}