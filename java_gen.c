# include "java_gen.h"
#include <stdio.h>


FILE *java_output;

void generate_java(ASTNode *node){
    if(!node) return;

    switch (node->type) {
        case NODE_INT:
            fprintf(java_output, "%d", node->int_val);
            break;

        case NODE_ID:
            fprintf(java_output, "%s", node->id_val);
            break;

        case NODE_OP:
            fprintf(java_output, "%d %s %d", node->left, node->type, node->right);
            break;

        case NODE_PRINT:
            fprintf(java_output, "System.Out.Printl(\"%s\")", node->left);
            break;

        case NODE_ASSIGN:
            fprintf(java_output, " = ");
            break;

        case NODE_IF:
            fprintf(java_output, "if(");
            generate_java(node->left);
            fprintf(java_output, "){\n");
            generate_java(node->right);
            fprintf(java_output, ")");

            break;

        case NODE_WHILE:
            fprintf(java_output, "while(%s){%s}", node->left, node->right);
            break;

        case NODE_BLOCK:
            generate_java(node->right);
            generate_java(node->left);
            break;

        case NODE_FOR:
            fprintf(java_output, "for (int %s : ", node->id_val);
            //i = 0 i<x i++
            generate_java(node->left);
            fprintf(java_output, "){\n");
            //bloco de codigo
            generate_java(node->right);
            fprintf(java_output, "}");

            break;

        case NODE_ARRAY:
            // Array
            break;

        case NODE_RANGE:
            //feito literal do pro for
            generate_java(node->right);
            break;

        default:
            printf("Tipo de nó desconhecido\n");
            break;
    }

}

void start_java(char *file){
    java_output = fopen(file, "w");
    if(!java_output){
        printf("ERRO, arquivo nao criado");
        exit(1);
    }

    fprintf(java_output, "public class Java_Traduzido{\n");
    fprintf(java_output, "  public static void main(String[] args) {\n");
}

void finish_java(){
    fprintf(java_output, "\n    }\n}\n");
    fclose(java_output);
}