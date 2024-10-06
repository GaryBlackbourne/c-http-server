#include "connection-manager.h"
#include "configuration.h"
#include <assert.h>
#include <netinet/in.h>
#include <sys/socket.h>

ConnectionManager create_connection_manager(const Configuration* config) {
    assert(config != NULL);

    ConnectionManager conman;
    setup_connection_manager(&conman, config);

    return conman;
}

int setup_listening_port(ConnectionManager* conman, const Configuration* config) {
    // listening socket
    // TODO: IPv6 support
    conman->connector.socket = socket(AF_INET, SOCK_STREAM, PF_INET);
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

    int setup_listen_port_ret = setup_listening_port(conman, config);
    if (setup_listen_port_ret < 0) { return setup_listen_port_ret; }

    return 0;
}

int start_connection_manager(ConnectionManager* conman) {
    assert(conman != NULL);

    int listen_ret = listen(conman->connector.socket, conman->connector.maximum_queue);
    if (listen_ret < 0) { return -1; }

    return 0;
}

int kill_connection_manager(ConnectionManager *conman) {
    return -1;
}
