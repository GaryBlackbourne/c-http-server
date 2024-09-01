#include "argument.h"
#include "config-test.h"
#include "unity.h"
#include <string.h>

void get_integer_value_test() {
    const char* test_key = "test-key";
    const char* test_int_value = "55";
    const char* test_float_value = "3.14";
    const char* test_string_value = "some test string";
    Argument test_int_arg = create_argument(test_key, Integer);

    int value = 0;
    int ret = 0;

    ret = 98;
    value = 98;
    strncpy(test_int_arg.value, test_int_value, strlen(test_int_value) + 1); // +1 => \0
    ret = get_integer_value(&test_int_arg, &value);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(55, value);

    ret = 98;
    value = 98;
    strncpy(test_int_arg.value, test_float_value, strlen(test_float_value) + 1);
    ret = get_integer_value(&test_int_arg, &value);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    TEST_ASSERT_EQUAL_INT(98, value);

    ret = 98;
    value = 98;
    strncpy(test_int_arg.value, test_string_value, strlen(test_string_value) + 1);
    ret = get_integer_value(&test_int_arg, &value);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    TEST_ASSERT_EQUAL_INT(98, value);
}

void get_string_value_test() {
    const char* test_key = "test-key";
    const char* test_int_value = "55";
    const char* test_float_value = "3.14";
    const char* test_string_value = "some test string";
    const char* test_string_value_default = "DEFAULT_VALUE";
    Argument test_string_arg = create_argument(test_key, String);

    char value [25];
    int ret = 0;

    ret = 98;
    strncpy(value, test_string_value_default, strlen(test_string_value_default) + 1);
    strncpy(test_string_arg.value, test_string_value, strlen(test_string_value) + 1); // +1 => \0
    ret = get_string_value(&test_string_arg, value);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_STRING("some test string", value);

    ret = 98;
    strncpy(value, test_string_value_default, strlen(test_string_value_default) + 1);
    strncpy(test_string_arg.value, test_float_value, strlen(test_float_value) + 1);
    ret = get_string_value(&test_string_arg, value);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    TEST_ASSERT_EQUAL_STRING("DEFAULT_VALUE", value);

    ret = 98;
    strncpy(value, test_string_value_default, strlen(test_string_value_default) + 1);
    strncpy(test_string_arg.value, test_int_value, strlen(test_int_value) + 1);
    ret = get_string_value(&test_string_arg, value);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    TEST_ASSERT_EQUAL_STRING("DEFAULT_VALUE", value);
}

void get_float_value_test() {
    const char* test_key = "test-key";
    const char* test_int_value = "55";
    const char* test_float_value = "3.14";
    const char* test_string_value = "some test string";
    Argument test_float_arg = create_argument(test_key, Float);

    float value = 0;
    int ret = 0;

    ret = 98;
    value = 98.98;
    strncpy(test_float_arg.value, test_float_value, strlen(test_float_value) + 1); // +1 => \0
    ret = get_float_value(&test_float_arg, &value);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_FLOAT(3.14, value);

    ret = 98;
    value = 98.98;
    strncpy(test_float_arg.value, test_string_value, strlen(test_string_value) + 1);
    ret = get_float_value(&test_float_arg, &value);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    TEST_ASSERT_EQUAL_FLOAT(98.98, value);

    ret = 98;
    value = 98.98;
    strncpy(test_float_arg.value, test_int_value, strlen(test_int_value) + 1);
    ret = get_float_value(&test_float_arg, &value);
    TEST_ASSERT_EQUAL_INT(-1, ret);
    TEST_ASSERT_EQUAL_FLOAT(98.98, value);
}

void check_argument_test() {
    const char* test_key = "test-key";
    const char* test_int_value = "55";
    const char* test_float_value = "3.14";
    const char* test_string_value = "some test string";

    Argument test_int_arg = create_argument(test_key, Integer);
    strncpy(test_int_arg.value, test_int_value, strlen(test_int_value) + 1); // +1 => \0

    Argument test_float_arg = create_argument(test_key, Float);
    strncpy(test_float_arg.value, test_float_value, strlen(test_float_value) + 1); // +1 => \0

    Argument test_string_arg = create_argument(test_key, String);
    strncpy(test_string_arg.value, test_string_value, strlen(test_string_value) + 1); // +1 => \0

    // Test good scenarios
    TEST_ASSERT_EQUAL_INT(0, check_argument(&test_int_arg));
    TEST_ASSERT_EQUAL_INT(0, check_argument(&test_float_arg));
    TEST_ASSERT_EQUAL_INT(0, check_argument(&test_string_arg));

    // Test bad scenarios
    // int
    strncpy(test_int_arg.value, test_float_value, strlen(test_float_value) + 1);
    TEST_ASSERT_EQUAL_INT(-1, check_argument(&test_int_arg));
    strncpy(test_int_arg.value, test_string_value, strlen(test_string_value) + 1);
    TEST_ASSERT_EQUAL_INT(-1, check_argument(&test_int_arg));

    // float
    strncpy(test_float_arg.value, test_int_value, strlen(test_int_value) + 1);
    TEST_ASSERT_EQUAL_INT(-1, check_argument(&test_float_arg));
    strncpy(test_float_arg.value, test_string_value, strlen(test_string_value) + 1);
    TEST_ASSERT_EQUAL_INT(-1, check_argument(&test_float_arg));

    // string
    strncpy(test_string_arg.value, test_float_value, strlen(test_float_value) + 1);
    TEST_ASSERT_EQUAL_INT(-1, check_argument(&test_string_arg));
    strncpy(test_string_arg.value, test_int_value, strlen(test_int_value) + 1);
    TEST_ASSERT_EQUAL_INT(-1, check_argument(&test_string_arg));
}

void create_argument_test() {
    const char* test_key = "test-key";
    Argument test_arg = create_argument(test_key, Integer);

    TEST_ASSERT_EQUAL_STRING(test_key, test_arg.key);
    TEST_ASSERT_EQUAL_STRING("", test_arg.value);
    TEST_ASSERT_EQUAL_INT(Integer, test_arg.type);
}

void copy_argument_test() {
    Argument arg_1 = create_argument("test-key-1", Integer);
    Argument arg_2 = copy_argument(&arg_1);

    TEST_ASSERT_EQUAL_INT(arg_1.type, arg_2.type);
    TEST_ASSERT_EQUAL_STRING(arg_1.key, arg_2.key);
    TEST_ASSERT_EQUAL_STRING(arg_1.value, arg_2.value);
}
