#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "err.h"
#include "block.h"

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
    
    Err e = init_load(c->blocks[c->index]);

    return OK;
}

Err genesis_block(Block* b) {
    b->prevHash = 0;
    b->timestamp = 0;

    if(init_load(b) != OK) {
        return E_MEMALLOC;
    }

    b->l[0]->timestamp = 0;
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
        init_block(c, ++c->index);
    }
    int loadCount = c->blocks[c->index]->loadCount;
    c->blocks[c->index]->l[loadCount]->timestamp = time(NULL);
    c->blocks[c->index]->l[loadCount]->data = (char*)malloc(sizeof(char)*strlen(msg) + 1);
    if(!c->blocks[c->index]->l[loadCount]->data) {
        return E_MEMALLOC;
    }
    strcpy(c->blocks[c->index]->l[loadCount]->data, msg);
    c->blocks[c->index]->loadCount++;

    return OK;
}

void print_block(Chain* c);
