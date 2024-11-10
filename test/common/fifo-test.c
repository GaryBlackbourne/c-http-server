#include "unity.h"
#include "fifo.h"
#include "fifo-test.h"

void init_fifo_test(void) {
    Fifo fifo;
    int ret = init_fifo(&fifo, 3);
    TEST_ASSERT_EQUAL_INT(0, ret);

    TEST_ASSERT_EQUAL_INT(0, fifo.index);
    TEST_ASSERT_EQUAL_INT(0, fifo.items_num);
    TEST_ASSERT_EQUAL_INT(3, fifo.length);
    TEST_ASSERT_NOT_NULL(fifo.list);

    TEST_ASSERT_EQUAL_INT(fifo.list[0].data_size, 0);
    TEST_ASSERT_EQUAL_INT(fifo.list[1].data_size, 0);
    TEST_ASSERT_EQUAL_INT(fifo.list[2].data_size, 0);

    TEST_ASSERT_NULL(fifo.list[0].data);
    TEST_ASSERT_NULL(fifo.list[1].data);
    TEST_ASSERT_NULL(fifo.list[2].data);
    destroy_fifo(&fifo);
}

void destroy_fifo_empty_test(void) {
    Fifo fifo;
    int ret = init_fifo(&fifo, 3);
    TEST_ASSERT_EQUAL_INT(0, ret);
    destroy_fifo(&fifo);

    TEST_ASSERT_NULL(fifo.list);
    TEST_ASSERT_EQUAL_INT(fifo.length, 0);
    TEST_ASSERT_EQUAL_INT(fifo.index, 0);
    TEST_ASSERT_EQUAL_INT(fifo.items_num, 0);
}

void destroy_fifo_non_empty_test(void) {
    Fifo fifo;
    int ret = init_fifo(&fifo, 3);
    TEST_ASSERT_EQUAL_INT(0, ret);

    int data = 4;
    unsigned data_size = sizeof(int);
    fifo_push(&fifo, &data, data_size);

    destroy_fifo(&fifo);

    TEST_ASSERT_NULL(fifo.list);
    TEST_ASSERT_EQUAL_INT(fifo.length, 0);
    TEST_ASSERT_EQUAL_INT(fifo.index, 0);
    TEST_ASSERT_EQUAL_INT(fifo.items_num, 0);
}

void fifo_push_normal(void){
    Fifo fifo;
    int ret = init_fifo(&fifo, 3);
    TEST_ASSERT_EQUAL_INT(0, ret);

    int test_data[3] = {1, 2, 3};

    ret = fifo_push(&fifo, &(test_data[0]), sizeof(int));
    TEST_ASSERT_EQUAL_INT(0, ret);
    ret = fifo_push(&fifo, &(test_data[1]), sizeof(int));
    TEST_ASSERT_EQUAL_INT(0, ret);
    ret = fifo_push(&fifo, &(test_data[2]), sizeof(int));
    TEST_ASSERT_EQUAL_INT(0, ret);


    destroy_fifo(&fifo);
}

void fifo_push_full(void) {
    Fifo fifo;
    int ret = init_fifo(&fifo, 2);
    TEST_ASSERT_EQUAL_INT(0, ret);

    int test_data[3] = {1, 2, 3};

    ret = fifo_push(&fifo, &(test_data[0]), sizeof(int));
    TEST_ASSERT_EQUAL_INT(0, ret);
    ret = fifo_push(&fifo, &(test_data[1]), sizeof(int));
    TEST_ASSERT_EQUAL_INT(0, ret);
    ret = fifo_push(&fifo, &(test_data[2]), sizeof(int));
    TEST_ASSERT_EQUAL_INT(-1, ret);

    destroy_fifo(&fifo);
}

void fifo_pop_normal(void) {
    
    Fifo fifo;
    int ret = init_fifo(&fifo, 3);
    TEST_ASSERT_EQUAL_INT(0, ret);


    int test_data[3] = {1, 2, 3};

    ret = fifo_push(&fifo, &(test_data[0]), sizeof(int));
    TEST_ASSERT_EQUAL_INT(0, ret);
    ret = fifo_push(&fifo, &(test_data[1]), sizeof(int));
    TEST_ASSERT_EQUAL_INT(0, ret);
    ret = fifo_push(&fifo, &(test_data[2]), sizeof(int));
    TEST_ASSERT_EQUAL_INT(0, ret);

    int returned_data = -1;
    uint32_t size = sizeof(int);

    ret = fifo_pop(&fifo, &returned_data, &size);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(test_data[0], returned_data);
    TEST_ASSERT_EQUAL_INT(sizeof(int), size);
    ret = fifo_pop(&fifo, &returned_data, &size);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(test_data[1], returned_data);
    TEST_ASSERT_EQUAL_INT(sizeof(int), size);
    ret = fifo_pop(&fifo, &returned_data, &size);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(test_data[2], returned_data);
    TEST_ASSERT_EQUAL_INT(sizeof(int), size);

    destroy_fifo(&fifo);
}

void fifo_pop_empty(void) {
    
    Fifo fifo;
    int ret = init_fifo(&fifo, 2);
    TEST_ASSERT_EQUAL_INT(0, ret);
    destroy_fifo(&fifo);

    int returned_data = -1;    
    uint32_t size = sizeof(int);

    ret = fifo_pop(&fifo, &returned_data, &size);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    TEST_ASSERT_EQUAL_INT(sizeof(int), size);
    TEST_ASSERT_EQUAL_INT(-1, returned_data);

}
