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
        free(heap);
    }

    TEST_CASE("Test can create insert and fetch one node") {
        struct MaxHeap* heap1;
        heap1 = mkMaxHeap(128);
        insert(heap1, 13);
        ASSERT(peakMax(heap1) == 13);
        free(heap1);
    }

    TEST_CASE("Test can create insert and remove nodes") {
        struct MaxHeap* heap2;
        heap2 = mkMaxHeap(128);
        insert(heap2, 17);
        ASSERT(peakMax(heap2) == 17);
        ASSERT(removeMax(heap2) == 17);
        insert(heap2, 13);
        ASSERT(peakMax(heap2) == 13);
        free(heap2);
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
        free(heap3);
    }

    TEST_CASE("Test insert and remove at will"){
        struct MaxHeap* heap4;
        heap4 = mkMaxHeap(128);
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
        free(heap4);
    }

    TEST_CASE("Test can grow capacity"){
        struct MaxHeap* heap5;
        heap5 = mkMaxHeap(128);
        for(i = 0; i < 100; i++){
            ASSERT(insert(heap5,i) == 0);
        }
        grow(heap5);
        ASSERT(heap5->capacity == 256);
        ASSERT(heap5->size == 100);
        for(i = 99; i >=0; i--){
            ASSERT(removeMax(heap5) == i);
        }
        free(heap5);
    }

    /*TEST_CASE("Test can auto-grow capacity on insert"){
        struct MaxHeap* heap6;
        heap6 = mkMaxHeap(4);
        for(i = 0; i < 16; i++){
            ASSERT(insert(heap6,i) == 0);
            int j;
            for(j = 0; j < heap6->size; j++){
                printf("%d", heap6->data[j]);
                printf("\r\n");
            }
        }
        ASSERT(heap6->capacity == 16);
        ASSERT(heap6->size == 16);
        for(i = 15; i >=0; i--){
            printf("%d", peakMax(heap6));
            ASSERT(removeMax(heap6) == i);
        }
    }*/

    END_TESTING();
}