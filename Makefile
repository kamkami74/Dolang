CC = gcc 
CFLAGS = -g -Werror
sources := $(wildcard src/*.c)
objects := $(notdir $(sources:.c=.o))
exec := bin/main

##################################################

all: $(exec)

##################################################

%.o: src/%.c 
	$(CC) -c $< $(CFLAGS) -o $@

##################################################

bin/main: main.o io.o lexer.o token.o
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	rm -f *.o
	rm $(exec)
