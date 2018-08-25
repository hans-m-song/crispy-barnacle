CC = gcc
BUILD := test
flags.test := -DTEST -std=c99 -Wall -pedantic -g
flags.verbose := -DVERBOSE -DTEST -std=c99 -Wall -pedantic -g
<<<<<<< HEAD
flags.test := -std=c99 -Wall -pedantic
FLAGS := $(flags.$(BUILD))
OBJ = err.o net.o
NODE = node.o $(OBJ)
server = server.o $(OBJ)
=======
flags.release := -std=c99 -Wall -pedantic
FLAGS := ${flags.${BUILD}}
OBJ = core.o init.o err.o
>>>>>>> 79ad4b56559f4b1eb6b94ab40670b417b0638090

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
