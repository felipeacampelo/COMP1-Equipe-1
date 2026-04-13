%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../parser/parser.tab.h" 
%}

%%

"print"     { 
    printf("PRINT(%s)\n", yytext);
    return PRINT; 
}

"if"        { 
    printf("IF(%s)\n", yytext);
    return IF; 
}

"else"      { 
    printf("ELSE(%s)\n", yytext);
    return ELSE; 
}

"while"     { 
    printf("WHILE(%s)\n", yytext);
    return WHILE; 
}

"=="        { 
    printf("EQ(%s)\n", yytext);
    return EQ; 
}

">"         { 
    printf("MT(%s)\n", yytext);
    return MT;
}

"<"         { 
    printf("LT(%s)\n", yytext);
    return LT; 
}
"//".*      { /* Ignorar comentário de linha */ }

"/*"([^*]|\*+[^*/])*\*+\/    { /* Ignorar comentários de bloco */ }

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.id = strdup(yytext); 
    printf("ID(%s)\n", yytext);
    return ID; 
}

[0-9]+(\.[0-9]+)? { 
    yylval.intValue = atoi(yytext); 
    printf("NUM(%s)\n", yytext);
    return NUM; 
}

"="         { 
    printf("ASSING(%s)\n", yytext);
    return ASSIGN; 
}

"+"         { 
    printf("PLUS(%s)\n", yytext);
    return PLUS; 
}

"-"         { 
    printf("MINUS(%s)\n", yytext);
    return MINUS; 
}

"*"         { 
    printf("TIMES(%s)\n", yytext);
    return TIMES; 
}

"/"         { 
    printf("DIV(%s)\n", yytext);
    return DIV; 
}

"("         { 
    printf("LPAREN(%s)\n", yytext);
    return LPAREN; 
}

")"         { 
    printf("RPAREN(%s)\n", yytext);
    return RPAREN; 
}

[ \t]+      { /* Ignorar espaços e pulos de linha */ }

\n          { 
    printf("NLINE\n");
    return '\n'; 
}

.           { printf("UNKNOWN(%s)\n", yytext); }

%%

int yywrap(void) {
    return 1;
}

int main(void) {
    return yyparse();
}