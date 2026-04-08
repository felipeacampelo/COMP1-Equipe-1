%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../parser/parser.tab.h" 
%}

%%

"print"     { return PRINT; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"=="        { return EQ; }
">"         { return MT; }
"<"         { return LT; }
"//".*      { /* Ignorar comentário de linha */ }
"/*"([^*]|\*+[^*/])*\*+\/    { /* Ignorar comentários de bloco */ }

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.id = strdup(yytext); 
    return ID; 
}

[0-9]+(\.[0-9]+)? { 
    yylval.intValue = atoi(yytext); 
    return NUM; 
}

"="         { return ASSIGN; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return TIMES; }
"/"         { return DIV; }
"("         { return LPAREN; }
")"         { return RPAREN; }

[ \t\n]+    { /* Ignorar espaços e pulos de linha */ }

.           { printf("UNKNOWN(%s)\n", yytext); }

%%

int yywrap(void) {
    return 1;
}

int main(void) {
    return yyparse();
}