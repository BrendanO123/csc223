#include "QUEUE.H"
#include "BDSCTEST.H"
#define NULL 0

main() {
    START_TESTING("QUEUE.C");

    TEST_CASE("Test can create node") {
        struct node* mynode;
        mynode = mkqnode(42);
        MSSERT_EQU(mynode->num, 42, "Node value not set correctly");
        MSSERT_EQU(mynode->next, NULL, "Node next pointer not initialized to NULL");
        free(mynode);
    }
    TEST_CASE("Test can create queue") {
        struct queue* q1;
        q1 = mkqueue(42);
        MSSERT_EQU(q1->head->num, 42, "Queue head value not set correctly");
        MSSERT_EQU(q1->head->next, NULL, "Queue head next pointer not initialized to NULL");
        MSSERT_EQU(q1->tail, q1->head, "Queue tail pointer not set correctly");
        MSSERT_EQU(q1->size, 1, "Queue size not set correctly");
        dellqueue(q1);
    }
    TEST_CASE("Test can enqueue and dequeue") {
        struct queue* q2;
        q2 = mkqueue(42);
        enqueue(q2, 12);
        enqueue(q2, 54);
        MSSERT_EQU(dequeue(q2), 42, "Dequeue did not return correct value");
        MSSERT_EQU(dequeue(q2), 12, "Dequeue did not return correct value");
        MSSERT_EQU(dequeue(q2), 54, "Dequeue did not return correct value");
        MSSERT_EQU(dequeue(q2), -1, "Dequeue on empty queue should return -1");
        dellqueue(q2);
    }
    TEST_CASE("Test can peak") {
        struct queue* q3;
        q3 = mkqueue(42);
        MSSERT_EQU(peak(q3), 42, "Peak did not return correct value");
        enqueue(q3, 12);
        MSSERT_EQU(peak(q3), 42, "Peak should not change after enqueue");
        dequeue(q3);
        MSSERT_EQU(peak(q3), 12, "Peak did not return correct value after dequeue");
        dequeue(q3);
        MSSERT_EQU(peak(q3), -1, "Peak on empty queue should return -1");
        dellqueue(q3);
    }

    END_TESTING();
}