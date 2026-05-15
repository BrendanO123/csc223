#include <stdio.h>
#include "AVLTREE.H"
#include "QUEUE.H"
#define NULL 0

struct AVLTnode* mkAVLTnode(Num) int Num; {
    struct AVLTnode* x;
    x = alloc(sizeof(*x));
    x->num = Num;
    x->left = NULL;
    x->right = NULL;
    x->parent = NULL;
    x->balance = 0;
    return x;
}

void balanceOneNode(tree, node) struct AVLTREE* tree; struct AVLTnode* node; {
    if(node == NULL) return;
    
    /* Left-heavy (balance < -1) */
    if(node->balance < -1){
        /* Check if left child is right-heavy (Left-Right case) */
        if(node->left != NULL && node->left->balance > 0){
            /* Rotate left on left child */
            struct AVLTnode* leftChild; leftChild = node->left;
            struct AVLTnode* leftRightChild; leftRightChild = leftChild->right;
            leftChild->right = leftRightChild->left;
            if(leftRightChild->left != NULL){leftRightChild->left->parent = leftChild;}
            leftRightChild->left = leftChild;
            leftChild->parent = leftRightChild;
            node->left = leftRightChild;
            leftRightChild->parent = node;
            /* Update balance of leftChild */
            leftChild->balance = -1;
        }
        /* Rotate right on node (Left-Left case after potential rebalance) */
        struct AVLTnode* newRoot1; newRoot1 = node->left;
        node->left = newRoot1->right;
        if(newRoot1->right != NULL){newRoot1->right->parent = node;}
        newRoot1->right = node;
        newRoot1->parent = node->parent;
        if(node->parent == NULL){tree->root = newRoot1;}
        else if(node->parent->left == node){node->parent->left = newRoot1;}
        else{node->parent->right = newRoot1;}
        node->parent = newRoot1;
        /* Update balances */
        node->balance = 0;
        newRoot1->balance = 0;
    }
    /* Right-heavy (balance > 1) */
    else if(node->balance > 1){
        /* Check if right child is left-heavy (Right-Left case) */
        if(node->right != NULL && node->right->balance < 0){
            /* Rotate right on right child */
            struct AVLTnode* rightChild; rightChild = node->right;
            struct AVLTnode* rightLeftChild; rightLeftChild = rightChild->left;
            rightChild->left = rightLeftChild->right;
            if(rightLeftChild->right != NULL){rightLeftChild->right->parent = rightChild;}
            rightLeftChild->right = rightChild;
            rightChild->parent = rightLeftChild;
            node->right = rightLeftChild;
            rightLeftChild->parent = node;
            /* Update balance of rightChild */
            rightChild->balance = 1;
        }
        /* Rotate left on node (Right-Right case after potential rebalance) */
        struct AVLTnode* newRoot2; newRoot2 = node->right;
        node->right = newRoot2->left;
        if(newRoot2->left != NULL){newRoot2->left->parent = node;}
        newRoot2->left = node;
        newRoot2->parent = node->parent;
        if(node->parent == NULL){tree->root = newRoot2;}
        else if(node->parent->left == node){node->parent->left = newRoot2;}
        else{node->parent->right = newRoot2;}
        node->parent = newRoot2;
        /* Update balances */
        node->balance = 0;
        newRoot2->balance = 0;
    }
}
void balanceNodes(tree, unbalancedNodes) struct AVLTREE* tree; struct queue* unbalancedNodes; {
    while(unbalancedNodes->size > 0){
        struct AVLTnode* Node; Node = dequeue(unbalancedNodes);
        if(Node->balance < -1 || Node->balance > 1){
            balanceOneNode(tree, Node);
        }
    }
}
struct AVLTREE* mkAVLTree(n) int n; {
    struct AVLTREE* tree; tree = alloc(sizeof(*tree));
    tree->root = mkAVLTnode(n);
    return tree;
}
struct AVLTnode* insert(tree, Num) struct AVLTREE* tree; int Num; {
    struct AVLTnode* newNode; newNode = mkAVLTnode(Num);
    if(tree->root == NULL){
        tree->root = newNode;
        return newNode;
    }
    struct AVLTnode* current; current = tree->root;
    struct queue* unbalancedNodes; unbalancedNodes = mkqueue(NULL);
    dequeue(unbalancedNodes); /* Remove initial NULL value */
    while(1){
        if(Num < current->num){
            current->balance--; /* New node will be added to left subtree, so decrement balance */
            if(current->balance < -1){
                enqueue(unbalancedNodes, current); /* Add unbalanced node to queue */
            }
            if(current->left == NULL){
                current->left = newNode;
                newNode->parent = current;
                break;
            }
            else{current = current->left;}
        }
        else{
            current->balance++; /* New node will be added to right subtree, so increment balance */
            if(current->balance > 1){
                enqueue(unbalancedNodes, current); /* Add unbalanced node to queue */
            }
            if(current->right == NULL){
                current->right = newNode;
                newNode->parent = current;
                break;
            }
            else{current = current->right;}
        }
    }
    balanceNodes(tree, unbalancedNodes);
    dellqueue(unbalancedNodes);
    return newNode;
}
char removeNode(tree, Num) struct AVLTREE* tree; int Num; {
    struct AVLTnode* current; current = tree->root;
    struct queue* unbalancedNodes; unbalancedNodes = mkqueue(NULL);
    dequeue(unbalancedNodes); /* Remove initial NULL value */
    while(current != NULL){
        if(Num < current->num){
            current = current->left; 
            current->balance++;
            if(current->balance > 1){
                enqueue(unbalancedNodes, current);
            }
        }
        else if(Num > current->num){
            current = current->right; 
            current->balance--;
            if(current->balance < -1){
                enqueue(unbalancedNodes, current);
            }
        }
        else{break;}
    }

    if(current == NULL){return -1;}
    if(current->left == NULL && current->right == NULL){
        if(current->parent == NULL){tree->root = NULL;}
        else if(current->parent->left == current){current->parent->left = NULL;}
        else{current->parent->right = NULL;}
    }
    else if(current->left != NULL && current->right != NULL){
        struct AVLTnode* successor; successor = current->right;
        while(successor->left != NULL){successor = successor->left;}
        int temp; temp = successor->num;
        removeNode(tree, successor);
        current->num = temp;
    }
    else{
        struct AVLTnode* child; child = ((current->left != NULL) ? current->left : current->right);
        if(current->parent == NULL){tree->root = child;}
        else if(current->parent->left == current){current->parent->left = child;}
        else{current->parent->right = child;}
        child->parent = current->parent;
    }
    free(current);
    balanceNodes(tree, unbalancedNodes);
    dellqueue(unbalancedNodes);
    return 0;
}
struct AVLTnode* find(tree, Num) struct AVLTREE* tree; int Num; {
    struct AVLTnode* current; current = tree->root;
    while(current != NULL){
        if(Num < current->num){current = current->left;}
        else if(Num > current->num){current = current->right;}
        else{break;}
    }
    return current;
}
int max(tree) struct AVLTREE* tree; {
    if(tree->root == NULL){return -1;}
    struct AVLTnode* current; current = tree->root;
    while(current->right != NULL){current = current->right;}
    return current->num;
}
int min(tree) struct AVLTREE* tree; {
    if(tree->root == NULL){return -1;}
    struct AVLTnode* current; current = tree->root;
    while(current->left != NULL){current = current->left;}
    return current->num;
}
char popMax(tree) struct AVLTREE* tree; {
    return removeNode(tree, max(tree));
}
char popMin(tree) struct AVLTREE* tree; {
    return removeNode(tree, min(tree));
}
void dellTree(tree) struct AVLTREE* tree; {
    if(tree->root == NULL){free(tree); return;}
    struct AVLTnode* current; current = tree->root;
    while(current != NULL){
        if(current->left != NULL){current = current->left;}
        else if(current->right != NULL){current = current->right;}
        else{
            struct AVLTnode* Parent; Parent = current->parent;
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

int height(tree) struct AVLTREE* tree; {
    return heightSubHelper(tree->root);
}
int heightSubHelper(node) struct AVLTnode* node; {
    if(node == NULL){return -1;}
    int leftHeight; leftHeight = height(node->left);
    int rightHeight; rightHeight = height(node->right);
    return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
}