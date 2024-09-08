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

    RUN_TEST(get_integer_value_test_normal_usage);
    RUN_TEST(get_integer_value_test_fail_on_bad_type);
    RUN_TEST(get_integer_value_test_fail_on_float);
    RUN_TEST(get_integer_value_test_fail_on_string);

    RUN_TEST(get_float_value_test_normal_usage);
    RUN_TEST(get_float_value_test_fail_on_bad_type);
    RUN_TEST(get_float_value_test_fail_on_int);
    RUN_TEST(get_float_value_test_fail_on_string);

    RUN_TEST(get_string_value_test_normal_usage);
    RUN_TEST(get_string_value_test_fail_on_bad_type);

    return UNITY_END();
}
