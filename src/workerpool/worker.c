#include <assert.h>
#include <pthread.h>

#include "worker.h"
#include "fifo.h"

int worker_start(Worker* worker) {
    assert(worker != NULL);
    worker->function(NULL);
}

int worker_init(Worker* worker, const Fifo* job_queue) {
    assert(worker != NULL);
    assert(job_queue != NULL);

    // init pthread handler

    // init thread function
    worker->function = worker_thread_function;

    worker->thread_argument.job_queue = job_queue;

    return 0;
}

int worker_destroy(Worker* worker) {
    
}
