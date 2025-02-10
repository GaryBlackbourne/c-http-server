#ifndef _BALU_CMDLINE_PARSER_H
#define _BALU_CMDLINE_PARSER_H

#include "configuration.h"

/**
 * @brief Parse arguments from command line and override configuration values.
 *
 * This function gets the argument list, and then sweeps it. For every option found,
 * the given configuration struct is updated accordingly.
 *
 * @param argc - const int argument counter.
 * @param argv - const char** string array of the given arguments.
 * @param conf - Configuration* pointer to the configuration structure.
 *
 * @return Upon success, 0 is returned. On error, a non-zero number is returned.
 */
int parse_cmdline_arguments(const int argc, const char *argv[], Configuration *conf);
    
#endif    
