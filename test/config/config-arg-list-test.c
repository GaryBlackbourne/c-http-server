#include "unity.h"
#include "argument.h"
#include "arg-list.h"
#include "config-test-statics.h"

void create_argument_list_element_test() {
    Argument arg = create_argument("My_Key", Integer);
    ArgumentListElement* arg_element = create_argument_list_element(&arg);

    TEST_ASSERT_NULL(arg_element->next);
    TEST_ASSERT_NULL(arg_element->prev);
    TEST_ASSERT_NOT_NULL(arg_element->argument);
    TEST_ASSERT_EQUAL(&arg, arg_element->argument);
}

void push_argument_list_element_test() {
    ArgumentList alist = create_argument_list();
    Argument arg1 = create_argument("key1", Integer);
    Argument arg2 = create_argument("key2", Float);
    
    push_argument_list_element(&alist, create_argument_list_element(&arg1));

    TEST_ASSERT_NOT_NULL(alist.list);

    TEST_ASSERT_NULL(alist.list->next);
    TEST_ASSERT_NULL(alist.list->prev);

    TEST_ASSERT_EQUAL_STRING("key1", alist.list->argument->key);
    TEST_ASSERT_EQUAL_INT(Integer, alist.list->argument->type);

    push_argument_list_element(&alist, create_argument_list_element(&arg2));

    TEST_ASSERT_NOT_NULL(alist.list->next);
    TEST_ASSERT_NULL(alist.list->next->next);
    TEST_ASSERT_EQUAL(alist.list, alist.list->next->prev);

    TEST_ASSERT_EQUAL_STRING("key2", alist.list->next->argument->key);
    TEST_ASSERT_EQUAL_INT(Float, alist.list->next->argument->type);

}

void remove_argument_list_element_test() {
    ArgumentList alist = create_argument_list();
    Argument arg1 = create_argument("key1", Integer);
    Argument arg2 = create_argument("key2", Float);
    Argument arg3 = create_argument("key3", String);

    ArgumentListElement* target1 = create_argument_list_element(&arg1);
    ArgumentListElement* target2 = create_argument_list_element(&arg2);
    ArgumentListElement* target3 = create_argument_list_element(&arg3);
    
    push_argument_list_element(&alist, target1);
    push_argument_list_element(&alist, target2);
    push_argument_list_element(&alist, target3);

    TEST_ASSERT_EQUAL(alist.list, target1);
    TEST_ASSERT_EQUAL(alist.list->next, target2);
    TEST_ASSERT_EQUAL(alist.list->next->next, target3);
    
    remove_argument_list_element(&alist, target2);

    TEST_ASSERT_EQUAL(alist.list->next, target3);
    TEST_ASSERT_EQUAL(target3->prev, alist.list);
}

void create_argument_list_test() {
    ArgumentList alist = create_argument_list();
    TEST_ASSERT_NULL(alist.list);
}

void destroy_argument_list_test();
    
void add_argument_test();

void find_argument_test();

void remove_argument_test();

