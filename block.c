#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "err.h"
#include "block.h"
#include "common.h"

unsigned long hash_block(Block* b) {
    unsigned long hash = 5381;
    
    return hash;
}

void destroy_block(Block* b) {
    for(int i = 0; i < LOAD_MAX; i++) {
        free(b->l[i]->data);
        free(b->l[i]);
    }
    free(b->l);
}

void destroy_chain(Chain* c) {
    for(int i = 0; i < c->index + 1; i++) {
        destroy_block(c->blocks[i]);
    }
}

Err init_load(Block* b) {
    b->l = (Load**)malloc(sizeof(Load*) * LOAD_MAX);
    if(!b->l) {
        return E_MEMALLOC;
    }

    for(int i = 0; i < LOAD_MAX; i++) {
        b->l[i] = (Load*)malloc(sizeof(Load));
        if(!b->l[i]) {
            return E_MEMALLOC;
        }
    }

    return OK;
}

Err init_block(Chain* c, int index) {
    c->blocks[c->index] = (Block*)malloc(sizeof(Block));
    if(!c->blocks[c->index]) {
        return E_MEMALLOC;
    }
    
    c->blocks[c->index]->loadCount = 0;
    Err e = init_load(c->blocks[c->index]);

    return e;
}

Err genesis_block(Block* b) {
    b->prevHash = 0;
    get_time(b->timeStamp);

    if(init_load(b) != OK) {
        return E_MEMALLOC;
    }

    get_time(b->l[0]->timeStamp);
    b->l[0]->data = "hello world";
    b->loadCount++;

    return OK;
}

Err init_chain(Chain* c) {
    Err e = OK;

    c->index = 0;
    c->blocks = (Block**)malloc(sizeof(Block*));
    if(!c->blocks) {
        return E_MEMALLOC;
    }
    
    c->blocks[0] = (Block*)malloc(sizeof(Block));
    if(!c->blocks[0]) {
        return E_MEMALLOC;
    }

    e = genesis_block(c->blocks[0]);

    return e;
}

Err save_msg(Chain* c, char* msg) {
    if(c->blocks[c->index]->loadCount == LOAD_MAX) {
#ifdef TEST
        printf("block size exceeded, generating new block\n");
#endif
        init_block(c, ++c->index);
    }

    int loadCount = c->blocks[c->index]->loadCount;
    get_time(c->blocks[c->index]->l[loadCount]->timeStamp);
    c->blocks[c->index]->l[loadCount]->data = (char*)malloc(sizeof(char)*strlen(msg) + 1);
    if(!c->blocks[c->index]->l[loadCount]->data) {
        return E_MEMALLOC;
    }
    strcpy(c->blocks[c->index]->l[loadCount]->data, msg);
    c->blocks[c->index]->loadCount++;

    return OK;
}

void print_block(Block* b) {
    char buffer[26];
    strftime(buffer, 26, "%Y-%m-%d-%H-%M-%S", b->timeStamp), 
    printf("Block: %s\n", buffer);
    for(int i = 0; i < b->loadCount; i++) {
        strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", b->l[i]->timeStamp);
        printf("%s|%s\n", buffer, b->l[i]->data);
    }
}
