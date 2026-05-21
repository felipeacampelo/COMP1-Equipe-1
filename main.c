#include <stdio.h>
#include "parser/ast.h"
#include "java_gen.h"

extern FILE *yyin;
extern ASTNode *root;

int main(int argc, char **argv){
    if(argc <2){
        fprintf(stderr, "Uso: %s arquivo.py", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");


    yyparse();

    char *java_file = (argc > 2) ? argv[2] : "output.java";

    start_java(java_file);
    generate_java(root);
    finish_java();

    fclose(yyin);
    return 0;
}