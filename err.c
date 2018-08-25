#include <stdio.h>
#include "err.h"

void err_msg(Err e, FILE* f) {
    char* str = (char*)malloc(sizeof(char) * 70);
    switch(e) {
        case OK:
            free(str);
            return;
        case E_HASHMISMATCH:
            str = "hash mismatch"
            break;
        case E_TIMESTAMPMISMATCH:
            str = "timestamp mismatch"
            break;
        case E_BADPAYLOAD:
            str = "bad payload received"
            break;
        default:
            str = "unknown error"
            break;
    }
    fprintf(f, str);
    fflush(f);
}
