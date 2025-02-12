#ifndef _BALU_CONFIGURATION_H
#define _BALU_CONFIGURATION_H

#include <netinet/in.h>
#include <stdio.h>

typedef struct {
    struct {
        char * binary_name;
    } general;

    struct {
        char * configuration_file_path;
    } configuration;

    struct {
        in_port_t port;
        short maximum_connection_queue;
        uint16_t maximum_connections;
    } connection;

    uint16_t job_queue_length;

    uint16_t worker_pool_lize;

} Configuration;

Configuration generate_default_config();

void destroy_config_struct(Configuration* conf);

void print_configuration(const Configuration* config, FILE* fstream);

#endif
