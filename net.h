#ifndef NET_H
#define NET_H

#include <stdlib.h>

Err auth(FILE* in, unsigned long pubKey, unsigned long privKey);

int get_port(int fd);

int open_port(int port);

int connect_to(int port);

#endif
