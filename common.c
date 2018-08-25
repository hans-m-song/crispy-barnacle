#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "common.h"

int get_line(char** str, int* size, FILE* f) {
    char line[256];
    char* ptr;
    int len;
    if(str == NULL || size == NULL) {
        return -1;
    }

    if(feof(f)) {
        return -1;
    }

    fgets(line, 256, f);

    ptr = strchr(line, '\n');
    if(ptr) {
        *ptr = '\0';
    }

    len = strlen(line);

    if((len + 1) < 256) {
        ptr = realloc(*str, 256);
        if(ptr == NULL) {
            return -1;
        }
        *str = ptr;
        *size = 256;
    }

    strcpy(*str, line);
    return len;
}

void get_time(struct tm* timeStamp) {
    time_t rawTime;
    time(&rawTime);
    timeStamp = localtime(&rawTime);
}
