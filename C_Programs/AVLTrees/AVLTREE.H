struct AVLTnode{
    int num;
    char balance;
    struct AVLTnode* left;
    struct AVLTnode* right;
    struct AVLTnode* parent;
};

struct AVLTREE{
    struct AVLTnode* root;
};

struct AVLTnode* mkAVLTnode(int num);
struct AVLTREE* mkAVLTree(int num);
void balanceOneNode(struct AVLTREE* tree, struct AVLTnode* node);
void balanceNodes(struct AVLTREE* tree, struct queue* unbalancedNodes);
struct AVLTnode* insert(struct AVLTREE* tree, int num);
struct AVLTnode* find(struct AVLTREE* tree, int num);
int max(struct AVLTREE* tree);
int min(struct AVLTREE* tree);
char popMax(struct AVLTREE* tree);
char popMin(struct AVLTREE* tree);
char removeNode(struct AVLTREE* tree, int num);
void dellTree(struct AVLTREE* tree);