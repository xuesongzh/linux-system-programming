.PHONY: all clean
SRCS = $(wildcard *.c)
BIN  = wsh

all:$(BIN)
$(BIN):$(SRCS)
	gcc -Wall -o $@ $^
clean:
	rm -f $(BIN)
