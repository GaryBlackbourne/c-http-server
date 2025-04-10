#ifndef _BALU_JOB_QUEUE_TEST_HPP
#define _BALU_JOB_QUEUE_TEST_HPP

void job_queue_init_test(void);
void job_queue_destroy_empty_test(void);
void job_queue_destroy_non_empty_test(void);

void job_queue_push_normal(void);
void job_queue_push_full(void);

void job_queue_pop_normal(void);
void job_queue_pop_empty(void);
void job_queue_pop_null_size(void);

#endif /* _BALU_JOB_QUEUE_TEST */
