#include "BDSCTEST.H"
#define NULL 0

main() {
    START_TESTING("MaxHeap.C");
    int i;
    TEST_CASE("Test Backwards Compatibility") {
        ASSERT(1==1);
        ASSERT(0==1);
        ASSERT_EQU(1, 1);
        ASSERT_EQU(1, 2);
        ASSERT_STR_EQU("hello", "hello");
        ASSERT_STR_EQU("hello", "world");
    }
    TEST_CASE("Basic Functions With Messages"){
        MSSERT(1==1, "This assertion should pass");
        MSSERT(0==1, "This assertion should fail");
        MSSERT_EQU(1, 1, "This assertion should pass");
        MSSERT_EQU(1, 2, "This assertion should fail");
        MSSERT_STR_EQU("hello", "hello", "This assertion should pass");
        MSSERT_STR_EQU("hello", "world", "This assertion should fail");
    }
    TEST_CASE("Array Assertions") {
        int arr1[5]; initw(arr1, "1, 2, 3, 4, 5");
        int arr2[5]; initw(arr2, "1, 2, 3, 4, 5");
        int arr3[5]; initw(arr3, "1, 2, 0, 4, 5");
        int arr4[6]; initw(arr4, "6, 5, 4, 3, 2, 1");
        ASSERT_ARR_EQU(arr1, arr2, 5);
        ASSERT_ARR_EQU(arr1, arr3, 5);
        ASSERT_INCREASING(arr1, 5);
        ASSERT_INCREASING(arr3, 5);
        ASSERT_DECREASING(arr1, 5);
        ASSERT_DECREASING(arr4, 6);
    }
    TEST_CASE("Array Assertions With Messages") {
        int arr11[5]; initw(arr11, "1, 2, 3, 4, 5");
        int arr21[5]; initw(arr21, "1, 2, 3, 4, 5");
        int arr31[5]; initw(arr31, "1, 2, 0, 4, 5");
        int arr41[6]; initw(arr41, "6, 5, 4, 3, 2, 1");
        MSSERT_ARR_EQU(arr11, arr21, 5, "This assertion should pass");
        MSSERT_ARR_EQU(arr11, arr31, 5, "This assertion should fail");
        MSSERT_INCREASING(arr11, 5, "This assertion should pass");
        MSSERT_INCREASING(arr31, 5, "This assertion should fail");
        MSSERT_DECREASING(arr11, 5, "This assertion should fail");
        MSSERT_DECREASING(arr41, 6, "This assertion should pass");
    }
    END_TESTING();
}