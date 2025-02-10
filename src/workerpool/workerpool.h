#ifndef _BALU_WORKERPOOL_H
#define _BALU_WORKERPOOL_H

#include <stdint.h>
#include "configuration.h"

typedef struct {
    // workers
    uint16_t max_workers;
} Workerpool;

int workerpool_init(Workerpool* workerpool, const Configuration* config);

int workerpool_destroy(Workerpool* workerpool);


#endif
