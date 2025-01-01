#include "workerpool.h"


int init_workerpool(Workerpool* workerpool, const Configuration* config) {
    assert(conman != NULL);
    assert(config != NULL);

    conman->worker_pool.max_connections = config->connection.maximum_connections;
    uint16_t maximum_connections        = config->connection.maximum_connections;

    conman->worker_pool.connections =
        (Connection*) malloc (maximum_connections * sizeof(Connection));

    memset(conman->worker_pool.connections, 0, maximum_connections);

    return 0;
}

int cleanup_worker_pool(ConnectionManager* conman, const Configuration * config) {
    assert(conman != NULL);
    assert(config != NULL);

    Connection* connection;
    for (int i = 0; i < conman->worker_pool.max_connections; i++) {
        connection = &(conman->worker_pool.connections[i]);
        if (connection->running) {
            pthread_join(connection->handler, NULL);
        }
    }
}

int check_available_connection_slot(ConnectionManager* conman) {
    assert(conman != NULL);
    uint16_t max_connections = conman->worker_pool.max_connections;
    for (int i = 0; i < max_connections; i++) {
        if (conman->worker_pool.connections[i].running == 0) {
            return 1;
        }
    }
    return 0;
}

int find_connection_slot(ConnectionManager* conman, Connection** conn) {
    assert(conman != NULL);
    assert(conn   != NULL);

    uint16_t max_connections = conman->worker_pool.max_connections;
    Connection* found_empty_connection = NULL;

    for (int i = 0; i < max_connections; i++) {
        if (conman->worker_pool.connections[i].running == 0) {
            found_empty_connection = &(conman->worker_pool.connections[i]);
            break;
        }
    }

    if (found_empty_connection == NULL){
        return -1;
    }

    (*conn) = found_empty_connection;
    return 0;
}
