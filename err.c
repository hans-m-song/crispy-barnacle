#include <stdio.h>
#include <stdlib.h>
#include "err.h"

void err_msg(Err e, FILE* f) {
    char* str = (char*)malloc(sizeof(char) * 70);
    switch(e) {
        case OK:
            free(str);
            return;
        case E_HASHMISMATCH:
            str = "hash mismatch";
            break;
        case E_TIMESTAMPMISMATCH:
            str = "timestamp mismatch";
            break;
        case E_BADPAYLOAD:
            str = "bad payload received";
            break;
        case E_GETPORT:
            str = "error when getting port";
            break;
        case E_OPENPORT:
            str = "error when openning port";
            break;
        case E_CONNECTTO:
            str = "error connecting to port";
            break;
        default:
            str = "unknown error";
            break;
    }
    fprintf(f, "%s\n", str);
    fflush(f);
}
