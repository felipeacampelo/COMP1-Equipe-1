---
layout: default
title: Documentação do Gerador da arvore sintatica abstrata
---

# Gerador da arvore Sintatica Abstrata

Implementação para gerar a arvore sintatica abstrata e organizar os nós

## Localização do Arquivo

```
parser/ast.c
parser/ast.h
```

## Estrutura

### Struct dos nós (ast.h)
```c
typedef struct no_ast {
    NodeType type;
    int int_val;
    double float_val;  
    char* str_val;          
    char *id_val;           
    char *op_val;
    struct no_ast *left;  
    struct no_ast *right; 
    struct no_ast *else_body;

} NoAST;
``` 

### Definição do NodeType (ast.h)
```c
typedef enum {
    NODE_INT,
    NODE_FLOAT,  
    NODE_STRING,     
    NODE_ID,        
    NODE_OP,        
    NODE_PRINT,     
    NODE_ASSIGN,    
    NODE_IF,        
    NODE_IF_ELSE,   
    NODE_WHILE,     
    NODE_FOR,       
    NODE_RANGE,     
    NODE_BLOCK     
} NodeType;
```

### Funções

#### create_int_node(int val)
- Cria um nó int e atribui seu valor númerico
```c
NoAST* create_int_node(int val) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_INT;
        node->int_val = val;
        node->op_val = NULL;
        node->left = node->right = NULL;
    return node;
}
```

#### create_id_node(char *id)
- Cria um nó de variavel e atribui seu indentificador
```c
NoAST* create_id_node(char *id) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_ID;
        node->id_val = strdup(id);
        node->op_val = NULL;
        node->left = node->right = NULL;
    return node;
}
```

#### create_float_node(double valor)
- Cria um nó de tipo floar e atribui seu valor
```c
NoAST* create_float_node(double valor) {
    NoAST *node = (NoAST*) malloc(sizeof(NoAST));
    node->type = NODE_FLOAT;
    node->float_val = valor;
    node->left = NULL;
    node->right = NULL;
    return node;
}
```

#### create_string_node(char* valor)
- Cria um nó de string e armazena a string
```c
NoAST* create_string_node(char* valor) {
    NoAST *node = (NoAST*) malloc(sizeof(NoAST));
    node->type = NODE_STRING;
    node->str_val = strdup(valor);
    node->left = NULL;
    node->right = NULL;
    return node;
}
```

#### create_op_node(NodeType type, char *op, NoAST *left, NoAST *right)
- Cria um nó de operador e salva o seu tipo como char
- Armazena à esquerda e à direita os nós das expressões em volta do operador
```c
NoAST* create_op_node(NodeType type, char *op, NoAST *left, NoAST *right) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = type;
        node->op_val = op ? strdup(op) : NULL;
        node->left = left;
        node->right = right;
    return node;
}
```

#### create_print_node(NoAST *expr)
- Cria nó de print
- Armazena à esquerda o nó da string a ser impressa
```c
NoAST* create_print_node(NoAST *expr) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_PRINT;
        node->left = expr;
        node->right = NULL;
    return node;
}
```

#### create_if_node(NoAST *codition, NoAST *body)
- Cria o nó de if
- À esquerda armazena o nó que contém a expressão condição
- À direita armazena o nó do bloco a ser executado caso o if seja verdade
```c
NoAST* create_if_node(NoAST *codition, NoAST *body) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_IF;
        node->left = codition;
        node->right = body;
    return node;
}
```

#### create_while_node(NoAST *codition, NoAST *body)
- Cria o nó while
- À esquerda armazena a condição do loop
- À direita armazena o bloco de código a ser repetido
```c
NoAST* create_while_node(NoAST *codition, NoAST *body) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_WHILE;
        node->left = codition;
        node->right = body;
    return node;
}
```

#### create_block_node(NoAST *v1, NoAST *v2)
- Cria o nó de bloco
- À esquerda armazena outro nó de bloco de código
- À direita armazena um stamtemnt, uma linha do código
```c
NoAST* create_block_node(NoAST *v1, NoAST *v2) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_BLOCK;
        node->left = v1;
        node->right = v2;
    return node;
}
```

#### create_for_node(NoAST *iter_var, NoAST *body, NoAST *iterable)
- Cria o nó de loop for
- À esquerda armazena o bloco da iteração do loop
- À direita armazena o bloco a ser repetido
```c
NoAST* create_for_node(NoAST *iter_var, NoAST *body, NoAST *iterable) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_FOR;
        node->left = create_block_node(iter_var, iterable);
        node->right = body;
    return node;

}
```

#### create_range_node(NoAST *start, NoAST *end)
- Cria o node de range para o loop
- A esquerda armazena o int onde o range começa
- A direita armazena o int onde o range termina
```c
NoAST* create_range_node(NoAST *start, NoAST *end) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_RANGE;
        node->left = start; 
        node->right = end; 
    return node;
}
```

#### create_if_else_node(NoAST *condition, NoAST *if_body, NoAST *else_body)
- Cria o nó de if else
- A esquerda armazena a condição
- A direita armazena o bloco a ser executado
- Else_body armazena o bloco do else
```c
NoAST* create_if_else_node(NoAST *condition, NoAST *if_body, NoAST *else_body) {
    NoAST* node = (NoAST*)malloc(sizeof(NoAST));
        node->type = NODE_IF_ELSE;
        node->left = condition;
        node->right = if_body;
        node->else_body = else_body;
    return node;
}
```


#### print_tree(NoAST *node, int level)
- Segue um switch case recursivo para imprimir a arvore
- Torna a arvore mais facil de se vizualizar
```c
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
```