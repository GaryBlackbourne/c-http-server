#include "unity.h"
#include "connection-test.h"
#include "unity_internals.h"
#include "configuration.h"

Configuration config;

void setUp(void) {
    config = generate_default_config();
}

void tearDown(void) {
    destroy_config_struct(&config);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_setup_worker_pool);
    /* RUN_TEST(test_imin); */

    /* RUN_TEST(str_to_i32_test_normal_behavior); */
    /* RUN_TEST(str_to_i32_test_bad_input); */

    /* RUN_TEST(str_to_float_test_normal_behavior); */
    /* RUN_TEST(str_to_float_test_bad_input); */
    /* RUN_TEST(str_to_float_test_multiple_decimals); */

    return UNITY_END();
}
