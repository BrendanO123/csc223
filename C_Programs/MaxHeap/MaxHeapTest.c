#include "MaxHeap.h"
#include "BDSCTEST.H"
#define NULL 0

main() {
    START_TESTING("MaxHeap.C");
    int i;
    TEST_CASE("Test can create heap") {
        struct MaxHeap* heap;
        heap = mkMaxHeap(128);
        MSSERT_EQU(heap->capacity, 128, "Heap capacity not set correctly");
        MSSERT_EQU(heap->size, 0, "Heap size not set correctly");
        MSSERT(heap->data != NULL, "Heap data not initialized correctly");
        free(heap);
    }

    TEST_CASE("Test can create insert and fetch one node") {
        struct MaxHeap* heap1;
        heap1 = mkMaxHeap(128);
        insert(heap1, 13);
        MSSERT_EQU(peakMax(heap1), 13, "Max value not set correctly");
        free(heap1);
    }

    TEST_CASE("Test can create insert and remove nodes") {
        struct MaxHeap* heap2;
        heap2 = mkMaxHeap(128);
        insert(heap2, 17);
        MSSERT_EQU(peakMax(heap2), 17, "Max value not set correctly");
        MSSERT_EQU(removeMax(heap2), 17, "Max value not properly returned when removed");
        insert(heap2, 13);
        MSSERT_EQU(peakMax(heap2), 13, "Max value not updated correctly");
        free(heap2);
    }

    TEST_CASE("Test can create insert and remove multiple nodes") {
        struct MaxHeap* heap3;
        heap3 = mkMaxHeap(128);
        for(i = 0; i < 100; i++){
            insert(heap3,i);
        }
        for(i = 99; i >=0; i--){
            MSSERT_EQU(removeMax(heap3), i, "Node not insert and remove failed");
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
            MSSERT_EQU(removeMax(heap4), i, "Node not insert and remove failed");
        }
        for(i = 10; i < 100; i++){
            insert(heap4,i);
        }
        for(i = 99; i >=0; i--){
            MSSERT_EQU(removeMax(heap4), i, "Node not insert and remove failed");
        }
        free(heap4);
    }

    TEST_CASE("Test can grow capacity"){
        struct MaxHeap* heap5;
        heap5 = mkMaxHeap(128);
        for(i = 0; i < 100; i++){
            MSSERT_EQU(insert(heap5,i), 0, "Node insert resize error");
        }
        grow(heap5);
        MSSERT_EQU(heap5->capacity, 256, "Heap capacity not updated correctly");
        MSSERT_EQU(heap5->size, 100, "Heap size not updated correctly");
        for(i = 99; i >=0; i--){
            MSSERT_EQU(removeMax(heap5), i, "Node not insert and remove failed");
        }
        free(heap5);
    }

    /*TEST_CASE("Test can auto-grow capacity on insert"){
        struct MaxHeap* heap6;
        heap6 = mkMaxHeap(4);
        for(i = 0; i < 16; i++){
            MSSERT_EQU(insert(heap6,i), 0, "Node insert auto-grow error");
            int j;
            for(j = 0; j < heap6->size; j++){
                printf("%d", heap6->data[j]);
                printf("\r\n");
            }
        }
        MSSERT_EQU(heap6->capacity, 16, "Heap capacity not updated correctly");
        MSSERT_EQU(heap6->size, 16, "Heap size not updated correctly");
        for(i = 15; i >=0; i--){
            printf("%d", peakMax(heap6));
            MSSERT_EQU(removeMax(heap6), i, "Node not insert and remove failed");
        }
    }*/

    TEST_CASE("Failures Look Correct"){
        MSSERT_EQU(1, 2, "This assertion should fail");
    }
    END_TESTING();
}