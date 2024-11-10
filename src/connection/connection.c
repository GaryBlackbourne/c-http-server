#include "connection.h"
#include <asm-generic/ioctls.h>
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int start_worker_thread(Connection* conn) {
    assert(conn != NULL);

    conn->running = 1;
    int pth_ret = pthread_create(&(conn->handler), NULL, worker_thread, conn);
    if (pth_ret != 0) {
        conn->running = 0;
        errno = pth_ret;
        perror("phtread_create");
        return -1;
    }

    return 0;
}

void* worker_thread(void* vp) {
    Connection* conn = (Connection*)vp;
    (void)conn;

    int all_received_bytes = 0;

    char request_string[MAX_REQUEST_SIZE] = {0};


    // read the status/request line
    // read lines (crlf) as long as there is an empty line
    // if content lenght was specified, read the body

    
    // legacy try:
    // recv string
    // use *buffer* to receive data in chunks.
    // This is a request, so for now, maximum request size is defined at 4 kb
    //                                    This should be configurable ---^^^^^
    // If the receive call fails, it means, that no response could be read from the
    // socket.
    while (1) {
        int chunk_received_bytes = 0;
        int buffer_len = RECEIVE_CHUNK_SIZE;
        char buffer [RECEIVE_CHUNK_SIZE] = {0};
        if ( (chunk_received_bytes = recv(conn->socket, buffer, buffer_len, 0)) < 0) {
            break;
        } else {
            all_received_bytes += chunk_received_bytes;
            if (all_received_bytes > 4095) {
                // todo server error
                pthread_exit(NULL);
            }
            memcpy(request_string - all_received_bytes, buffer, chunk_received_bytes);
        }
    }

    // process string
    // for the demo, the string will be the answer

    // send answer
    send(conn->socket, request_string, all_received_bytes, 0);

    pthread_exit(NULL);
}
