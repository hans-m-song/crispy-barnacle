CC = gc
BUILD := release
flags.test := -DTEST -std=c99 -Wall -pedantic -g
flags.verbose := -DVERBOSE -DTEST -std=c99 -Wall -pedantic -g
flags.release := -std=c99 -Wall -pedantic
FLAGS := ${flags.${BUILD}}
OBJ = core.o init.o err.o

.PHONY: all

all: bc8h1b
        @echo BUILD=${BUILD}

blockchain-alpha: $(OBJ)
        $(CC) $(FLAGS) $(OBJ) -o blockchain-alpha

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -f blockcain-alpha *.o
