#include "connection.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>

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
    // start something

    // recv string

    // process string

    // send answer

    pthread_exit(NULL);
}
