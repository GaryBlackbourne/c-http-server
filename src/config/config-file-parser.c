#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <errno.h>

#include "config-file-parser.h"
#include "configuration.h"
#include "stdio.h"

#include "_config-file-parser-private.h"

int is_matching_line(const char* line, size_t line_len, const char* expected) {
    assert(line != NULL);
    assert(expected != NULL);

    size_t expected_len = strlen(expected);

    if (line_len < expected_len) { return 0; }
    return (strncmp(line, expected, expected_len) == 0);
}

int get_config_line_value(const char* line, size_t len, char** value) {
    assert(line != NULL);
    assert(value != NULL);

    char* v = (char*)line;
    for (size_t i = 0; i < len; i++) {
        if (*(v + i) == '=') {
            *value = (v + i);
            return 0;
        }
    }
    return -1;
}

int process_config_line(const char* line, size_t len, Configuration* config) {
    assert(line != NULL);
    assert(config != NULL);
    char* value = NULL;
    if (is_matching_line(line, len, "port=")) {
        get_config_line_value(line, len, &value);
        /* config->networking.port = str_to_i32(value); */
    }
    return 0;
}

int parse_configuration_file(Configuration* conf, const char* path) {
    assert(path != NULL);

    FILE* fd = fopen(path, "r");
    if (fd == NULL) {
        fprintf(stderr, "Error! Config file not found: '%s'\n", path);
        return -1;
    }

    // parse config line by line
    // append config
    char*  line     = NULL;
    size_t line_len = 0;
    while (getline(&line, &line_len, fd) != -1) {
        int ret = process_config_line(line, line_len, conf);
        free(line);
        line = NULL;
        if (ret != 0) {
            fclose(fd);
            return ret;
        }
    }

    fclose(fd);
    return 0;
}

int config_file_exists(const char* path) {
    assert(path != NULL);
    struct stat buffer;
    if (stat(path, &buffer) == 0) {
        errno = 0;
        return 1;
    } else {
        errno = 0;
        return 0;
    }
}
