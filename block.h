#ifndef BLOCK_H
#define BLOCK_H

#include <time.h>
#include "err.h"

#define LOAD_MAX 1

typedef struct {
    time_t timestamp;
    char* data;
} Load;

typedef struct {
    unsigned long prevHash;
    unsigned long hash;
    time_t timestamp;
    Load** l;
} Block;

typedef struct {
    int index;
    Block** blocks;
} Chain;

Err init_chain(Chain* c);

#endif
