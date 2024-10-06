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

int setup_connection_manager(ConnectionManager* conman, const Configuration* config) {
    assert(conman != NULL);

    // listening socket
    // TODO: IPv6 support
    conman->listen_socket = socket(AF_INET, SOCK_STREAM, PF_INET);
    if (conman->listen_socket < 0) {
        perror("socket");
        return -1;
    }

    int reuse = 1;
    int setsockopt_ret =
        setsockopt(
                   conman->listen_socket,
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
                        conman->listen_socket,
                        (struct sockaddr*)&address,
                        sizeof(address)
                        );
    if (bind_ret < 0) {
        perror("bind");
        return -1;
    }

    return 0;
}

int start_connection_manager(ConnectionManager* conman) {
    assert(conman != NULL);
    return -1;
}
