#include <assert.h>
#include <stdlib.h>

#include "workerpool.h"
#include "worker.h"
#include "fifo.h"

int workerpool_init(Workerpool* workerpool, const Fifo* job_queue, const Configuration* config) {
    assert(workerpool != NULL);
    assert(config != NULL);

    workerpool->pool_size = config->worker_pool_lize;
    workerpool->pool = (Worker*) malloc(workerpool->pool_size * sizeof(Worker));

    workerpool->job_queue = job_queue;
    
    if (workerpool->pool == NULL) {
        return -1;
    }

    int fail_index = 0;
    for (int i = 0; i < workerpool->pool_size; i++) {
        int ret = worker_init(&workerpool->pool[i]);
        if (ret != 0) {
            fail_index = i;
            goto error_on_worker_init;
        }
    }

    return 0;

 error_on_worker_init:
    for (int i = 0; i < fail_index; i ++) {
        worker_destroy(&workerpool->pool[i]);
    }
    free(workerpool->pool);
    workerpool->pool = NULL;
    return -2;
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
