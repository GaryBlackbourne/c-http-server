#include "workerpool.h"
#include <assert.h>
#include <stdlib.h>

int workerpool_init(Workerpool* workerpool, const Configuration* config) {
    assert(workerpool != NULL);
    assert(config != NULL);
    return 0;
}

int workerpool_destroy(Workerpool* workerpool) {
    assert(workerpool != NULL);
    return 0;
}
