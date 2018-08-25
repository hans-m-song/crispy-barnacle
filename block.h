#ifndef BLOCK_H
#define BLOCK_H

#include <time.h>
#include "err.h"

#define LOAD_MAX 2

typedef struct {
    struct tm* timeStamp;
    char* data;
} Load;

typedef struct {
    unsigned long prevHash;
    unsigned long hash;
    struct tm* timeStamp;
    Load** l;
    int loadCount;
} Block;

typedef struct {
    int index;
    Block** blocks;
} Chain;

Err init_chain(Chain* c);

void destroy_chain(Chain* c);

Err save_msg(Chain* c, char* msg);

void print_block(Block* b);

#endif
