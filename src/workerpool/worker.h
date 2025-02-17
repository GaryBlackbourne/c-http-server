#ifndef _BALU_WORKER_H
#define _BALU_WORKER_H

#include <bits/pthreadtypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

#include "fifo.h"

typedef struct {
    Fifo*     job_queue;
    bool*           should_quit;
    pthread_cond_t* cond_var;
    pthread_mutex_t* mux;
} WorkerArgument;

WorkerArgument create_worker_argument(Fifo* job_queue, bool* should_quit, pthread_cond_t* cond_var, pthread_mutex_t* mux);

typedef struct {
    pthread_t handler;
    void* (*function)(void* vp);
    WorkerArgument argument;
} Worker;

int worker_init(Worker* worker, WorkerArgument argument);

int worker_destroy(Worker* worker);

int worker_start(Worker* worker);

void* worker_thread_function(void* arg /*Fifo of Jobs*/);

#endif
