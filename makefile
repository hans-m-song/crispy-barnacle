CC = gcc
BUILD := test
flags.test := -DTEST -std=c99 -Wall -pedantic -g
flags.verbose := -DVERBOSE -DTEST -std=c99 -Wall -pedantic -g
flags.release := -std=c99 -Wall -pedantic
FLAGS := $(flags.$(BUILD))
OBJ = err.o net.o block.o
NODE = node.o $(OBJ)
server = server.o $(OBJ)

.PHONY: all

all: node 
	@echo BUILD=$(BUILD)

node: $(NODE)
	$(CC) $(FLAGS) $(OBJ) node.o -o node

server: $(SERVER)
	$(CC) $(FLAGS) $(OBJ) server.o -o server

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -f node server *.o
