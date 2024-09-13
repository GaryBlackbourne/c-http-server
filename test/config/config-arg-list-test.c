#include "unity.h"
#include "argument.h"
#include "arg-list.h"
#include "config-test-statics.h"

void create_argument_list_element_test() {
    ArgumentListElement* arg_element =
        create_argument_list_element(create_argument("My_Key", Integer));

    TEST_ASSERT_NULL(arg_element->next);
    TEST_ASSERT_NULL(arg_element->prev);
    TEST_ASSERT_EQUAL_STRING("My_Key", arg_element->argument.key);
    TEST_ASSERT_EQUAL_INT(Integer, arg_element->argument.type);
}

void push_argument_list_element_test_add_first() {
    ArgumentList alist = create_argument_list();
    Argument arg1 = create_argument("key1", Integer);
    
    ArgumentListElement* target = create_argument_list_element(arg1);
    push_argument_list_element(&alist, target);

    TEST_ASSERT_EQUAL(target, alist.list);

    TEST_ASSERT_NULL(target->next);
    TEST_ASSERT_NULL(target->prev);
}

void push_argument_list_element_test_add_more() {
    ArgumentList alist = create_argument_list();
    Argument arg1 = create_argument("key1", Integer);
    Argument arg2 = create_argument("key2", Float);

    ArgumentListElement *target1 = create_argument_list_element(arg1);
    ArgumentListElement *target2 = create_argument_list_element(arg2);
    push_argument_list_element(&alist, target1);
    push_argument_list_element(&alist, target2);

    TEST_ASSERT_EQUAL(target1, alist.list);
    TEST_ASSERT_EQUAL(target2, alist.list->next);

    TEST_ASSERT_EQUAL(target2, target1->next);
    TEST_ASSERT_EQUAL(target1, target2->prev);
}

void remove_argument_list_element_test() {
    ArgumentList alist = create_argument_list();
    Argument arg1 = create_argument("key1", Integer);
    Argument arg2 = create_argument("key2", Float);
    Argument arg3 = create_argument("key3", String);

    ArgumentListElement* target1 = create_argument_list_element(arg1);
    ArgumentListElement* target2 = create_argument_list_element(arg2);
    ArgumentListElement* target3 = create_argument_list_element(arg3);
    
    push_argument_list_element(&alist, target1);
    push_argument_list_element(&alist, target2);
    push_argument_list_element(&alist, target3);

    remove_argument_list_element(&alist, target2);

    TEST_ASSERT_EQUAL(alist.list->next, target3);
    TEST_ASSERT_EQUAL(target3->prev, alist.list);
}

void create_argument_list_test() {
    ArgumentList alist = create_argument_list();
    TEST_ASSERT_NULL(alist.list);
}

void destroy_argument_list_test() {
    ArgumentList alist = create_argument_list();

    Argument arg1 = create_argument("key1", Integer);
    Argument arg2 = create_argument("key2", Integer);
    Argument arg3 = create_argument("key3", Integer);

    ArgumentListElement* target1 = create_argument_list_element(arg1);
    ArgumentListElement* target2 = create_argument_list_element(arg2);
    ArgumentListElement* target3 = create_argument_list_element(arg3);

    push_argument_list_element(&alist, target1);
    push_argument_list_element(&alist, target2);
    push_argument_list_element(&alist, target3);

    destroy_argument_list(&alist);

    TEST_ASSERT_NULL(alist.list);

    TEST_ASSERT_NULL(target1);
    TEST_ASSERT_NULL(target2);
    TEST_ASSERT_NULL(target3);
    
}
    
void add_argument_test();

void find_argument_test();

void remove_argument_test();

