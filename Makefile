TARGET = compiladorpj

all:
	bison -d parser/parser.y -o parser/parser.tab.c

	flex -o lexer/lex.yy.c lexer/lexer.l

	gcc parser/parser.tab.c lexer/lex.yy.c parser/ast.c parser/symtable.c -o $(TARGET) -lfl

clean:
	rm -f $(TARGET) parser/parser.tab.c parser/parser.tab.h lexer/lex.yy.c