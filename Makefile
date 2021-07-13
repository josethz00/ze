run: quapa 
		./quapa.out

quapa:
	gcc src/constants/tokens-constants.c src/core/lexer/lexer.c src/core/parser/parser.c 
	scripts/run/run.c scripts/shell/shell.c main.c -o quapa.out

clean: 
	rm -rf *.out
