#include <asm-generic/socket.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "config-file-parser.h"
#include "cmdline-parser.h"
#include "configuration.h"
#include "connection-manager.h"

int main(int argc, const char* argv[]) {

    // Generate default configuration
    Configuration main_config = generate_default_config();

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

    // Create and setup connection manager
    ConnectionManager conman;
    int ret_conn_setup = setup_connection_manager(&conman, &main_config);
    if (ret_conn_setup != 0) {
        return -1;
        // no resource deallocation?
    }

    int start_conn_manager = start_connection_manager(&conman);
    if (start_conn_manager != 0) {
        return -1;
        // no resource deallocation?
    }


    
    destroy_config_struct(&main_config);
    return 0;
}
