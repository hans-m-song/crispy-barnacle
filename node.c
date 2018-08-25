#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "err.h"

unsigned long hash(char* name, char* pubKey, char* privKey) {
    unsigned long hash = 5381;
    int c;
    char* str = (char*)malloc(sizeof(char) * (strlen(name) + strlen(pubKey) + strlen(privKey)));
    strcpy(str, name);
    strcat(str, pubKey);
    strcat(str, privKey);

    while(c = *str++) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

Err init_user(User *u, char* name, char* pubKey, char* privKey) {
    Err e = OK;
    char* end;
    u->name = name;
    u->pubKey = strtoul(pubKey, &end, 10);
    u->privKey = strtoul(privKey, &end, 10);
    u->hash = hash(u->name, pubKey, privKey);

#ifdef TEST
    printf("received: name=\"%s\", pubkey=%lu, privkey=%lu\nhash=%lu", u->name, u->pubKey, u->privKey, u->hash);
#endif

    return e;
}

Err init_chain(Chain* c);

int main(int argc, char** argv) {
    Err e = OK;
    User u;
    e = init_user(&u, argv[1], argv[2], argv[3]);
    if(e != OK) {
        err_msg(stderr, e);
        return e;
    }
    Chain c;
    
    return e;
}
