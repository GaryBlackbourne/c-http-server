#include <errno.h>
#include <assert.h>
#include <pthread.h>

#include "configuration.h"
#include "job-queue.h"
#include "fifo.h"
#include "job.h"

int job_queue_init(JobQueue* job_queue, const Configuration* config) {
    assert(job_queue != NULL);
    assert(config != NULL);

    /*
     * Try to initialize all parts. If any of them fails,
     * destroy the previously created objects.
     */

    if (fifo_init(&job_queue->fifo, config->job_queue_length) != 0) {
        goto fifo_fail;
    }
    if (pthread_mutex_init(&job_queue->fifo_lock, NULL) != 0) {
        goto fifo_mux_fail;
    }
    if (pthread_cond_init(&job_queue->new_job_cond_v, NULL) != 0) {
        goto cond_var_fail;
    }
    if (pthread_mutex_init(&job_queue->new_job_cond_mux, NULL) != 0) {
        goto cond_var_mux_fail;
    }

    return 0;

cond_var_mux_fail:
    pthread_cond_destroy(&job_queue->new_job_cond_v);
cond_var_fail:
    pthread_mutex_destroy(&job_queue->fifo_lock);
fifo_mux_fail:
    fifo_destroy(&job_queue->fifo);
fifo_fail:
    return -1;
}

int job_queue_push(JobQueue* job_queue, Job job) {
    assert(job_queue != NULL);

    pthread_mutex_lock(&job_queue->fifo_lock);
    int fifo_ret = fifo_push(&job_queue->fifo, &job, sizeof(Job));
    pthread_mutex_unlock(&job_queue->fifo_lock);
    if (fifo_ret != 0) {
        return -1;
    }

    // TODO signaling

    return -1;
}

int job_queue_pop(JobQueue* job_queue, Job* job) {
    assert(job_queue != NULL);
    assert(job_queue != NULL);

    pthread_mutex_lock(&job_queue->fifo_lock);
    int fifo_ret = fifo_pop(&job_queue->fifo, &job, NULL);
    pthread_mutex_unlock(&job_queue->fifo_lock);
    if (fifo_ret != 0) {
        return -1;
    }

    // TODO signaling

    return 0;
}
