#include "unity.h"
#include "unity_internals.h"

#include "configuration.h"


#include "fifo-test.h"
#include "common-test.h"
#include "config-file-parser-test.h"
#include "cmdline-parser-test.h"
#include "configuration-test.h"
#include "connector-test.h"
#include "job-queue-test.h"

Configuration config;

void setUp(void) {
    // Set up before each test, if needed
    config = configuration_generate_default_config();
}

void tearDown(void) {
    // Clean up after each test, if needed
    configuration_destroy(&config);
}

int main(void) {
    UNITY_BEGIN();

    //-------------------- common --------------------
    RUN_TEST(test_imax);
    RUN_TEST(test_imin);

    RUN_TEST(str_to_i32_test_normal_behavior);
    RUN_TEST(str_to_i32_test_bad_input);

    RUN_TEST(str_to_float_test_normal_behavior);
    RUN_TEST(str_to_float_test_bad_input);
    RUN_TEST(str_to_float_test_multiple_decimals);

    RUN_TEST(fifo_init_test);

    RUN_TEST(fifo_destroy_empty_test);
    RUN_TEST(fifo_destroy_non_empty_test);

    RUN_TEST(fifo_push_normal);
    RUN_TEST(fifo_push_full);

    RUN_TEST(fifo_pop_normal);
    RUN_TEST(fifo_pop_empty);
    RUN_TEST(fifo_pop_null_size);

    //-------------------- config --------------------
    RUN_TEST(is_matching_line_test_match_exact);
    RUN_TEST(is_matching_line_test_match_equation);
    RUN_TEST(is_matching_line_test_no_match_bad_char);
    RUN_TEST(is_matching_line_test_no_match_bad_len);

    RUN_TEST(is_matching_arg_test_matching);
    RUN_TEST(is_matching_arg_test_non_matching_shorter);
    RUN_TEST(is_matching_arg_test_non_matching_longer);
    RUN_TEST(is_matching_arg_test_non_matching_bad_char);

    //-------------------- connection --------------------
    RUN_TEST(connector_init_test_is_correct);
    RUN_TEST(connector_destroy_test_is_correct);

    //-------------------- workerpool --------------------
    RUN_TEST(job_queue_init_test);
    RUN_TEST(job_queue_destroy_empty_test);
    RUN_TEST(job_queue_destroy_non_empty_test);
    RUN_TEST(job_queue_push_normal);
    RUN_TEST(job_queue_push_full);
    RUN_TEST(job_queue_pop_normal);
    RUN_TEST(job_queue_pop_empty);
    RUN_TEST(job_queue_pop_null_size);

    return UNITY_END();
}
