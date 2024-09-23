#ifndef _BALU_CONFIG_FILE_PARSER_H
#define _BALU_CONFIG_FILE_PARSER_H

#include "configuration.h"

int parse_configuration_file(Configuration* conf, const char* path);

int config_exists(const char* path);

#endif
