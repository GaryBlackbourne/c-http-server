#ifndef _BALU_WORKERPOOL_H
#define _BALU_WORKERPOOL_H

#include <bits/pthreadtypes.h>
#include <stdint.h>
#include "configuration.h"

#include "worker.h"
#include "fifo.h"

typedef struct {
    Worker*     pool;
    uint16_t    pool_size;
    Fifo* job_queue;
    pthread_mutex_t mux;
    pthread_cond_t cond_var;
    bool threads_should_quit;
} Workerpool;

int workerpool_init(Workerpool* workerpool, Fifo* job_queue, const Configuration* config);

int workerpool_start(Workerpool* workerpool);

int workerpool_stop(Workerpool* workerpool);

int workerpool_destroy(Workerpool* workerpool);

#endif
