#ifndef _BALU_CONNECTOR_H
#define _BALU_CONNECTOR_H

#include "fifo.h"
#include "configuration.h"

typedef struct {
    int socket;
    Fifo job_queue;
}Connector;

int connector_init(Connector* connector, const Configuration* config);

int connector_destroy(Connector* connector);

int connector_start(Connector* connector);

#endif

