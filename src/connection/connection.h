#ifndef _BALU_CONNECTION_H
#define _BALU_CONNECTION_H

#include <stdint.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct {
    uint8_t running;
    pthread_t handler;
    int socket;
    struct sockaddr_in client_address;
    socklen_t client_address_len;
} Connection;

void* worker_thread(void* vp);

int start_worker_thread(Connection* conn);

#endif
