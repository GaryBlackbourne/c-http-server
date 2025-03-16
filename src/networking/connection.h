#ifndef _BALU_CONNECTION_H
#define _BALU_CONNECTION_H

#include <netinet/in.h>

/**
 * @brief Connection struct to encapsulate incomming connections.
 */
typedef struct {
    int                socket;
    struct sockaddr_in address;
    socklen_t          address_length;
} Connection;

#endif
