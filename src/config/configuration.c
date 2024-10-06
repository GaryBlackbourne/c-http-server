#include <stdlib.h>
#include <string.h>

#include "configuration.h"
#include <stdio.h>

static const char* default_binary_name = "balu";
static const char* default_config_file_path = "$HOME/.config/balu/balu.conf";

Configuration generate_default_config() {
    Configuration conf;

    conf.general.binary_name =
        (char*) malloc (strlen(default_binary_name) + 1);
    strncpy(
            conf.general.binary_name,
            default_binary_name,
            strlen(default_binary_name) + 1
            );

    conf.configuration.configuration_file_path =
        (char*) malloc (strlen(default_config_file_path) + 1);
    strncpy(
            conf.configuration.configuration_file_path,
            default_config_file_path,
            strlen(default_config_file_path) + 1
            );

    conf.connection.port = 80;

    return conf;
}

void destroy_config_struct(Configuration *conf) {
    free(conf->general.binary_name);
    free(conf->configuration.configuration_file_path);
}

void print_configuration(const Configuration *config, FILE* fstream) {
    fprintf(fstream,
            "general:binary_name = %s\n",
            config->general.binary_name);
    fprintf(fstream,
            "configuration:configuration_file_path = %s\n",
            config->configuration.configuration_file_path);
    fprintf(fstream,
            "connection:port = %d\n",
            config->connection.port);
}
