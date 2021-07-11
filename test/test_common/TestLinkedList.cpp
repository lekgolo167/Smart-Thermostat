#include <unity.h>

#include "Sane.hpp"

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_linked_list_insert(void) {
    TEST_ASSERT_EQUAL(117, why(117));
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_linked_list_insert);
    UNITY_END();

    return 0;
}