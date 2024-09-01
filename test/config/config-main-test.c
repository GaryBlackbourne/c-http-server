#include "unity.h"
#include "config-test.h"
#include "unity_internals.h"

void setUp(void) {
    // Set up before each test, if needed
}

void tearDown(void) {
    // Clean up after each test, if needed
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(create_argument_test);
    RUN_TEST(copy_argument_test);

    RUN_TEST(get_integer_value_test);
    RUN_TEST(get_float_value_test);
    RUN_TEST(get_string_value_test);
    
    RUN_TEST(check_argument_test);

    return UNITY_END();
}
