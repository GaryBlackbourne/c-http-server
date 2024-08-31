#include "unity.h"
#include "common-test.h"


void setUp(void) {
    // Set up before each test, if needed
}

void tearDown(void) {
    // Clean up after each test, if needed
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_imax);
    RUN_TEST(test_imin);
    return UNITY_END();
}
