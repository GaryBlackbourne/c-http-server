#include "unity.h"
#include "unity_internals.h"
#include "configuration.h"
#include "connector-test.h"

Configuration config;

void setUp(void) {
    config = configuration_generate_default_config();
}

void tearDown(void) {
    configuration_destroy(&config);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(connector_init_test_is_correct);
    RUN_TEST(connector_destroy_test_is_correct);

    return UNITY_END();
}
