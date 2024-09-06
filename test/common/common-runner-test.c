#include "unity.h"
#include "common-test.h"
#include "unity_internals.h"


void setUp(void) {
    // Set up before each test, if needed
}

void tearDown(void) {
    // Clean up after each test, if needed
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_imax);
    RUN_TEST(test_imin);

    RUN_TEST(str_to_i32_test_normal_behavior);
    RUN_TEST(str_to_i32_test_bad_input);

    RUN_TEST(str_to_float_test_normal_behavior);
    RUN_TEST(str_to_float_test_bad_input);
    RUN_TEST(str_to_float_test_multiple_decimals);

    return UNITY_END();
}
