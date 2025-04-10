#include <asm-generic/socket.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "config-file-parser.h"
#include "cmdline-parser.h"
#include "configuration.h"
#include "connector.h"

int main(int argc, const char* argv[]) {
    
    // Generate default configuration
    Configuration main_config = configuration_generate_default_config();

    // parse configuration file and override defaults
    // if file is non existent, just go with the defaults
    if (config_file_exists(main_config.configuration.configuration_file_path)) {
        int conf_ret =
            parse_configuration_file(
                                     &main_config,
                                     main_config.configuration.configuration_file_path
                                     );
        if (conf_ret != 0) {
            return -1;
        }
    }

    // parse command line arguments as final, top priority settings
    int cmd_ret  = parse_cmdline_arguments(argc, argv, &main_config);
    if (cmd_ret != 0) {
        return -1;
    }

    printf("Default config path: %s\n", main_config.configuration.configuration_file_path);
    printf("Default executable name: %s\n", main_config.general.binary_name);

    Connector connector;
    connector_init(&connector, &main_config);
    
    /* connector_start(&connector); */

    connector_destroy(&connector);
    
    configuration_destroy(&main_config);
    return 0;
}
