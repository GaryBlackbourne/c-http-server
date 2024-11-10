#ifndef _BALU_FIFO_TEST_H
#define _BALU_FIFO_TEST_H

void init_fifo_test(void);
void destroy_fifo_empty_test(void);
void destroy_fifo_non_empty_test(void);

void fifo_push_normal(void);
void fifo_push_full(void);

void fifo_pop_normal(void);
void fifo_pop_empty(void);

#endif
