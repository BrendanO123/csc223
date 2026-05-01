#include <stdio.h>

unsigned tests;
unsigned passedTests;
unsigned failedTests;

unsigned asserts;
unsigned passAsserts;
unsigned failedAsserts;

unsigned currentAssertNumber;
unsigned failedCurrentTest;

unsigned firstTest;
unsigned assertPassed;

START_TESTING(file)
char* file; 
{
    tests = 0;
    passedTests = 0;
    failedTests = 0;

    asserts = 0;
    passAsserts = 0;
    failedAsserts = 0;

    failedCurrentTest = 0;
    currentAssertNumber = 0;
    firstTest = 1;
    printf("\n\t\033[36m---\033[0m %s \033[36m---\033[0m\n", file);
}

incPass() {
    if (tests != 1 && !failedCurrentTest) {
        passedTests++;
    }
}

#define TEST_CASE(description)  printf("\n\t%s\n", description); tests++; incPass(); currentAssertNumber = 0; failedCurrentTest = 0; firstTest = 0;
#define AID_P(msg) printf("\t\t\033[0;32m%s\033[0;37m.\n", msg);
#define AID_F(msg) printf("\t\t\033[0;31m%s\033[0;37m.\n", msg);
ECHO_MESSAGE(msg) 
char* msg; {
    if(assertPassed) {
        AID_P(msg); 
    } else {
        AID_F(msg);
    }
}

ASSERT(boolExp) 
int boolExp; {
    if (boolExp)
        PASS();
    else
        FAIL();
}
ASSERT_EQU(val1, val2)
int val1; int val2; {
    if (val1 == val2)
        PASS();
    else {
        FAIL();
    }
}
ASSERT_STR_EQU(strI, strJ) 
char *strI[], *strJ[]; {
    if (strcmp(strI, strJ) == 0) {
        PASS();
    } else {
        FAIL();
        printf("\t\t\033[0;31m%s != %s\033[0;37m.\n", strI, strJ);
    }
}

ASSERT_INCREASING(arr, n)
int arr[]; int n; {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            FAIL();
            printf("\t\t\033[0;31mArray is not increasing at index %d: %d > %d\033[0;37m.\n", i, arr[i], arr[i + 1]);
            return;
        }
    }
    PASS();
}
ASSERT_DECREASING(arr, n)
int arr[]; int n; {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (arr[i] < arr[i+1]) {
            FAIL();
            printf("\t\t\033[0;31mArray is not decreasing at index %d: %d < %d\033[0;37m.\n", i, arr[i], arr[i + 1]);
            return;
        }
    }
    PASS();
}
ASSERT_ARR_EQU(expected, actual, n)
int expected[]; int actual[]; int n; {
    int i;
    for (i = 0; i < n; i++) {
        if (expected[i] != actual[i]) {
            FAIL();
            printf("\t\t\033[0;31mArray elements differ at index %d: expected %d, got %d\033[0;37m.\n", i, expected[i], actual[i]);
            return;
        }
    }
    PASS();
}

MSSERT(boolExp, msg)
int boolExp; char* msg; {
    ASSERT(boolExp); ECHO_MESSAGE(msg);
}
MSSERT_EQU(val1, val2, msg) int val1; int val2; char* msg; {
    ASSERT_EQU(val1, val2); ECHO_MESSAGE(msg);
}
MSSERT_STR_EQU(strI, strJ, msg) char* strI; char* strJ; char* msg; {
    ASSERT_STR_EQU(strI, strJ); ECHO_MESSAGE(msg);
}

MSSERT_INCREASING(arr, n, msg) int arr[]; int n; char* msg; {
    ASSERT_INCREASING(arr, n); ECHO_MESSAGE(msg);
}
MSSERT_DECREASING(arr, n, msg) int arr[]; int n; char* msg; {
    ASSERT_DECREASING(arr, n); ECHO_MESSAGE(msg);
}
MSSERT_ARR_EQU(expected, actual, n, msg) int expected[]; int actual[]; int n; char* msg; {
    ASSERT_ARR_EQU(expected, actual, n); ECHO_MESSAGE(msg);
}

PASS() {
    asserts++;
    currentAssertNumber++;
    passAsserts++;
    assertPassed = 1;
    printf("\t\033[0;32mAssertion %d passed\033[0;37m.\n", currentAssertNumber);
}

FAIL() {
    asserts++;
    currentAssertNumber++;
    if (!failedCurrentTest) {
        failedCurrentTest = 1;
        failedTests++;
    }
    assertPassed = 0;
    printf("\t\033[0;31mAssertion %d failed\033[0;37m.\n", currentAssertNumber);
    failedAsserts++;
}

END_TESTING() {
    incPass();

    printf("\n\t====================================\n"); 
    (tests == 1) ?  printf("\t1 test.\n") : printf("\t%d tests.\n", tests);
    printf("\t\033[0;32m%d passed\033[0;37m, \033[0;31m %d failed\033[0;37m.", passedTests, failedTests);

    (asserts == 1) ? printf("\n\n1 assertion.\n") : printf("\n\n\t%d assertions.\n", asserts);
    printf("\t\033[0;32m%d passed\033[0;37m, \033[0;31m %d failed\033[0;37m.", passAsserts, failedAsserts);
    printf("\n\t====================================\n");
}