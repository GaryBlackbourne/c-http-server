#ifndef _BALU_WORKER_H
#define _BALU_WORKER_H

void worker(void* vp);

/*
typedef struct {
    uint8_t running;
    pthread_t handler;
    int socket;
    struct sockaddr_in client_address;
    socklen_t client_address_len;
} Connection;

void* worker_thread(void* vp);

int start_worker_thread(Connection* conn);

#define RECEIVE_CHUNK_SIZE 512
#define MAX_REQUEST_SIZE   4096
*/

#endif
