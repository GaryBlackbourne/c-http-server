#ifndef _BALU_WORKER_H
#define _BALU_WORKER_H

#include <stdint.h>
#include <pthread.h>
#include "connection.h"

typedef struct {
    pthread_t handler;
    void (*worker_function) (void* vp);
    Connection connection;
} Worker;

int worker_init(Worker* worker);

int worker_destroy(Worker* worker);

#endif
