%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../parser/parser.tab.h" 

int indents[100];
int top = 0;
int pending_dents = 0;

void push(int n) {
    top++;
    indents[top] = n;
}

%}

%%

"print" { 
    return PRINT; 
}

"if" { 
    return IF; 
}

"else" { 
    return ELSE; 
}

"while" { 
    return WHILE; 
}

"for" {
    return FOR;
}

"import" {
    return IMPORT;
}

"as" {
    return AS;
}

"from" {
    return FROM;
}

"input" {
    return INPUT;
}

"int" {
    return INT;
}

"double" {
    return DOUBLE;
}

"float" {
    return FLOAT;
}

"complex" {
    return COMPLEX;
}

"!" {
    return NOT;
}

">" { 
    return MT;
}

"<" { 
    return LT; 
}

"#".* { /* Ignorar comentário de linha */ }

"/*"([^*]|\*+[^*/])*\*+\/ { /* Ignorar comentários de bloco */ }

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.id = strdup(yytext); 
    return ID; 
}

[0-9]+\.[0-9]+ {
    yylval.floatValue = atof(yytext);
    return FLOAT_NUM;
}

[0-9]+ { 
    yylval.intValue = atoi(yytext); 
    return NUM;
}

"++" {
    return INCREMENT;
}

"+=" {
    return PLUS_ATRIBUTION;
}

"+" { 
    return PLUS; 
}

"-=" {
    return MINUS_ATRIBUTION;
}

"-" { 
    return MINUS; 
}

"*=" {
    return TIMES_ATRIBUTION;
}

"*" { 
    return TIMES; 
}

"//=" {
    return INT_DIV_ATRIBUTION;
}

"/=" {
    return DIV_ATRIBUTION;
}

"//" {
    return INT_DIV;
}

"/" { 
    return DIV; 
}

"==" { 
    return EQ; 
}

"!=" {
    return DIFF;
}

"=" { 
    return ASSIGN; 
}

"(" { 
    return LPAREN; 
}

")" { 
    return RPAREN; 
}

":" {
    return COLON;
}

\r?\n[ \t]* { 
    int indent = (yyleng - 1) / 4;

    if(yytext[0] == '\r') indent = (yyleng-2) / 4;
    
    if(indent > indents[top]) {
        push(indent);

        return INDENT;
    }else if(indent < indents[top]) {
        while(indent < indents[top] && top > 0) {
            top--;
            pending_dents++;
        }
        
        if(pending_dents > 1){
            unput(yytext[0]);
        }
        
        pending_dents--;
        
        return DEDENT;
    }else if(pending_dents >= 1){
        if(pending_dents > 1){
            unput(yytext[0]);
        }

        pending_dents--;
        
        return DEDENT;
    }else{
        return NEWLINE;
    }
}

<<EOF>> {
    if(pending_dents > 0){
        pending_dents--;
        unput(' ');

        return DEDENT;
    }

    if(indents[top] > 0){
        top--;
        unput(' ');

        return DEDENT;
    }

    return EOF;
}

[ \t]+ { /* Ignora espacos no meio da linha */ }
. { printf("UNKNOWN(%s)\n", yytext); }

%%

int yywrap(void){
    return 1;
}

int main(int argc, char **argv){
    indents[0] = 0;
    
    if(argc > 1){
        FILE *f = fopen(argv[1], "r");
        
        if(f) yyin = f;
    }

    return yyparse();
}