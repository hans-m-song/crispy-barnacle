#ifndef NODE_H
#define NODE_H

#include <time.h>

#define MAX_BUFF 90

typedef struct {
    char* name;
    unsigned long hash;
    unsigned long pubKey;
    unsigned long privKey;
} User;

#endif
