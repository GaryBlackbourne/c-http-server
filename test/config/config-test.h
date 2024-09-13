#ifndef _COMMON_TEST_H
#define _COMMON_TEST_H

// config-argument-test.c
void get_integer_value_test_normal_usage();
void get_integer_value_test_fail_on_bad_type();
void get_integer_value_test_fail_on_float();
void get_integer_value_test_fail_on_string();

void get_string_value_test_normal_usage();
void get_string_value_test_fail_on_bad_type();

void get_float_value_test_normal_usage();
void get_float_value_test_fail_on_bad_type();
void get_float_value_test_fail_on_int();
void get_float_value_test_fail_on_string();

void create_argument_test();
void copy_argument_test();

void check_argument_test();

// config-arg-list-test.c
void create_argument_list_test();

void create_argument_list_element_test();
void push_argument_list_element_test_add_first();
void push_argument_list_element_test_add_more();
void remove_argument_list_element_test();

void destroy_argument_list_test();
void add_argument_test();
void find_argument_test();
void remove_argument_test(); // do we need this?

#endif
