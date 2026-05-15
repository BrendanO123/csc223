#include "BDSCTEST.H"
#include "AVLTREE.H"
#define NULL 0

main() {
    START_TESTING("AVLTREE.C");

    TEST_CASE("Test can create AVLTnode") {
        struct AVLTnode* mynode;
        mynode = mkAVLTnode(42);
        MSSERT_EQU(mynode->num, 42, "AVLTnode value not set correctly");
        MSSERT_EQU(mynode->balance, 0, "AVLTnode balance not initialized to 0");
        MSSERT_EQU(mynode->left, NULL, "AVLTnode left pointer not initialized to NULL");
        MSSERT_EQU(mynode->right, NULL, "AVLTnode right pointer not initialized to NULL");
        MSSERT_EQU(mynode->parent, NULL, "AVLTnode parent pointer not initialized to NULL");
        free(mynode);
    }
    TEST_CASE("Test can create tree") {
        struct AVLTREE* tree1;
        tree1 = mkAVLTree(42);
        MSSERT_EQU(tree1->root->num, 42, "Tree root value not set correctly");
        MSSERT_EQU(tree1->root->balance, 0, "Tree root balance not initialized to 0");
        MSSERT_EQU(tree1->root->left, NULL, "Tree root left pointer not initialized to NULL");
        MSSERT_EQU(tree1->root->right, NULL, "Tree root right pointer not initialized to NULL");
        MSSERT_EQU(tree1->root->parent, NULL, "Tree root parent pointer not initialized to NULL");
        dellTree(tree1);
    }
    TEST_CASE("Test can insert nodes") {
        struct AVLTREE* tree2;
        tree2 = mkAVLTree(42);
        struct AVLTnode* node1; node1 = insert(tree2, 12);
        struct AVLTnode* node2; node2 = insert(tree2, 54);
        MSSERT_EQU(node1->num, 12, "AVLTnode value not set correctly");
        MSSERT_EQU(node1->balance, 0, "AVLTnode balance not initialized to 0");
        MSSERT_EQU(node1->left, NULL, "AVLTnode left pointer not initialized to NULL");
        MSSERT_EQU(node1->right, NULL, "AVLTnode right pointer not initialized to NULL");
        MSSERT_EQU(node1->parent, tree2->root, "AVLTnode parent pointer not set correctly");
        MSSERT_EQU(node2->num, 54, "AVLTnode value not set correctly");
        MSSERT_EQU(node2->balance, 0, "AVLTnode balance not initialized to 0");
        MSSERT_EQU(node2->left, NULL, "AVLTnode left pointer not initialized to NULL");
        MSSERT_EQU(node2->right, NULL, "AVLTnode right pointer not initialized to NULL");
        MSSERT_EQU(node2->parent, tree2->root, "AVLTnode parent pointer not set correctly");
        MSSERT_EQU(tree2->root->left, node1, "Tree root left pointer not set correctly");
        MSSERT_EQU(tree2->root->right, node2, "Tree root right pointer not set correctly");
        dellTree(tree2);
    }
    TEST_CASE("Keeps Balanced for Many Nodes"){
        struct AVLTREE* tree3;
        tree3 = mkAVLTree(42);
        insert(tree3, 12);
        insert(tree3, 54);
        insert(tree3, 6);
        insert(tree3, 18);
        insert(tree3, 48);
        insert(tree3, 60);
        MSSERT_EQU(tree3->root->num, 42, "Tree root value not correct after multiple insertions");
        MSSERT_EQU(tree3->root->balance, 0, "Tree root balance not correct after multiple insertions");
        MSSERT_EQU(tree3->root->left->num, 12, "Tree root left child value not correct after multiple insertions");
        MSSERT_EQU(tree3->root->left->balance, 0, "Tree root left child balance not correct after multiple insertions");
        MSSERT_EQU(tree3->root->right->num, 54, "Tree root right child value not correct after multiple insertions");
        MSSERT_EQU(tree3->root->right->balance, 0, "Tree root right child balance not correct after multiple insertions");
        MSSERT_EQU(tree3->root->left->left->num, 6, "Tree root left-left grandchild value not correct after multiple insertions");
        MSSERT_EQU(tree3->root->left->left->balance, 0, "Tree root left-left grandchild balance not correct after multiple insertions");
        MSSERT_EQU(tree3->root->left->right->num, 48, "Tree root left-right grandchild value not correct after multiple insertions");
        MSSERT_EQU(tree3->root->left->right->balance, 0, "Tree root left-right grandchild balance not correct after multiple insertions");
        MSSERT_EQU(tree3->root->right->left->num, 18, "Tree root right-left grandchild value not correct after multiple insertions");
        MSSERT_EQU(tree3->root->right->left->balance, 0, "Tree root right-left grandchild balance not correct after multiple insertions");
        MSSERT_EQU(tree3->root->right->right->num, 60, "Tree root right-right grandchild value not correct after multiple insertions");
        MSSERT_EQU(tree3->root->right->right->balance, 0, "Tree root right-right grandchild balance not correct after multiple insertions");
        dellTree(tree3);
    }
    TEST_CASE("Test can find nodes") {
        struct AVLTREE* tree4;
        tree4 = mkAVLTree(42);
        struct AVLTnode* node3; node3 = insert(tree4, 12);
        struct AVLTnode* node4; node4 = insert(tree4, 54);
        MSSERT_EQU(find(tree4, 12)->num, 12, "AVLTnode not found correctly");
        MSSERT_EQU(find(tree4, 54)->num, 54, "AVLTnode not found correctly");
        MSSERT_EQU(find(tree4, 100), NULL, "Nonexistent AVLTnode should return NULL");
        dellTree(tree4);
    }
    TEST_CASE("Test can find min and max values") {
        struct AVLTREE* tree5;
        tree5 = mkAVLTree(42);
        insert(tree5, 12);
        insert(tree5, 54);
        MSSERT_EQU(min(tree5), 12, "Min value not found correctly");
        MSSERT_EQU(max(tree5), 54, "Max value not found correctly");
        dellTree(tree5);
    }
    TEST_CASE("Test can remove nodes") {
        struct AVLTREE* tree6;
        tree6 = mkAVLTree(42);
        struct AVLTnode* node5; node5 = insert(tree6, 12);
        struct AVLTnode* node6; node6 = insert(tree6, 54);
        MSSERT_EQU(removeNode(tree6, 12), 0, "AVLTnode not removed correctly");
        MSSERT_EQU(tree6->root->left, NULL, "AVLTnode left pointer not set to NULL after removal");
        MSSERT_EQU(removeNode(tree6, 54), 0, "AVLTnode not removed correctly");
        MSSERT_EQU(tree6->root->right, NULL, "AVLTnode right pointer not set to NULL after removal");
        dellTree(tree6);
    }
    TEST_CASE("Keeps Sorted for many Nodes"){
        struct AVLTREE* tree7;
        tree7 = mkAVLTree(42);
        insert(tree7, 12);
        insert(tree7, 54);
        insert(tree7, 6);
        insert(tree7, 18);
        insert(tree7, 48);
        insert(tree7, 60);
        char removed; removed = removeNode(tree7, 42);
        MSSERT_EQU(removed, 0, "AVLTnode not removed correctly");
        MSSERT_EQU(find(tree7, 42), NULL, "Removed AVLTnode should not be found");
        MSSERT_EQU(min(tree7), 6, "Min value not found correctly after removal");
        MSSERT_EQU(max(tree7), 60, "Max value not found correctly after removal");
        removeNode(tree7, 12);
        MSSERT_EQU(find(tree7, 12), NULL, "Removed AVLTnode should not be found");
        MSSERT_EQU(min(tree7), 6, "Min value not found correctly after removal");
        removeNode(tree7, 6);
        MSSERT_EQU(min(tree7), 18, "Min value not found correctly after removal");
        removeNode(tree7, 54);
        removeNode(tree7, 60);
        MSSERT_EQU(max(tree7), 18, "Max value not found correctly after removal");
        dellTree(tree7);
    }
    END_TESTING();
}