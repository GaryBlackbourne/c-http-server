#ifndef _BALU_WORKERPOOL_H
#define _BALU_WORKERPOOL_H

#include <stdint.h>
#include "configuration.h"

#include "worker.h"
#include "fifo.h"

typedef struct {
    Worker*     pool;
    uint16_t    pool_size;
    const Fifo* job_queue;
} Workerpool;

int workerpool_init(Workerpool* workerpool, const Fifo* job_queue, const Configuration* config);

int workerpool_start(Workerpool* workerpool);

int workerpool_stop(Workerpool* workerpool);

int workerpool_destroy(Workerpool* workerpool);

#endif
