#include <errno.h>
#include <assert.h>
#include <pthread.h>

#include "job-queue.h"
#include "fifo.h"

int job_queue_init(JobQueue* job_queue) {
    assert(job_queue != NULL);

    /*
     * Try to initialize all parts. If any of them fails,
     * destroy the previously created objects.
     */ 

    // init fifo, and lock
    if (init_fifo(&job_queue->fifo, 10) != 0){ // <<<<< TODO -> job queue length !
        goto fifo_fail;
    }
    if (pthread_mutex_init(&job_queue->fifo_lock, NULL)) {
        goto fifo_mux_fail;
    }
    // init cond var
    if (pthread_cond_init(&job_queue->new_job_cond_v, NULL)){
        goto cond_var_fail;
    }
    if (pthread_mutex_init(&job_queue->new_job_cond_mux, NULL)) {
        goto cond_var_mux_fail;
    }

    return 0;

 cond_var_mux_fail:
    pthread_cond_destroy(&job_queue->new_job_cond_v);
 cond_var_fail:
     pthread_mutex_destroy(&job_queue->fifo_lock);
 fifo_mux_fail:
     destroy_fifo(&job_queue->fifo);
 fifo_fail:
    return -1;
}
