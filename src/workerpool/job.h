#ifndef _BALU_JOB_H
#define _BALU_JOB_H

#include "connection.h"

/**
 * @brief Job struct containing a connection with a request.
 */
typedef struct {
    Connection   connection;
} Job;

#endif
