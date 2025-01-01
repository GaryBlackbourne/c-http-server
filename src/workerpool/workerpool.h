#ifndef _BALU_WORKERPOOL_H
#define _BALU_WORKERPOOL_H

#include "connection.h"

typedef struct {
    Connection *connections;
    uint16_t max_connections;
} Workerpool;




#endif
