%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../parser/parser.tab.h" 

int indents[100];
int top = 0;
int pending_dents = 0;

void push(int n){
    top++;
    indents[top] = n;
}

%}

%%

"print"     { 
   // printf("PRINT(%s)\n", yytext);
    return PRINT; 
}

"if"        { 
   // printf("IF(%s)\n", yytext);
    return IF; 
}

"else"      { 
   // printf("ELSE(%s)\n", yytext);
    return ELSE; 
}

"while"     { 
    //printf("WHILE(%s)\n", yytext);
    return WHILE; 
}

"for"       {
    //printf("FOR(%s)\n", yytext);
    return FOR;
}

"import"    {
    //printf("IMPORT(%s)\n", yytext);
    return IMPORT;
}

"as"        {
    //printf("AS(%s)\n", yytext);
    return AS;
}

"from"      {
    //printf("FROM(%s)\n", yytext);
    return FROM;
}

"input"     {
    //printf("INPUT(%s)\n", yytext);
    return INPUT;
}

"int"       {
   // printf("INT(%s)\n", yytext);
    return INT;
}

"double"    {
   // printf("DOUBLE(%s)\n", yytext);
    return DOUBLE;
}

"float"     {
   // printf("FLOAT(%s)\n", yytext);
    return FLOAT;
}

"complex"   {
   // printf("COMPLEX(%s)\n", yytext);
    return COMPLEX;
}

"!"         {
   // printf("NOT(%s)\n", yytext);
    return NOT;
}

">"         { 
   // printf("MT(%s)\n", yytext);
    return MT;
}

"<"         { 
   // printf("LT(%s)\n", yytext);
    return LT; 
}

"#".*      { /* Ignorar comentário de linha */ }

"/*"([^*]|\*+[^*/])*\*+\/    { /* Ignorar comentários de bloco */ }

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.id = strdup(yytext); 
   // printf("ID(%s)\n", yytext);
    return ID; 
}

[0-9]+\.[0-9]+      {
    yylval.floatValue = atof(yytext);
   // printf("FLOAT_NUM(%s)\n", yytext);
    return FLOAT_NUM;
}

[0-9]+      { 
    yylval.intValue = atoi(yytext); 
   // printf("NUM(%s)\n", yytext);
    return NUM;
}

"++"        {
   // printf("INCREMENT(%s)\n", yytext);
    return INCREMENT;
}

"+="        {
   // printf("PLUS_ATRIBUTION(%s)\n", yytext);
    return PLUS_ATRIBUTION;
}

"+"         { 
   // printf("PLUS(%s)\n", yytext);
    return PLUS; 
}

"-="        {
   // printf("MINUS_ATRIBUTION(%s)\n", yytext);
    return MINUS_ATRIBUTION;
}

"-"         { 
   // printf("MINUS(%s)\n", yytext);
    return MINUS; 
}

"*="        {
   // printf("TIMES_ATRIBUTION(%s)\n", yytext);
    return TIMES_ATRIBUTION;
}

"*"         { 
   // printf("TIMES(%s)\n", yytext);
    return TIMES; 
}

"//="       {
   // printf("INT_DIV_ATRIBUTION(%s)\n", yytext);
    return INT_DIV_ATRIBUTION;
}

"/="        {
   // printf("DIV_ATRIBUTION(%s)\n", yytext);
    return DIV_ATRIBUTION;
}

"//"        {
   // printf("INT_DIV(%s)\n", yytext);
    return INT_DIV;
}

"/"         { 
   // printf("DIV(%s)\n", yytext);
    return DIV; 
}

"=="        { 
   // printf("EQ(%s)\n", yytext);
    return EQ; 
}

"!="        {
   // printf("DIFF(%s)\n", yytext);
    return DIFF;
}

"="         { 
    // printf("ASSING(%s)\n", yytext);
    return ASSIGN; 
}

"("         { 
   // printf("LPAREN(%s)\n", yytext);
    return LPAREN; 
}

")"         { 
   // printf("RPAREN(%s)\n", yytext);
    return RPAREN; 
}

":"         {
   // printf("COLON(%s)\n", yytext);
    return COLON;
}

\r?\n[ \t]* { 
    int indent = (yyleng-1) / 4;
    if (yytext[0] == '\r') indent = (yyleng-2) / 4;
    if(indent > indents[top]) {
        push(indent);
        return INDENT;
    }
    else if(indent < indents[top]) {
        while(indent < indents[top] && top > 0) {
            top--;
            pending_dents++;
        }
        if(pending_dents > 1){
            unput(yytext[0]);
        }
        pending_dents--;
        return DEDENT;
    }
    else if(pending_dents >= 1){
        if(pending_dents > 1){
            unput(yytext[0]);
        }
        pending_dents--;
        return DEDENT;
    }
    else{
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

[ \t]+      { /* Ignora espacos no meio da linha */ }
.           { printf("UNKNOWN(%s)\n", yytext); }

%%

int yywrap(void) {
    return 1;
}

int main(void) {
    return yyparse();
}