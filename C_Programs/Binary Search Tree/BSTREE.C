#include <stdio.h>
#include "BSTREE.H"
#define NULL 0

struct node* mkTnode(Num) int Num; {
    struct node* x;
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
struct node* insert(tree, Num) struct BSTREE* tree; int Num; {
    struct node* newNode; newNode = mkTnode(Num);
    if(tree->root == NULL){
        tree->root = newNode;
        return newNode;
    }
    struct node* current; current = tree->root;
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
char removeNode(tree, Node) struct BSTREE* tree; struct node* Node; {
    if(Node == NULL){return -1;}
    if(Node->left == NULL && Node->right == NULL){
        if(Node->parent == NULL){tree->root = NULL;}
        else if(Node->parent->left == Node){Node->parent->left = NULL;}
        else{Node->parent->right = NULL;}
    }
    else if(Node->left != NULL && Node->right != NULL){
        struct node* successor; successor = Node->right;
        while(successor->left != NULL){successor = successor->left;}
        int temp; temp = successor->num;
        removeNode(tree, successor);
        Node->num = temp;
    }
    else{
        struct node* child; child = ((Node->left != NULL) ? Node->left : Node->right);
        if(Node->parent == NULL){tree->root = child;}
        else if(Node->parent->left == Node){Node->parent->left = child;}
        else{Node->parent->right = child;}
        child->parent = Node->parent;
    }
    free(Node);
    return 0;
}
struct node* find(tree, Num) struct BSTREE* tree; int Num; {
    struct node* current; current = tree->root;
    while(current != NULL){
        if(Num < current->num){current = current->left;}
        else if(Num > current->num){current = current->right;}
        else{break;}
    }
    return current;
}
struct node* maxNode(tree) struct BSTREE* tree; {
    if(tree->root == NULL){return NULL;}
    struct node* current; current = tree->root;
    while(current->right != NULL){current = current->right;}
    return current;
}
struct node* minNode(tree) struct BSTREE* tree; {
    if(tree->root == NULL){return NULL;}
    struct node* current; current = tree->root;
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
    struct node* current; current = tree->root;
    while(current != NULL){
        if(current->left != NULL){current = current->left;}
        else if(current->right != NULL){current = current->right;}
        else{
            struct node* Parent; Parent = current->parent;
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