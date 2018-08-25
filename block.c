#include <stdio.h>
#include <stdlib.h>
#include "err.h"
#include "block.h"

unsigned long hash_block(Block* b);

void destroy_block(Block* b) {
    for(int i = 0; i < LOAD_MAX; i++) {
        free(b->l[i]->data);
        free(b->l[i]);
    }
    free(b->l);
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

Err genesis_block(Block* b) {
    b = (Block*)malloc(sizeof(Block));
    if(!b) {
        return E_MEMALLOC;
    }
    b->prevHash = 0;
    b->timestamp = 0;
    if(init_load(b) != OK) {
        return E_MEMALLOC;
    }
    b->l[0]->timestamp = 0;
    b->l[0]->data = "hello world";
    return OK;
}

Err init_chain(Chain* c) {
    Err e = OK;

    c->index = 0;
    c->blocks = (Block**)malloc(sizeof(Block*) * 2);
    if(!c->blocks) {
        return E_MEMALLOC;
    }
    
    e = genesis_block(c->blocks[0]);

    return e;
}

