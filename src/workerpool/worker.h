#ifndef _BALU_WORKER_H
#define _BALU_WORKER_H

#include <stdint.h>
#include <pthread.h>

#include "connection.h"
#include "fifo.h"

typedef struct {
    pthread_t handler;
    void (*function) (void* vp);
} Worker;

int worker_init(Worker* worker, const Fifo* job_queue);

int worker_destroy(Worker* worker);

int worker_start(Worker* worker);

void worker_thread_function(void* arg/*Fifo of Jobs*/);

#endif
