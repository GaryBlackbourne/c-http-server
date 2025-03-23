#ifndef _BALU_CONNECTION_H
#define _BALU_CONNECTION_H

#include <netinet/in.h>

/**
 * @brief Connection struct to encapsulate incomming connections.
 *
 * This struct identifies an incomming request, and storing all
 * data available at connection time. Incomming jobs are put to
 * a fifo, and then picked by worker threads and processed.
 */
typedef struct {
    int                socket;
    struct sockaddr_in address;
    socklen_t          address_length;
} Connection;

#endif
