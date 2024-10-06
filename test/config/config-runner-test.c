#include "unity.h"
#include "unity_internals.h"

#include "config-file-parser-test.h"
#include "cmdline-parser-test.h"
#include "configuration-test.h"

void setUp(void) {
    // Set up before each test, if needed
}

void tearDown(void) {
    // Clean up after each test, if needed
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(is_matching_line_test_match_exact);
    RUN_TEST(is_matching_line_test_match_equation);
    RUN_TEST(is_matching_line_test_no_match_bad_char);
    RUN_TEST(is_matching_line_test_no_match_bad_len);

    RUN_TEST(is_matching_arg_test_matching);
    RUN_TEST(is_matching_arg_test_non_matching_shorter);
    RUN_TEST(is_matching_arg_test_non_matching_longer);
    RUN_TEST(is_matching_arg_test_non_matching_bad_char);

    return UNITY_END();
}
