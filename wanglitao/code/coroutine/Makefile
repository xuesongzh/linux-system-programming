.PHONY: all clean

CC = gcc

all: a.out
a.out: main.c ctx.c ctx.h
	$(CC) -o $@ $^

clean:
	rm -rf a.out
