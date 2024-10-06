#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "cmdline-parser.h"
#include "configuration.h"

#include "_cmdline-parser-private.h"

int is_matching_arg(const char* arg, const char* expected) {
    assert(arg != NULL);
    assert(expected != NULL);

    int arg_len = strlen(arg);
    int expected_len = strlen(expected);

    if (arg_len != expected_len) {
        return 0; // 0 means false here
    }
    return (strncmp(arg, expected, expected_len) == 0);
}

int parse_cmdline_arguments(const int argc, const char **argv, Configuration *conf) {
    assert(conf != NULL);
    assert(argv != NULL);

    for (int i = 1; i < argc; i++) {
        if (is_matching_arg(argv[i], "--version")) {
            // print version
            continue;
        } else if (is_matching_arg(argv[i], "--port")) {
            // set port
            continue;
        } else if (is_matching_arg(argv[i], "--dump-config")) {
            // dump configuration to file on nect argument
            continue;
        }

        fprintf(stderr, "Argument: '%s' is not found!\n", argv[i]);
        return -1;
    }

    return 0;
}
