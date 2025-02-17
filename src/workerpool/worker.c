#include <assert.h>
#include <pthread.h>
#include <stdio.h>

#include "fifo.h"
#include "job.h"
#include "worker.h"

int worker_start(Worker* worker) {
    assert(worker != NULL);

    // create thread with default attributes
    int ret = pthread_create(&worker->handler, NULL, worker->function,
                             (void*)&worker->argument);

    // check for errors
    if (ret < 0) {
        perror("pthread_create");
        return ret;
    }

    return 0;
}

int worker_init(Worker* worker, WorkerArgument argument) {
    assert(worker != NULL);

    // init thread function
    worker->function = worker_thread_function;

    // init argument
    worker->argument = argument;

    return 0;
}

int worker_destroy(Worker* worker) {
    assert(worker != NULL);

    // cancel running thread
    pthread_cancel(worker->handler);

    // we do not deallocate resources, because we only store
    // references, the ownership is not ours

    return 0;
}

WorkerArgument create_worker_argument(Fifo* job_queue, bool* should_quit,
                                      pthread_cond_t*  cond_var,
                                      pthread_mutex_t* mux) {
    WorkerArgument arg = {
        .should_quit = should_quit,
        .job_queue   = job_queue,
        .cond_var    = cond_var,
        .mux         = mux,
    };
    return arg;
}

void* worker_thread_function(void* arg) {
    WorkerArgument* params = (WorkerArgument*)arg;

    Job      job;
    uint32_t job_size = 0;
    pthread_mutex_lock(params->mux);
    while (1) {
        // cond wait on if job arrives, or should exit
        pthread_cond_wait(params->cond_var, params->mux);

        if (*params->should_quit) { break; }

        // else we have a new job.
        // get data from fifo
        int ret = fifo_pop(params->job_queue, &job, &job_size);
        // unlock mutex, we do not access shared resources anymore
        pthread_mutex_unlock(params->mux);
        if (ret != 0) {
            // handle error
            continue;
        }

        // process job
    }

    pthread_mutex_unlock(params->mux);
    pthread_exit(NULL);
}
