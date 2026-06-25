TARGET = compiladorpj

all:
	bison -d parser/parser.y -o parser/parser.tab.c
	flex -o lexer/lex.yy.c lexer/lexer.l
	gcc parser/parser.tab.c lexer/lex.yy.c parser/ast.c parser/symtable.c java_gen.c -o $(TARGET) -lfl

# testes automatizados
test: all
	@echo "Executando testes (Python -> Java)..."
	@for t in tests/*.in; do \
		echo "---------------------------"; \
		echo "Testando $$t..."; \
		./$(TARGET) < $$t; \
		if [ -f Main.java ]; then \
			mv Main.java $${t%.in}.java; \
			echo "Status: Sucesso ($${t%.in}.java gerado)"; \
		else \
			echo "Status: Falha ao gerar Java"; \
		fi; \
	done

clean:
	rm -f $(TARGET) parser/parser.tab.c parser/parser.tab.h lexer/lex.yy.c tests/*.java Ma
