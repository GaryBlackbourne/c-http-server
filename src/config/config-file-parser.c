#include <assert.h>
#include <sys/stat.h>

#include "config-file-parser.h"
#include "configuration.h"
#include "stdio.h"

int parse_configuration_file(Configuration *conf, const char * path) {
    assert(path != NULL);

    FILE* fd = fopen(path, "r");
    if (fd == NULL) {
        fprintf(stderr, "Error! Config file not found: '%s'\n", path);
        return -1;
    }

    (void) conf;

    // parse config line by line 
    // append config

    return 0;
}

int config_exists(const char* path) {
    assert(path != NULL);

    struct stat buffer;
    
    return (stat(path, &buffer) == 0);
}
