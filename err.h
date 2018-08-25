#ifndef ERR_H
#define ERR_H

typedef enum {
    ACK,
    NACK
} Com;

typedef enum {
    OK,
    E_HASHMISMATCH,
    E_TIMESTAMPMISMATCH,
    E_BADPAYLOAD,
    E_GETPORT,
    E_OPENPORT,
    E_CONNECTTO,
    E_MEMALLOC
} Err;

void err_msg(Err e, FILE* f);

#endif
