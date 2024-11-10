#include "connection-manager.h"
#include "configuration.h"
#include "connection.h"
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>

int setup_worker_pool(ConnectionManager* conman, const Configuration* config) {
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
    
}

int setup_listening_port(ConnectionManager* conman, const Configuration* config) {
    assert(conman != NULL);
    assert(config != NULL);

    // listening socket
    // TODO: IPv6 support
    conman->connector.socket = socket(AF_INET, SOCK_STREAM, 0);
    if (conman->connector.socket < 0) {
        perror("socket");
        return -1;
    }

    int reuse = 1;
    int setsockopt_ret =
        setsockopt(
                   conman->connector.socket,
                   SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT,
                   &reuse,
                   sizeof(reuse)
                   );
    if (setsockopt_ret != 0) {
        perror("setsockopt");
        return -1;
    }

    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(config->connection.port)
    };
    
    int bind_ret = bind(
                        conman->connector.socket,
                        (struct sockaddr*)&address,
                        sizeof(address)
                        );
    if (bind_ret < 0) {
        perror("bind");
        return -1;
    }

    return 0;
}

int setup_connection_manager(ConnectionManager* conman, const Configuration* config) {
    assert(conman != NULL);
    assert(config != NULL);

    int setup_listen_port_ret = setup_listening_port(conman, config);
    if (setup_listen_port_ret < 0) { return setup_listen_port_ret; }
    int setup_worker_pool_ret = setup_worker_pool(conman, config);
    if (setup_worker_pool_ret < 0) { return setup_worker_pool_ret; }

    return 0;
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

int start_connection_manager(ConnectionManager* conman) {
    assert(conman != NULL);

    int listen_ret = listen(conman->connector.socket, conman->connector.maximum_queue);
    if (listen_ret < 0) {
        perror("listen");
        return -1;
    }

    // setup poll list
    struct pollfd pollfd_connector = {
        .fd = conman->connector.socket,
        .events = POLLIN
    };

    // main request handler loop
    while(1) {

        // poll on connector.socket
        if (poll(&pollfd_connector, 1, -1) < 0) {
            if (errno == EINTR) {
                // upon signal, we exit
                return 0;
            }
            // if not signal just error, then return with error
            perror("poll");
            return -1;
        }

        // accept connection
        struct sockaddr_in client_address;
        socklen_t client_address_len = sizeof(client_address);
        int connection_socket = accept(
                                       conman->connector.socket,
                                       (struct sockaddr*)&client_address,
                                       &client_address_len
                                       );
        if (connection_socket == -1) {
            perror("accept");
            return -1;
        }

        // check for available connection space
        Connection* conn;
        if(find_connection_slot(conman, &conn) < 0) {
            // if there is no free connection slot then deny the connection
            close(connection_socket);
            continue;
        }

        conn->socket             = connection_socket;
        conn->client_address     = client_address;
        conn->client_address_len = client_address_len;
        conn->running            = 0;
        conn->handler            = 0;

        // start connection thread
        if (start_worker_thread(conn) < 0) {
            return -1;
        }

    } // end of loop

    // unreachable
    return -1;
}

int kill_connection_manager(ConnectionManager *conman) {
    assert(conman != NULL);
    // unimplemented
    return -1;
}
