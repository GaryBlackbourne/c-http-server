#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

#include "workerpool.h"
#include "worker.h"
#include "fifo.h"

int workerpool_init(Workerpool* workerpool, Fifo* job_queue,
                    const Configuration* config) {
    assert(workerpool != NULL);
    assert(config != NULL);

    workerpool->pool_size = config->worker_pool_lize;
    workerpool->pool = (Worker*)malloc(workerpool->pool_size * sizeof(Worker));

    workerpool->job_queue = job_queue;

    if (workerpool->pool == NULL) { return -1; }

    int fail_index = 0;
    for (int i = 0; i < workerpool->pool_size; i++) {
        int ret = worker_init(
            &workerpool->pool[i],
            create_worker_argument(job_queue, &workerpool->threads_should_quit,
                                   &workerpool->cond_var, &workerpool->mux));
        if (ret != 0) {
            fail_index = i;
            goto error_on_worker_init;
        }
    }

    workerpool->cond_var = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    workerpool->mux      = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

    return 0;

error_on_worker_init:
    for (int i = 0; i < fail_index; i++) {
        worker_destroy(&workerpool->pool[i]);
    }
    free(workerpool->pool);
    workerpool->pool = NULL;
    return -2;
}

int workerpool_start(Workerpool* workerpool) {
    assert(workerpool != NULL);

    for (int i = 0; i < workerpool->pool_size; i++) {
        int ret = worker_start(&workerpool->pool[i]);
        if (ret != 0) { return ret; }
    }

    return 0;
}

int workerpool_stop(Workerpool* workerpool) {
    assert(workerpool != NULL);

    return 0;
}

int workerpool_destroy(Workerpool* workerpool) {
    assert(workerpool != NULL);

    for (int i = 0; i < workerpool->pool_size; i++) {
        worker_destroy(&workerpool->pool[i]);
    }
    free(workerpool->pool);
    workerpool->pool = NULL;

    return 0;
}
