#ifndef _BALU_CONFIG_FILE_PARSER_PRIVATE_H
#define _BALU_CONFIG_FILE_PARSER_PRIVATE_H
#include "configuration.h"
#include "stdlib.h"

int is_matching_line(const char* line, size_t line_len, const char* expected);

int get_config_line_value(const char* line, size_t len, char** value);

int process_config_line(const char* line, size_t len, Configuration* config);

#endif
