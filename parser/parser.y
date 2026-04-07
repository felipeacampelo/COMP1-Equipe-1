%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%union{
    int intValue;
    char *id;
}

%token <intValue> NUM
%token <id> ID
%token PLUS MINUS TIMES DIV
%token ASSIGN
%token LPAREN RPAREN
%token PRINT

%left PLUS MINUS
%left TIMES DIV

%type <intValue> expr term factor

%%

program:
    stmt
;

stmt:
    ID ASSIGN expr{
        printf("Atribuicao reconhecida\n");
    }
    | PRINT LPAREN NUM RPAREN{
        printf("Print reconhecido\n");
    }
;

expr:
    expr PLUS term{
        $$ = $1 + $3;
    }
    | expr MINUS term{
        $$ = $1 - $3;
    }
    | term{
        $$ = $1;
    }
;

term:
    term TIMES factor{
        $$ = $1 * $3;
    }
    | term DIV factor{
        $$ = $1 / $3;
    }
    | factor{
        $$ = $1;
    }
;

factor:
    NUM{
        $$ = $1;
    }
    | ID{
        $$ = 0;
    }
    | LPAREN expr RPAREN{
        $$ = $2;
    }
;

%%

void yyerror(const char *s){
    printf("Erro sintatico\n");
}

int main(){
    return yyparse();
}