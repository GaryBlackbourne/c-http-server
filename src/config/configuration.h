#ifndef _BALU_CONFIGURATION_H
#define _BALU_CONFIGURATION_H

#include <stdio.h>

typedef struct {
    struct {
        char * binary_name;
    } general;

    struct {
        char * configuration_file_path;
    } configuration;

} Configuration;

Configuration generate_default_config();

void destroy_config_struct(Configuration* conf);

void print_configuration(const Configuration* config, FILE* fstream);

#endif
