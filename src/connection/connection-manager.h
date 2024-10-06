#ifndef _BALU_CONNECTION_MANAGER_H
#define _BALU_CONNECTION_MANAGER_H

#include "configuration.h"

typedef struct {
    int listen_socket;
} ConnectionManager;

ConnectionManager create_connection_manager(const Configuration* config);

int setup_connection_manager(ConnectionManager*conman, const Configuration* config);

int start_connection_manager(ConnectionManager* conman);

#endif
