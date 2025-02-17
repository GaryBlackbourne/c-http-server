#ifndef _BALU_JOB_H
#define _BALU_JOB_H

#include "connection.h"

enum JobType {
    task = 0,
    quit = 1,
};

typedef struct {
    enum JobType type;
    Connection   connection;
} Job;

#endif
