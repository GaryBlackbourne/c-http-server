#include "unity.h"
#include "unity_internals.h"
#include "configuration.h"
#include "connector-test.h"

Configuration config;

void setUp(void) {
    config = generate_default_config();
}

void tearDown(void) {
    destroy_config_struct(&config);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(connector_init_test_is_correct);
    RUN_TEST(connector_destroy_test_is_correct);

    return UNITY_END();
}
