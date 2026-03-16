#include "MaxHeap.h"
#include "BDSCTEST.H"
#define NULL 0

main() {
    START_TESTING("MaxHeap.C");
    int i;
    TEST_CASE("Test can create heap") {
        struct MaxHeap* heap;
        heap = mkMaxHeap(128);
        ASSERT(heap->capacity == 128);
        ASSERT(heap->size == 0);
        ASSERT(heap->data != NULL);
    }

    TEST_CASE("Test can create insert and fetch one node") {
        struct MaxHeap* heap1;
        heap1 = mkMaxHeap(128);
        insert(heap1, 13);
        ASSERT(peakMax(heap1) == 13);
    }

    TEST_CASE("Test can create insert and remove nodes") {
        struct MaxHeap* heap2;
        heap2 = mkMaxHeap(128);
        insert(heap2, 17);
        ASSERT(peakMax(heap2) == 17);
        ASSERT(removeMax(heap2) == 17);
        insert(heap2, 13);
        ASSERT(peakMax(heap2) == 13);
    }

    TEST_CASE("Test can create insert and remove multiple nodes") {
        struct MaxHeap* heap3;
        heap3 = mkMaxHeap(128);
        for(i = 0; i < 100; i++){
            insert(heap3,i);
        }
        for(i = 99; i >=0; i--){
            ASSERT(removeMax(heap3) == i);
        }
    }

    TEST_CASE("Test insert and remove at will"){
        struct MaxHeap* heap4;
        heap4 = mkMaxHeap(128);
        int* data; data = alloc(128);
        for(i = 0; i < 100; i++){
            insert(heap4,i);
        }
        for(i = 99; i >=10; i--){
            ASSERT(removeMax(heap4) == i);
        }
        for(i = 10; i < 100; i++){
            insert(heap4,i);
        }
        for(i = 99; i >=0; i--){
            ASSERT(removeMax(heap4) == i);
        }
    }

    END_TESTING();
}