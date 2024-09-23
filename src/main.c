#include "config/config-file-parser.h"
#include "config/cmdline-parser.h"
#include "config/configuration.h"

int main(int argc, const char* argv[]) {

    (void) argc;
    (void) argv;

    // Generate default configuration
    Configuration main_config = generate_default_config();

    // parse configuration file and override defaults
    if (config_exists(main_config.configuration.configuration_file_path)) {
        int conf_ret = parse_configuration_file(&main_config, main_config.configuration.configuration_file_path);
        if (conf_ret != 0) {
            return -1;
        }
    }

    int cmd_ret  = parse_cmdline_arguments(argc, argv, &main_config);
    if (cmd_ret != 0) {
        return -1;
    }


    destroy_config_struct(&main_config);
    return 0;
}
