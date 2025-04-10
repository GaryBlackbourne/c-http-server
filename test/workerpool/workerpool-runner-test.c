#include "unity.h"
#include "unity_internals.h"
#include "configuration.h"

#include "job-queue-test.h"

Configuration config;

void setUp(void) {
    config = configuration_generate_default_config();
}

void tearDown(void) {
    configuration_destroy(&config);
}

int main(void) {
    UNITY_BEGIN();

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
