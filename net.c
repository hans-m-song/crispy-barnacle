#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "err.h"
#include "net.h"

Err auth(FILE* in, unsigned long pubKey, unsigned long privKey) {
    return OK;
}

int get_port(int fd) {
    struct sockaddr_in s;
    socklen_t l = sizeof(s);
    
    if(getsockname(fd, (struct sockaddr*)&s, &l) < 0) {
        return E_GETPORT;
    }

    return ntohs(s.sin_port);
}

int open_port(int port) {
    int fd, opt_val;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    fd = socket(AF_INET, SOCK_STREAM, 0);
    opt_val = 1;
    if(fd < 0 || setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(int)) < 0) {
#ifdef TEST
        printf("setsockopt\n");
#endif
        return E_OPENPORT;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = 0;
    if(port) {
        addr.sin_port = htons(port);
    }

    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(fd, (struct sockaddr*)&addr, addr_len) < 0) {
#ifdef TEST
        printf("bind\n");
#endif
        return E_OPENPORT;
    }

    if((!port) && getsockname(fd, (struct sockaddr*)&addr, &addr_len) < 0) {
#ifdef TEST
        printf("getsockname\n");
#endif
        return E_OPENPORT;
    }

    if(listen(fd, SOMAXCONN) < 0) {
#ifdef TEST
        printf("listen\n");
#endif
        return E_OPENPORT;
    }

#ifdef TEST
        printf("got port:%d\n", ntohs(addr.sin_port));
#endif

        return fd;

}

int connect_to(int port) {
    int fd;
    struct sockaddr_in dest;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) {
#ifdef TEST
        printf("socket\n");
#endif
        return E_CONNECTTO;
    }

    dest.sin_family = AF_INET;
    dest.sin_port = 0;
    if(port) {
        dest.sin_port = htons(port);
    }
    dest.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // need to change this
    if(connect(fd, (struct sockaddr*)&dest, sizeof(struct sockaddr_in)) < 0) {
#ifdef TEST
        printf("connect\n");
#endif
        return E_CONNECTTO;
    }

    return fd;
}
