#include "unity.h"
#include "fifo-test.h"
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

    RUN_TEST(init_fifo_test);

    RUN_TEST(destroy_fifo_empty_test);
    RUN_TEST(destroy_fifo_non_empty_test);

    RUN_TEST(fifo_push_normal);
    RUN_TEST(fifo_push_full);

    RUN_TEST(fifo_pop_normal);
    RUN_TEST(fifo_pop_empty);

    return UNITY_END();
}
