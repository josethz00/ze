run: quapa 
		./ze.out

quapa:
	gcc -Wall src/constants/tokens-constants.c src/constants/lexer-constants.c src/constants/keywords-constants.c src/core/lexer/lexer.c scripts/run/run.c scripts/shell/shell.c main.c -o ze.out

clean: 
	rm -rf *.out
