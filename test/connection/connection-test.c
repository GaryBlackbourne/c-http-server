#include "connection-test.h"
#include "unity.h"

#include "configuration.h"
#include "connection-manager.h"
#include <stdlib.h>
#include <string.h>

extern Configuration config;

extern int setup_worker_pool(ConnectionManager* conman,
                             const Configuration* config);
extern int cleanup_worker_pool(ConnectionManager* conman,
                               const Configuration* config);

void test_setup_worker_pool() {
    ConnectionManager conman;
    setup_worker_pool(&conman, &config);

    TEST_ASSERT_EQUAL_INT(config.connection.maximum_connections, conman.worker_pool.max_connections);

    const unsigned array_len
        = config.connection.maximum_connections * sizeof(Connection);
    char* zero_array = (char*)malloc(array_len);
    memset(zero_array, 0, array_len);

    TEST_ASSERT_EQUAL_CHAR_ARRAY(zero_array, conman.worker_pool.connections,
                                 conman.worker_pool.max_connections);

    free(conman.worker_pool.connections);
    free(zero_array);
}

void test_cleanup_worker_pool() {
    return;
}
