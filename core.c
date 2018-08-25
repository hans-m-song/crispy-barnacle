#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"

unsigned long hash(char* name, int pubKey, int privKey) {
    unsigned long hash = 5381;
    int c;
    char* str = (char*)malloc((sizeof(char) * strlen(name)) + (sizeof(int) * 2));
    strcpy(str, name);
    strcat(str, itoa(pubKey));
    strcat(str, itoa(privKey));

    while(c = *str++) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

Err init_user(User *u, char** argv) {
    Err e = OK;
    u->name = argv[1];
    u->hash = hash(name, pubKey, privKey);

    return e;
}

Err init_chain(chain* c);

int main(int argc, char** argv) {
    Err e = OK;
    User u;
    Chain c;
    
}
