#include <asm-generic/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "config/config-file-parser.h"
#include "config/cmdline-parser.h"
#include "config/configuration.h"

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
    
    /* // create listening socket */
    /* int listen_socket = socket(AF_INET, SOCK_STREAM, PF_INET); */
    /* if (listen_socket < 0) { */
    /*     perror("socket"); */
    /*     exit(EXIT_FAILURE); */
    /* } */

    /* setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 1, 1); */
    /* struct sockaddr_in address = { */
    /*     .sin_addr = j */
    /* } */



    /* const int maximum_waitin_requests = 5; */
    /* int connection = listen(listen_scket, maximum_waitin_requests); */



    destroy_config_struct(&main_config);
    return 0;
}
