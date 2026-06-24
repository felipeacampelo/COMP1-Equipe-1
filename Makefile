TARGET = compiladorpj

all:
	bison -d parser/parser.y -o parser/parser.tab.c
	flex -o lexer/lex.yy.c lexer/lexer.l
	gcc parser/parser.tab.c lexer/lex.yy.c parser/ast.c parser/symtable.c -o $(TARGET) -lfl

# testes automatizados
test: all
	@echo "Executando testes..."
	@for t in tests/*.in; do \
		echo "---------------------------"; \
		echo "Testando $$t..."; \
		./$(TARGET) < $$t; \
		if [ -f compilador.tac ]; then \
			mv compilador.tac $${t%.in}.tac; \
			echo "Status: Sucesso ($${t%.in}.tac gerado)"; \
		else \
			echo "Status: Falha ao gerar TAC"; \
		fi; \
	done

clean:
	rm -f $(TARGET) parser/parser.tab.c parser/parser.tab.h lexer/lex.yy.c tests/*.tac compilador.tac