#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "java_gen.h"
#include "parser/symtable.h"

typedef struct JavaDeclaredVar {
    char *name;
    struct JavaDeclaredVar *next;
} JavaDeclaredVar;

static char* duplicate_string(const char *value) {
    char *copy = (char*)malloc(strlen(value) + 1);
    strcpy(copy, value);
    return copy;
}

static char* string_from_format(const char *fmt, ...) {
    va_list args;
    va_list copy_args;
    va_start(args, fmt);
    va_copy(copy_args, args);
    int size = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char *buffer = (char*)malloc(size + 1);
    vsnprintf(buffer, size + 1, fmt, copy_args);
    va_end(copy_args);
    return buffer;
}

static const char* java_type_name(SymbolType type) {
    switch(type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "double";
        case TYPE_BOOL: return "boolean";
        default: return "double";
    }
}

static int is_comparison_operator(const char *op) {
    return strcmp(op, ">") == 0 ||
           strcmp(op, "<") == 0 ||
           strcmp(op, "==") == 0 ||
           strcmp(op, "!=") == 0;
}

static SymbolType infer_node_type(NoAST *node) {
    if(node == NULL) return TYPE_UNKNOWN;

    switch(node->type) {
        case NODE_INT:
            return TYPE_INT;

        case NODE_FLOAT:
            return TYPE_FLOAT;

        case NODE_ID: {
            Symbol *symbol = lookup_symbol(node->id_val);
            return symbol ? symbol->type : TYPE_UNKNOWN;
        }

        case NODE_OP:
            if(node->op_val && is_comparison_operator(node->op_val)) {
                return TYPE_BOOL;
            }

            if(node->op_val && strcmp(node->op_val, "=") == 0) {
                return infer_node_type(node->right);
            }

            if(infer_node_type(node->left) == TYPE_FLOAT || infer_node_type(node->right) == TYPE_FLOAT) {
                return TYPE_FLOAT;
            }

            return TYPE_INT;

        default:
            return TYPE_UNKNOWN;
    }
}

static int java_var_declared(JavaDeclaredVar *declared, const char *name) {
    for(JavaDeclaredVar *current = declared; current != NULL; current = current->next) {
        if(strcmp(current->name, name) == 0) return 1;
    }

    return 0;
}

static void java_mark_declared(JavaDeclaredVar **declared, const char *name) {
    if(java_var_declared(*declared, name)) return;

    JavaDeclaredVar *entry = (JavaDeclaredVar*)malloc(sizeof(JavaDeclaredVar));
    entry->name = duplicate_string(name);
    entry->next = *declared;
    *declared = entry;
}

static void free_java_declared(JavaDeclaredVar *declared) {
    while(declared != NULL) {
        JavaDeclaredVar *next = declared->next;
        free(declared->name);
        free(declared);
        declared = next;
    }
}

static void write_indent(FILE *output, int indent) {
    for(int i = 0; i < indent; i++) {
        fputs("    ", output);
    }
}

static char* generate_java_expr(NoAST *node) {
    if(node == NULL) return duplicate_string("");

    switch(node->type) {
        case NODE_INT:
            return string_from_format("%d", node->int_val);

        case NODE_FLOAT:
            return string_from_format("%.2f", node->float_val);

        case NODE_ID:
            return duplicate_string(node->id_val);

        case NODE_OP: {
            char *left = generate_java_expr(node->left);
            char *right = generate_java_expr(node->right);
            char *expr = string_from_format("(%s %s %s)", left, node->op_val, right);
            free(left);
            free(right);
            return expr;
        }

        default:
            return duplicate_string("");
    }
}

static char* generate_java_condition(NoAST *node) {
    char *expr = generate_java_expr(node);
    SymbolType type = infer_node_type(node);

    if(type == TYPE_BOOL) {
        return expr;
    }

    char *condition = string_from_format("(%s != 0)", expr);
    free(expr);
    return condition;
}

static void generate_java_stmt(NoAST *node, FILE *output, int indent, JavaDeclaredVar **declared) {
    if(node == NULL) return;

    switch(node->type) {
        case NODE_BLOCK:
            generate_java_stmt(node->left, output, indent, declared);
            generate_java_stmt(node->right, output, indent, declared);
            break;

        case NODE_ASSIGN: {
            char *right = generate_java_expr(node->right);
            Symbol *symbol = lookup_symbol(node->left->id_val);
            const char *java_type = java_type_name(symbol ? symbol->type : TYPE_INT);

            write_indent(output, indent);

            if(!java_var_declared(*declared, node->left->id_val)) {
                fprintf(output, "%s %s = %s;\n", java_type, node->left->id_val, right);
                java_mark_declared(declared, node->left->id_val);
            } else {
                fprintf(output, "%s = %s;\n", node->left->id_val, right);
            }

            free(right);
            break;
        }

        case NODE_PRINT: {
            char *value = generate_java_expr(node->left);
            write_indent(output, indent);
            fprintf(output, "System.out.println(%s);\n", value);
            free(value);
            break;
        }

        case NODE_IF: {
            char *condition = generate_java_condition(node->left);
            write_indent(output, indent);
            fprintf(output, "if %s {\n", condition);
            generate_java_stmt(node->right, output, indent + 1, declared);
            write_indent(output, indent);
            fprintf(output, "}\n");
            free(condition);
            break;
        }

        case NODE_IF_ELSE: {
            char *condition = generate_java_condition(node->left);
            write_indent(output, indent);
            fprintf(output, "if %s {\n", condition);
            generate_java_stmt(node->right, output, indent + 1, declared);
            write_indent(output, indent);
            fprintf(output, "} else {\n");
            generate_java_stmt(node->else_body, output, indent + 1, declared);
            write_indent(output, indent);
            fprintf(output, "}\n");
            free(condition);
            break;
        }

        case NODE_WHILE: {
            char *condition = generate_java_condition(node->left);
            write_indent(output, indent);
            fprintf(output, "while %s {\n", condition);
            generate_java_stmt(node->right, output, indent + 1, declared);
            write_indent(output, indent);
            fprintf(output, "}\n");
            free(condition);
            break;
        }

        default:
            break;
    }
}

void compile_java(NoAST *root, const char *filename) {
    FILE *output = fopen(filename, "w");

    if(output == NULL) {
        printf("Erro ao gerar arquivo Java: %s\n", filename);
        return;
    }

    JavaDeclaredVar *declared = NULL;

    fprintf(output, "public class Main {\n");
    fprintf(output, "    public static void main(String[] args) {\n");
    generate_java_stmt(root, output, 2, &declared);
    fprintf(output, "    }\n");
    fprintf(output, "}\n");

    free_java_declared(declared);
    fclose(output);

    printf("\nCodigo Java gerado em %s\n", filename);
}
