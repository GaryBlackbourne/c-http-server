#include "common-test.h"
#include "common.h"
#include "unity.h"

void test_imin(void) {
    int a = 4;
    int b = 9;
    int res = 0;

    res = imin(a, b);
    TEST_ASSERT_EQUAL(a, res);

    b = -1 * b;

    res = imin(a, b);
    TEST_ASSERT_EQUAL(b, res);
}

void test_imax(void) {
    int a = 4;
    int b = 9;
    int res = 0;

    res = imax(a, b);
    TEST_ASSERT_EQUAL(b, res);

    b = -1 * b;

    res = imax(a, b);
    TEST_ASSERT_EQUAL(a, res);
}
