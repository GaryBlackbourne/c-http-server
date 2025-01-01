#include "connector.h"

#include <assert.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int connector_init(Connector* connector, Fifo* job_queue, const Configuration* config) {
    assert(config != NULL);
    assert(job_queue != NULL);

    connector->job_queue = job_queue;
    
    connector->socket = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    int setsockopt_ret =
        setsockopt(
                   connector->socket,
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
                        connector->socket,
                        (struct sockaddr*)&address,
                        sizeof(address)
                        );
    if (bind_ret < 0) {
        perror("bind");
        return -1;
    }
    return 0;
}

int connector_destroy(Connector* connector) {
    assert(connector != NULL);
    connector->task_queue = NULL;
    int ret = close(connector->socket);
    if (ret != 0) {
        perror("close");
    }
    return ret;
}

int connector_start(Connector* connector) {
    assert(connector != NULL);
    // todo
    return 0;
}
