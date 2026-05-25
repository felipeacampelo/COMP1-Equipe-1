#ifndef JAVA_GEN_H
#define JAVA_GEN_H

#include "parser/ast.h"
#include <stdio.h>
#include <stdlib.h>

void generate_java(ASTNode*node);

void start_java(char *file);

void finish_java();

#endif