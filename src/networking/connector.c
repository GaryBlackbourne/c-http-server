#include "connector.h"
#include "fifo.h"
#include "job.h"

#include <assert.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <errno.h>

int connector_init(Connector* connector, const Configuration* config) {
    assert(config != NULL);

    init_fifo(&(connector->job_queue), config->job_queue_length);

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
    destroy_fifo(&connector->job_queue);
    int ret = close(connector->socket);
    if (ret != 0) {
        perror("close");
    }
    return ret;
}

int connector_start(Connector* connector) {
    assert(connector != NULL);
    int ret = listen(connector->socket, 5); // why 5?
    if (ret < 0) {
        perror("listen");
        return ret;
    }

    /* struct pollfd fds; */
    /* fds.fd = connector->socket; */
    /* fds.events = POLLIN; */
    /* fds.revents = 0; */

    /* while (poll(&fds, 1, 100/\*ms*\/) != -1) { */
    /*     if (fds.revents & POLLIN) { */
    /*         Job job; */
    /*         job.type = task; */
    /*         job.connection.socket = */
    /*             accept(connector->socket, */
    /*                    (struct sockaddr *)&job.connection.address, */
    /*                    &job.connection.address_length); */
    /*         int ret = fifo_push(&connector->job_queue, &job, sizeof(Job)); */
    /*         if (ret < 0) { */
    /*             fprintf(stderr, "Connection queue is full, dropping connection!\n"); */
    /*             close(job.connection.socket); */
    /*         }else{ */
    /*             printf("new job is added\n"); */
    /*         } */
    /*     } */
    /* } */

    if (errno == EINVAL) { // A signal has been caught!
        return 0;
    } else {
        perror("poll");
        return -1;
    }
    
    // unreachable
    return -1;
}

