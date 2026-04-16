# Nome do executável final
TARGET = compiladorpj

all:
 #Gera o arquivo do bison
	bison -d parser/parser.y -o parser/parser.tab.c

 #Gera o arquivo flex
	flex -o lexer/lex.yy.c lexer/lexer.l

 #Isso aqui é para compilar os dois arqvuios para criar o executavel
	gcc parser/parser.tab.c lexer/lex.yy.c parser/ast.c -o $(TARGET) -lfl

# Comando para limpar os arquivos gerados
clean:
	rm -f $(TARGET) parser/parser.tab.c parser/parser.tab.h lexer/lex.yy.c