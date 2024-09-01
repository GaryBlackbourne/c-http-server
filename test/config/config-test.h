#ifndef _COMMON_TEST_H
#define _COMMON_TEST_H

#include "argument.h"
#include "arg-list.h"

// config-argument-test.c
void get_integer_value_test_normal_usage();
void get_integer_value_test_fail_on_bad_type();
void get_integer_value_test_fail_on_float();
void get_integer_value_test_fail_on_string();

void get_string_value_test_normal_usage();
void get_string_value_test_fail_on_bad_type();
void get_string_value_test_fail_on_int();
void get_string_value_test_fail_on_float();

void get_float_value_test_normal_usage();
void get_float_value_test_fail_on_bad_type();
void get_float_value_test_fail_on_int();
void get_float_value_test_fail_on_string();

void check_argument_test();

void create_argument_test();
void copy_argument_test();

// config-arg-list-test.c

ArgumentList create_argument_list_test();
int destroy_argument_list_test(ArgumentList* list);

int add_argument_test(ArgumentList* list, Argument* arg);
int find_argument_test(const ArgumentList* list, const char* string, const Argument** result);

int remove_argument_test(ArgumentList* list, const char* target_key); // do we need this?

#endif
