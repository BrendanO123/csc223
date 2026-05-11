#include "BSTREE.H"
#include "BDSCTEST.H"
#define NULL 0

main() {
    START_TESTING("BSTREE.C");

    TEST_CASE("Test can create node") {
        struct node* mynode;
        mynode = mknode(42);
        MSSERT_EQU(mynode->num, 42, "Node value not set correctly");
        MSSERT_EQU(mynode->left, NULL, "Node left pointer not initialized to NULL");
        MSSERT_EQU(mynode->right, NULL, "Node right pointer not initialized to NULL");
        MSSERT_EQU(mynode->parent, NULL, "Node parent pointer not initialized to NULL");
        free(mynode);
    }
    TEST_CASE("Test can create tree") {
        struct BSTREE* tree1;
        tree1 = mkBSTree(42);
        MSSERT_EQU(tree1->root->num, 42, "Tree root value not set correctly");
        MSSERT_EQU(tree1->root->left, NULL, "Tree root left pointer not initialized to NULL");
        MSSERT_EQU(tree1->root->right, NULL, "Tree root right pointer not initialized to NULL");
        MSSERT_EQU(tree1->root->parent, NULL, "Tree root parent pointer not initialized to NULL");
        dellTree(tree1);
    }
    TEST_CASE("Test can insert nodes") {
        struct BSTREE* tree2;
        tree2 = mkBSTree(42);
        struct node* node1; node1 = insert(tree2, 12);
        struct node* node2; node2 = insert(tree2, 54);
        MSSERT_EQU(node1->num, 12, "Node value not set correctly");
        MSSERT_EQU(node1->left, NULL, "Node left pointer not initialized to NULL");
        MSSERT_EQU(node1->right, NULL, "Node right pointer not initialized to NULL");
        MSSERT_EQU(node1->parent, tree2->root, "Node parent pointer not set correctly");
        MSSERT_EQU(node2->num, 54, "Node value not set correctly");
        MSSERT_EQU(node2->left, NULL, "Node left pointer not initialized to NULL");
        MSSERT_EQU(node2->right, NULL, "Node right pointer not initialized to NULL");
        MSSERT_EQU(node2->parent, tree2->root, "Node parent pointer not set correctly");
        MSSERT_EQU(tree2->root->left, node1, "Tree root left pointer not set correctly");
        MSSERT_EQU(tree2->root->right, node2, "Tree root right pointer not set correctly");
        dellTree(tree2);
    }
    TEST_CASE("Test can remove nodes") {
        struct BSTREE* tree3;
        tree3 = mkBSTree(42);
        struct node* node3; node3 = insert(tree3, 12);
        struct node* node4; node4 = insert(tree3, 54);
        MSSERT_EQU(removeNode(tree3, node3), 0, "Node not removed correctly");
        MSSERT_EQU(tree3->root->left, NULL, "Node left pointer not set to NULL after removal");
        MSSERT_EQU(removeNode(tree3, node4), 0, "Node not removed correctly");
        MSSERT_EQU(tree3->root->right, NULL, "Node right pointer not set to NULL after removal");
        dellTree(tree3);
    }
    TEST_CASE("Test can remove nodes by value") {
        struct BSTREE* tree4;
        tree4 = mkBSTree(42);
        insert(tree4, 12);
        insert(tree4, 54);
        MSSERT_EQU(removeNum(tree4, 12), 0, "Node not removed correctly");
        MSSERT_EQU(tree4->root->left, NULL, "Node left pointer not set to NULL after removal");
        MSSERT_EQU(removeNum(tree4, 54), 0, "Node not removed correctly");
        MSSERT_EQU(tree4->root->right, NULL, "Node right pointer not set to NULL after removal");
        dellTree(tree4);
    }
    TEST_CASE("Test can find nodes") {
        struct BSTREE* tree5;
        tree5 = mkBSTree(42);
        struct node* node5; node5 = insert(tree5, 12);
        struct node* node6; node6 = insert(tree5, 54);
        MSSERT_EQU(find(tree5, 12)->num, 12, "Node not found correctly");
        MSSERT_EQU(find(tree5, 54)->num, 54, "Node not found correctly");
        MSSERT_EQU(find(tree5, 100), NULL, "Nonexistent node should return NULL");
        MSSERT_EQU(find(tree5, 12), node5, "Node not found correctly");
        MSSERT_EQU(find(tree5, 54), node6, "Node not found correctly");
        dellTree(tree5);
    }
    TEST_CASE("Test can find min and max nodes") {
        struct BSTREE* tree6;
        tree6 = mkBSTree(42);
        struct node* node7; node7 = insert(tree6, 12);
        struct node* node8; node8 = insert(tree6, 54);
        MSSERT_EQU(minNode(tree6), node7, "Min node not found correctly");
        MSSERT_EQU(maxNode(tree6), node8, "Max node not found correctly");
        MSSERT_EQU(minNode(tree6)->num, 12, "Min node not found correctly");
        MSSERT_EQU(maxNode(tree6)->num, 54, "Max node not found correctly");
        dellTree(tree6);
    }
    TEST_CASE("Test can find min and max values") {
        struct BSTREE* tree7;
        tree7 = mkBSTree(42);
        insert(tree7, 12);
        insert(tree7, 54);
        MSSERT_EQU(min(tree7), 12, "Min value not found correctly");
        MSSERT_EQU(max(tree7), 54, "Max value not found correctly");
        dellTree(tree7);
    }
    TEST_CASE("Test can pop min and max nodes") {
        struct BSTREE* tree8;
        tree8 = mkBSTree(42);
        insert(tree8, 12);
        insert(tree8, 54);
        MSSERT_EQU(popMin(tree8), 0, "Min node not popped correctly");
        MSSERT_EQU(tree8->root->left, NULL, "Node left pointer not set to NULL after popping min");
        MSSERT_EQU(popMax(tree8), 0, "Max node not popped correctly");
        MSSERT_EQU(tree8->root->right, NULL, "Node right pointer not set to NULL after popping max");
        dellTree(tree8);
    }

    END_TESTING();
}