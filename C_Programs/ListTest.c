#include "LINKLIST.H"
#include "BDSCTEST.H"
#define NULL 0

main() {
    START_TESTING("LINKLIST.C");

    TEST_CASE("Test can create node") {
        struct node* mynode;
        mynode = mknode(42);
        MSSERT_EQU(mynode->num, 42, "Node value not set correctly");
        MSSERT_EQU(mynode->next, NULL, "Node next pointer not initialized to NULL");
    }

    TEST_CASE("Test dellst"){
        struct node* list;
        list = mknode(42);
        struct node* mynode1; mynode1 = mknode(12);
        list->next = mynode1;

        MSSERT_EQU(list->num, 42, "Node value not set correctly");
        MSSERT_EQU(list->next, mynode1, "Node next pointer not set correctly");
        MSSERT_EQU(mynode1->num, 12, "Node value not set correctly");
        MSSERT_EQU(mynode1->next, NULL, "Node next pointer not initialized to NULL");

        endListAtNode(list);
        MSSERT_EQU(list->next, NULL, "List not terminated correctly");

        dellst(&list);
        MSSERT_EQU(list, NULL, "List not deleted correctly");
    }

    END_TESTING();
}