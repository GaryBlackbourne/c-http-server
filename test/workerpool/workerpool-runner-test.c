#include "unity.h"
#include "unity_internals.h"
#include "configuration.h"


Configuration config;

void setUp(void) {
    config = configuration_generate_default_config();
}

void tearDown(void) {
    configuration_destroy(&config);
}

int main(void) {
    UNITY_BEGIN();


    return UNITY_END();
}
