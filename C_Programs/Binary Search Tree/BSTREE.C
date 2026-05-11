#include <stdio.h>
#include "BSTREE.H"
#define NULL 0

struct BSTnode* mkTnode(Num) int Num; {
    struct BSTnode* x;
    x = alloc(sizeof(*x));
    x->num = Num;
    x->left = NULL;
    x->right = NULL;
    x->parent = NULL;
    return x;
}

struct BSTREE* mkBSTree(n) int n; {
    struct BSTREE* tree; tree = alloc(sizeof(*tree));
    tree->root = mkTnode(n);
    return tree;
}
struct BSTnode* insert(tree, Num) struct BSTREE* tree; int Num; {
    struct BSTnode* newNode; newNode = mkTnode(Num);
    if(tree->root == NULL){
        tree->root = newNode;
        return newNode;
    }
    struct BSTnode* current; current = tree->root;
    while(1){
        if(Num < current->num){
            if(current->left == NULL){
                current->left = newNode;
                newNode->parent = current;
                break;
            }
            else{current = current->left;}
        }
        else{
            if(current->right == NULL){
                current->right = newNode;
                newNode->parent = current;
                break;
            }
            else{current = current->right;}
        }
    }
    return newNode;
}
char removeNum(tree, num) struct BSTREE* tree; int num; {
    return removeNode(tree, find(tree, num));
}
char removeNode(tree, BSTNode) struct BSTREE* tree; struct BSTnode* BSTNode; {
    if(BSTNode == NULL){return -1;}
    if(BSTNode->left == NULL && BSTNode->right == NULL){
        if(BSTNode->parent == NULL){tree->root = NULL;}
        else if(BSTNode->parent->left == BSTNode){BSTNode->parent->left = NULL;}
        else{BSTNode->parent->right = NULL;}
    }
    else if(BSTNode->left != NULL && BSTNode->right != NULL){
        struct BSTnode* successor; successor = BSTNode->right;
        while(successor->left != NULL){successor = successor->left;}
        int temp; temp = successor->num;
        removeNode(tree, successor);
        BSTNode->num = temp;
    }
    else{
        struct BSTnode* child; child = ((BSTNode->left != NULL) ? BSTNode->left : BSTNode->right);
        if(BSTNode->parent == NULL){tree->root = child;}
        else if(BSTNode->parent->left == BSTNode){BSTNode->parent->left = child;}
        else{BSTNode->parent->right = child;}
        child->parent = BSTNode->parent;
    }
    free(BSTNode);
    return 0;
}
struct BSTnode* find(tree, Num) struct BSTREE* tree; int Num; {
    struct BSTnode* current; current = tree->root;
    while(current != NULL){
        if(Num < current->num){current = current->left;}
        else if(Num > current->num){current = current->right;}
        else{break;}
    }
    return current;
}
struct BSTnode* maxNode(tree) struct BSTREE* tree; {
    if(tree->root == NULL){return NULL;}
    struct BSTnode* current; current = tree->root;
    while(current->right != NULL){current = current->right;}
    return current;
}
struct BSTnode* minNode(tree) struct BSTREE* tree; {
    if(tree->root == NULL){return NULL;}
    struct BSTnode* current; current = tree->root;
    while(current->left != NULL){current = current->left;}
    return current;
}
int max(tree) struct BSTREE* tree; {
    return (maxNode(tree) != NULL) ? maxNode(tree)->num : -1;
}
int min(tree) struct BSTREE* tree; {
    return (minNode(tree) != NULL) ? minNode(tree)->num : -1;
}
char popMax(tree) struct BSTREE* tree; {
    return removeNode(tree, maxNode(tree));
}
char popMin(tree) struct BSTREE* tree; {
    return removeNode(tree, minNode(tree));
}
void dellTree(tree) struct BSTREE* tree; {
    if(tree->root == NULL){free(tree); return;}
    struct BSTnode* current; current = tree->root;
    while(current != NULL){
        if(current->left != NULL){current = current->left;}
        else if(current->right != NULL){current = current->right;}
        else{
            struct BSTnode* Parent; Parent = current->parent;
            free(current);
            if(Parent != NULL){
                if(Parent->left == current){Parent->left = NULL;}
                else{Parent->right = NULL;}
            }
            current = Parent;
        }
    }
    free(tree);
}