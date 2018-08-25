#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "node.h"
#include "err.h"
#include "block.h"
#include "common.h"

unsigned long hash_user(char* name, char* pubKey, char* privKey) {
    unsigned long hash = 5381;
    int c; 
    char str[MAX_BUFF] = ""; 
    strcpy(str, name);
    strcat(strcat(str, privKey), pubKey);

    int i = 0;
    while((c = str[i++])) {
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
    u->hash = hash_user(u->name, pubKey, privKey);

#ifdef TEST
    printf("received: name=\"%s\", pubkey=%lu, privkey=%lu\nhash=%lu\n", 
            u->name, u->pubKey, u->privKey, u->hash);
#endif

    return e;
}

Err get_input(User* u, Chain* c) {
    Err e = OK;
    char* str = NULL;
    int len;
    while(e == OK) {
        for(int i = 0; i < LOAD_MAX; i++) {
            printf("enter message\n");
            get_line(&str, &len, stdin);
            if(str == NULL || strcmp(str, "q") == 0) {
                // cancel message, destoy load?
                return OK;
            } else if(strcmp(str, "print") == 0) {
                printf("print the block\n");
            }
            
            e = save_msg(c, str);
            if(e != OK) {
                return e;
            }
        }
    }
    free(str);
    return OK;
}

int main(int argc, char** argv) {
    Err e = OK;
    User u;
    e = init_user(&u, argv[1], argv[2], argv[3]);
    if(e != OK) {
        err_msg(e, stderr);
        return e;
    }
    Chain c;
    e = init_chain(&c);

    e = get_input(&u, &c);
    
    return e;
}
