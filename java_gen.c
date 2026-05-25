# include "java_gen.h"
#include <stdio.h>
#include <string.h>


FILE *java_output;
int indetacao;

void generate_java(ASTNode *node){
    if(!node){
        printf("no nao encontrado\n");
        return;
    }
    //fprintf(java_output, "  ");

    switch (node->type) {
        
        case NODE_INT:
            fprintf(java_output, "%d", node->int_val);
            break;

        case NODE_ID:
            fprintf(java_output, "%s", node->id_val);
            //printf("id\n");
            break;

        case NODE_OP:
            if(!strcmp(node->id_val, "=")){
                for(int i = 0; i <= indetacao; i++){
                    fprintf(java_output, "  ");
                }    

                generate_java(node->left);
                fprintf(java_output, " %s ", node->id_val);
                generate_java(node->right);

                fprintf(java_output, ";\n");
            }else{
                generate_java(node->left);
                fprintf(java_output, " %s ", node->id_val);
                generate_java(node->right);
            } 
            
            break;

        case NODE_PRINT:
            for(int i = 0; i <= indetacao; i++){
                fprintf(java_output, "  ");
            }
            fprintf(java_output, "System.Out.Println(\"");
            generate_java(node->left);
            fprintf(java_output, "\"); \n");
            //printf("node print terminado\n");
            break;

        case NODE_ASSIGN:
            fprintf(java_output, " = ");
            break;

        case NODE_IF:
            for(int i = 0; i <= indetacao; i++){
                fprintf(java_output, "  ");
            }
            indetacao += 1;
            fprintf(java_output, "if(");
            generate_java(node->left);
            fprintf(java_output, "){\n");
            generate_java(node->right);
            indetacao -= 1;
            for(int i = 0; i <= indetacao; i++){
                fprintf(java_output, "  ");
            }
            fprintf(java_output, "}");
            //printf("node if terminado\n");
            break;

        case NODE_WHILE:
            fprintf(java_output, "while(");
            generate_java(node->left);
            fprintf(java_output, "){\n");
            generate_java(node->right);
            fprintf(java_output, "}\n");
            break;

        case NODE_BLOCK:
            generate_java(node->left);
            //fprintf(java_output,"\n");
            generate_java(node->right);
            break;
        
        case NODE_FOR:
            for(int i = 0; i <= indetacao; i++){
                fprintf(java_output, "  ");
            }
            indetacao += 1;
            fprintf(java_output, "for (int %s : ", node->id_val);
            //i = 0 i<x i++
            
            generate_java(node->left);
            fprintf(java_output, "){\n");
            //bloco de codigo
            generate_java(node->right);
            indetacao -= 1;
            for(int i = 0; i <= indetacao; i++){
                fprintf(java_output, "  ");
            }
            fprintf(java_output, "}\n");

            break;

        case NODE_ARRAY:
            // Array
            break;

        case NODE_RANGE:
            //feito literal do pro for
            generate_java(node->right);
            break;

        default:
            printf("Tipo de nó desconhecido (%d)\n", node->type);
            break;
    }

}

void start_java(char *file){
    java_output = fopen(file, "w");
    if(!java_output){
        printf("ERRO, arquivo nao criado");
        exit(1);
    }
    indetacao = 2;
    fprintf(java_output, "public class Java_Traduzido{\n");
    fprintf(java_output, "   public static void main(String[] args) {\n");
    //printf("cabecalho terminado\n");
}

void finish_java(){
    fprintf(java_output, "\n   }\n}\n");
    fclose(java_output);
}