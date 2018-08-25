#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <time.h>

int get_line(char** str, int* size, FILE* f);

void get_time(struct tm* timeStamp);

#endif
