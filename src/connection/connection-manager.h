#ifndef _BALU_CONNECTION_MANAGER_H
#define _BALU_CONNECTION_MANAGER_H

#include "configuration.h"
#include "connection.h"
#include <pthread.h>

typedef struct {
    struct {
        int socket;
        short maximum_queue;
    } connector;
    struct {
        Connection *connections;
        uint16_t max_connections;
    } worker_pool;
} ConnectionManager;

ConnectionManager create_connection_manager(const Configuration* config);

int setup_connection_manager(ConnectionManager*conman, const Configuration* config);

int start_connection_manager(ConnectionManager* conman);

int kill_connection_manager(ConnectionManager* conman);

#endif
