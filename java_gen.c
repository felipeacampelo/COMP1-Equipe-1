#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "java_gen.h"

typedef struct {
    char name[50];
    const char *type;
} JavaVar;

static JavaVar declared[100];
static int n_decl = 0;

static void generate_java(NoAST *node, FILE *out, int lvl);

static int find_declared(char *name) {
    for (int i = 0; i < n_decl; i++) {
        if (strcmp(declared[i].name, name) == 0) {
            return i;
        }
    }

    return -1;
}

static int was_declared(char *name) {
    return find_declared(name) >= 0;
}

static const char* declared_type(char *name) {
    int idx = find_declared(name);
    if (idx >= 0) {
        return declared[idx].type;
    }

    return "int";
}

static void mark_declared(char *name, const char *type) {
    strcpy(declared[n_decl].name, name);
    declared[n_decl].type = type;
    n_decl++;
}

static void indent(FILE *out, int l) {
    for (int i = 0; i < l; i++) {
        fprintf(out, "    ");
    }
}

static int is_comparison_op(const char *op) {
    return strcmp(op, ">") == 0 ||
           strcmp(op, "<") == 0 ||
           strcmp(op, "==") == 0 ||
           strcmp(op, "!=") == 0;
}

static const char* infer_type(NoAST *node) {
    if (!node) return "int";

    switch (node->type) {
        case NODE_INT:
            return "int";

        case NODE_STRING:
            return "String";

        case NODE_FLOAT:
            return "double";

        case NODE_BOOL:
            return "boolean";

        case NODE_ID:
            return declared_type(node->id_val);

        case NODE_OP:
            if (node->op_val && (is_comparison_op(node->op_val) || strcmp(node->op_val, "!") == 0)) {
                return "boolean";
            }

            if ((node->left && strcmp(infer_type(node->left), "double") == 0) ||
                (node->right && strcmp(infer_type(node->right), "double") == 0)) {
                return "double";
            }

            return "int";

        default:
            return "int";
    }
}

static int is_boolean_expr(NoAST *node) {
    return strcmp(infer_type(node), "boolean") == 0;
}

static void generate_java_condition(NoAST *node, FILE *out) {
    if (is_boolean_expr(node)) {
        generate_java(node, out, 0);
        return;
    }

    generate_java(node, out, 0);
    fprintf(out, " != 0");
}

static void generate_java(NoAST *node, FILE *out, int lvl) {
    if (!node) return;

    switch (node->type) {
        case NODE_INT:
            fprintf(out, "%d", node->int_val);
            break;

        case NODE_FLOAT:
            fprintf(out, "%f", node->float_val);
            break;

        case NODE_BOOL:
            fprintf(out, "%s", node->bool_val ? "true" : "false");
            break;

        case NODE_STRING:
            fprintf(out, "\"%s\"", node->str_val);
            break;

        case NODE_ID:
            fprintf(out, "%s", node->id_val);
            break;

        case NODE_OP:
            if (node->op_val && strcmp(node->op_val, "!") == 0) {
                fprintf(out, "!");
                generate_java(node->left, out, 0);
            } else if (node->op_val && strcmp(node->op_val, "//") == 0) {
                if (strcmp(infer_type(node), "double") == 0) {
                    fprintf(out, "Math.floor(");
                    generate_java(node->left, out, 0);
                    fprintf(out, " / ");
                    generate_java(node->right, out, 0);
                    fprintf(out, ")");
                } else {
                    generate_java(node->left, out, 0);
                    fprintf(out, " / ");
                    generate_java(node->right, out, 0);
                }
            } else {
                generate_java(node->left, out, 0);
                fprintf(out, " %s ", node->op_val);
                generate_java(node->right, out, 0);
            }
            break;

        case NODE_ASSIGN:
            indent(out, lvl);

            if (!was_declared(node->left->id_val)) {
                const char *type = infer_type(node->right);
                fprintf(out, "%s ", type);
                mark_declared(node->left->id_val, type);
            }

            fprintf(out, "%s = ", node->left->id_val);
            generate_java(node->right, out, 0);
            fprintf(out, ";\n");
            break;

        case NODE_PRINT:
            indent(out, lvl);
            fprintf(out, "System.out.println(");
            generate_java(node->left, out, 0);
            fprintf(out, ");\n");
            break;

        case NODE_BLOCK:
            generate_java(node->left, out, lvl);
            generate_java(node->right, out, lvl);
            break;

        case NODE_IF:
            indent(out, lvl);
            fprintf(out, "if (");
            generate_java_condition(node->left, out);
            fprintf(out, ") {\n");
            generate_java(node->right, out, lvl + 1);
            indent(out, lvl);
            fprintf(out, "}\n");
            break;

        case NODE_IF_ELSE:
            indent(out, lvl);
            fprintf(out, "if (");
            generate_java_condition(node->left, out);
            fprintf(out, ") {\n");
            generate_java(node->right, out, lvl + 1);
            indent(out, lvl);
            fprintf(out, "} else {\n");
            generate_java(node->else_body, out, lvl + 1);
            indent(out, lvl);
            fprintf(out, "}\n");
            break;

        case NODE_WHILE:
            indent(out, lvl);
            fprintf(out, "while (");
            generate_java_condition(node->left, out);
            fprintf(out, ") {\n");
            generate_java(node->right, out, lvl + 1);
            indent(out, lvl);
            fprintf(out, "}\n");
            break;

        default:
            break;
    }
}

void compile_java(NoAST *root, const char *filename) {
    FILE *out = fopen(filename, "w");
    if (!out) return;

    n_decl = 0;

    fprintf(out, "public class Main {\n");
    fprintf(out, "    public static void main(String[] args) {\n");

    generate_java(root, out, 2);

    fprintf(out, "    }\n");
    fprintf(out, "}\n");

    fclose(out);
}
