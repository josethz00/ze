exec = ze.out
sources = $(wildcard src/**/*.c) $(wildcard src/**/**/*.c) $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic

run: quapa 
		./$(exec)

quapa:
	gcc $(flags) $(sources) -o $(exec)

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o
	-rm src/**/*.o