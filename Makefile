CC = gcc 
CFLAGS = -g -Werror
sources := $(wildcard src/*.c)
objects := $(notdir $(sources:.c=.o))
exec :=  bin/do
test :=  bin/test_lexer bin/test_ast

##################################################

all: $(exec) $(test)

test: $(test)

##################################################

%.o: src/%.c 
	$(CC) -c $< $(CFLAGS) -o $@

##################################################

bin/test_lexer: test_lexer.o io.o lexer.o token.o
	$(CC) -o $@ $^ $(CFLAGS)

bin/test_ast: test_ast.o ast.o
	$(CC) -o $@ $^ $(CFLAGS)

bin/do: do.o syntax.o lexer.o token.o io.o
	$(CC) -o $@ $^ $(CFLAGS)


clean: 
	rm -f *.o
	rm $(exec)
