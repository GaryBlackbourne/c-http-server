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
    
void add_argument_test_add_first() {
    ArgumentList alist = create_argument_list();

    int ret = add_argument(&alist, create_argument("key1", Integer));

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL_STRING("key1", alist.list->argument.key);
    TEST_ASSERT_EQUAL_INT(Integer, alist.list->argument.key);
}

void add_argument_test_add_more() {
    ArgumentList alist = create_argument_list();

    int ret1 = add_argument(&alist, create_argument("key1", Integer));
    int ret2 = add_argument(&alist, create_argument("key2", Float));
    int ret3 = add_argument(&alist, create_argument("key3", String));

    TEST_ASSERT_EQUAL(0, ret1);
    TEST_ASSERT_EQUAL(0, ret2);
    TEST_ASSERT_EQUAL(0, ret3);

    TEST_ASSERT_EQUAL_STRING("key1", alist.list->argument.key);
    TEST_ASSERT_EQUAL_INT(Integer, alist.list->argument.key);

    TEST_ASSERT_EQUAL_STRING("key2", alist.list->next->argument.key);
    TEST_ASSERT_EQUAL_INT(Integer, alist.list->next->argument.key);

    TEST_ASSERT_EQUAL_STRING("key1", alist.list->next->next->argument.key);
    TEST_ASSERT_EQUAL_INT(Integer, alist.list->next->next->argument.key);
}

void find_argument_test_target_found() {
    ArgumentList alist = create_argument_list();

    add_argument(&alist, create_argument("key1", Integer));
    add_argument(&alist, create_argument("key2", Float));
    add_argument(&alist, create_argument("key3", String));

    const Argument* res1;
    int ret1 = find_argument(&alist, "key1", &res1);

    TEST_ASSERT_EQUAL_INT(0, ret1);
    TEST_ASSERT_EQUAL_STRING("key1", res1->key);
    TEST_ASSERT_EQUAL_INT(Integer, res1->type);

    const Argument* res2;
    int ret2 = find_argument(&alist, "key2", &res2);

    TEST_ASSERT_EQUAL_INT(0, ret2);
    TEST_ASSERT_EQUAL_STRING("key2", res2->key);
    TEST_ASSERT_EQUAL_INT(Float, res2->type);

    const Argument* res3;
    int ret3 = find_argument(&alist, "key3", &res3);

    TEST_ASSERT_EQUAL_INT(0, ret3);
    TEST_ASSERT_EQUAL_STRING("key3", res3->key);
    TEST_ASSERT_EQUAL_INT(String, res3->type);
}

void find_argument_test_target_not_found() {
    ArgumentList alist = create_argument_list();

    add_argument(&alist, create_argument("key1", Integer));
    add_argument(&alist, create_argument("key2", Float));
    add_argument(&alist, create_argument("key3", String));

    const Argument* res1 = NULL;
    int ret = find_argument(&alist, "nonexistent", &res1);

    TEST_ASSERT_EQUAL(-1, ret);
    TEST_ASSERT_EQUAL_INT(NULL, res1);
}

void remove_argument_test_target_found() {
    ArgumentList alist = create_argument_list();

    add_argument(&alist, create_argument("key1", Integer));
    add_argument(&alist, create_argument("key2", Float));
    add_argument(&alist, create_argument("key3", String));

    int res = remove_argument(&alist, "key2");

    TEST_ASSERT_EQUAL(0, res);

    TEST_ASSERT_EQUAL_STRING("key1", alist.list->argument.key);
    TEST_ASSERT_EQUAL_INT(Integer, alist.list->argument.type);

    TEST_ASSERT_EQUAL_STRING("key3", alist.list->next->argument.key);
    TEST_ASSERT_EQUAL_INT(String, alist.list->next->argument.type);
}

void remove_argument_test_target_not_found() {
    ArgumentList alist = create_argument_list();

    add_argument(&alist, create_argument("key1", Integer));
    add_argument(&alist, create_argument("key2", Float));
    add_argument(&alist, create_argument("key3", String));

    int res = remove_argument(&alist, "nonexistent");

    TEST_ASSERT_EQUAL(-1, res);

    TEST_ASSERT_EQUAL_STRING("key1", alist.list->argument.key);
    TEST_ASSERT_EQUAL_INT(Integer, alist.list->argument.type);

    TEST_ASSERT_EQUAL_STRING("key2", alist.list->next->argument.key);
    TEST_ASSERT_EQUAL_INT(String, alist.list->next->argument.type);

    TEST_ASSERT_EQUAL_STRING("key3", alist.list->next->next->argument.key);
    TEST_ASSERT_EQUAL_INT(String, alist.list->next->next->argument.type);
}
