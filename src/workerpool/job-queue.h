#ifndef BALU_JOB_QUEUE_HPP
#define BALU_JOB_QUEUE_HPP

#include "fifo.h"
#include <pthread.h>

/**
 * @brief Job Queue struct which manages a fifo of jobs.
 *
 * This struct manages a fifo, which hold jobs. The instance is responsible for
 * keeping the fifo thread safe, and maintaining a conditional variable which
 * can be waited upon, and signals new jobs. For this, manually handling
 * internal data of this struct is strictly FORBIDDEN! Jobs can be pushed, or
 * popped with job_queue_push() and job_queue_pop() calls only.
 */
typedef struct {
    Fifo fifo;                        // fifo containing jobs
    pthread_mutex_t fifo_lock;        // mutex for fifo operations

    pthread_cond_t new_job_cond_v;    // conditional variable signailng new job
    pthread_mutex_t new_job_cond_mux; // mutex for the conditional variable
}JobQueue;

int job_queue_init(JobQueue* job_queue);

int job_queue_push(JobQueue* job_queue);

int job_queue_pop(JobQueue* job_queue);



#endif /* BALU_JOB_QUEUE */
