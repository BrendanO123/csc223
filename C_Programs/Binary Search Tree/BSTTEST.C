#include "BSTREE.H"
#include "BDSCTEST.H"
#define NULL 0

main() {
    START_TESTING("BSTREE.C");

    TEST_CASE("Test can create BSTnode") {
        struct BSTnode* mynode;
        mynode = mkTnode(42);
        MSSERT_EQU(mynode->num, 42, "BSTNode value not set correctly");
        MSSERT_EQU(mynode->left, NULL, "BSTNode left pointer not initialized to NULL");
        MSSERT_EQU(mynode->right, NULL, "BSTNode right pointer not initialized to NULL");
        MSSERT_EQU(mynode->parent, NULL, "BSTNode parent pointer not initialized to NULL");
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
        struct BSTnode* node1; node1 = insert(tree2, 12);
        struct BSTnode* node2; node2 = insert(tree2, 54);
        MSSERT_EQU(node1->num, 12, "BSTNode value not set correctly");
        MSSERT_EQU(node1->left, NULL, "BSTNode left pointer not initialized to NULL");
        MSSERT_EQU(node1->right, NULL, "BSTNode right pointer not initialized to NULL");
        MSSERT_EQU(node1->parent, tree2->root, "BSTNode parent pointer not set correctly");
        MSSERT_EQU(node2->num, 54, "BSTNode value not set correctly");
        MSSERT_EQU(node2->left, NULL, "BSTNode left pointer not initialized to NULL");
        MSSERT_EQU(node2->right, NULL, "BSTNode right pointer not initialized to NULL");
        MSSERT_EQU(node2->parent, tree2->root, "BSTNode parent pointer not set correctly");
        MSSERT_EQU(tree2->root->left, node1, "Tree root left pointer not set correctly");
        MSSERT_EQU(tree2->root->right, node2, "Tree root right pointer not set correctly");
        dellTree(tree2);
    }
    TEST_CASE("Test can remove nodes") {
        struct BSTREE* tree3;
        tree3 = mkBSTree(42);
        struct BSTnode* node3; node3 = insert(tree3, 12);
        struct BSTnode* node4; node4 = insert(tree3, 54);
        MSSERT_EQU(removeNode(tree3, node3), 0, "BSTNode not removed correctly");
        MSSERT_EQU(tree3->root->left, NULL, "BSTNode left pointer not set to NULL after removal");
        MSSERT_EQU(removeNode(tree3, node4), 0, "BSTNode not removed correctly");
        MSSERT_EQU(tree3->root->right, NULL, "BSTNode right pointer not set to NULL after removal");
        dellTree(tree3);
    }
    TEST_CASE("Test can remove nodes by value") {
        struct BSTREE* tree4;
        tree4 = mkBSTree(42);
        insert(tree4, 12);
        insert(tree4, 54);
        MSSERT_EQU(removeNum(tree4, 12), 0, "BSTNode not removed correctly");
        MSSERT_EQU(tree4->root->left, NULL, "BSTNode left pointer not set to NULL after removal");
        MSSERT_EQU(removeNum(tree4, 54), 0, "BSTNode not removed correctly");
        MSSERT_EQU(tree4->root->right, NULL, "BSTNode right pointer not set to NULL after removal");
        dellTree(tree4);
    }
    TEST_CASE("Test can find nodes") {
        struct BSTREE* tree5;
        tree5 = mkBSTree(42);
        struct BSTnode* node5; node5 = insert(tree5, 12);
        struct BSTnode* node6; node6 = insert(tree5, 54);
        MSSERT_EQU(find(tree5, 12)->num, 12, "BSTNode not found correctly");
        MSSERT_EQU(find(tree5, 54)->num, 54, "BSTNode not found correctly");
        MSSERT_EQU(find(tree5, 100), NULL, "Nonexistent BSTnode should return NULL");
        MSSERT_EQU(find(tree5, 12), node5, "BSTNode not found correctly");
        MSSERT_EQU(find(tree5, 54), node6, "BSTNode not found correctly");
        dellTree(tree5);
    }
    TEST_CASE("Test can find min and max nodes") {
        struct BSTREE* tree6;
        tree6 = mkBSTree(42);
        struct BSTnode* node7; node7 = insert(tree6, 12);
        struct BSTnode* node8; node8 = insert(tree6, 54);
        MSSERT_EQU(minNode(tree6), node7, "Min BSTnode not found correctly");
        MSSERT_EQU(maxNode(tree6), node8, "Max BSTnode not found correctly");
        MSSERT_EQU(minNode(tree6)->num, 12, "Min BSTnode not found correctly");
        MSSERT_EQU(maxNode(tree6)->num, 54, "Max BSTnode not found correctly");
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
        MSSERT_EQU(popMin(tree8), 0, "Min BSTnode not popped correctly");
        MSSERT_EQU(tree8->root->left, NULL, "BSTNode left pointer not set to NULL after popping min");
        MSSERT_EQU(popMax(tree8), 0, "Max BSTnode not popped correctly");
        MSSERT_EQU(tree8->root->right, NULL, "BSTNode right pointer not set to NULL after popping max");
        dellTree(tree8);
    }
    TEST_CASE("Keeps Sorted for Many Nodes"){
        struct BSTREE* tree9;
        tree9 = mkBSTree(42);
        insert(tree9, 12);
        insert(tree9, 54);
        insert(tree9, 6);
        insert(tree9, 18);
        insert(tree9, 48);
        insert(tree9, 60);
        removeNum(tree9, 54);
        removeNum(tree9, 12);
        removeNum(tree9, 60);
        insert(tree9, 20);
        insert(tree9, 47);
        insert(tree9, 5);
        MSSERT_EQU(find(tree9, 6)->num, 6, "BSTNode not found correctly");
        MSSERT_EQU(find(tree9, 18)->num, 18, "BSTNode not found correctly");
        MSSERT_EQU(find(tree9, 48)->num, 48, "BSTNode not found correctly");
        MSSERT_EQU(find(tree9, 47)->num, 47, "BSTNode not found correctly");
        MSSERT_EQU(find(tree9, 5)->num, 5, "BSTNode not found correctly");
        MSSERT_EQU(find(tree9, 20)->num, 20, "BSTNode not found correctly");
        MSSERT_EQU(find(tree9, 54), NULL, "Nonexistent BSTnode should return NULL");
        MSSERT_EQU(max(tree9), 48, "Max value not found correctly");
        MSSERT_EQU(min(tree9), 5, "Min value not found correctly");
        dellTree(tree9);
    }

    END_TESTING();
}