#ifndef ERR_H
#define ERR_H

typedef enum {
    OK,
    ACK,
    NACK
} Com;

typedef enum {
    OK,
    E_HASHMISMATCH,
    E_TIMESTAMPMISMATCH,
    E_BADPAYLOAD
} Err;
