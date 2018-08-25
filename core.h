#ifndef CORE_H
#define CORE_H

#include <time.h>

typedef struct {
    char* name;
    unsigned long hash;
    int pubKey;
    int privKey;
} User;

typedef struct {
    int index;
    unsigned long prevHash;
    unsigned long hash;
    time_t timestamp;
    char** payload;
} Block;

typedef struct {
    int index;
    Block* blocks
} Chain;

#endif
