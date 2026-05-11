struct BSTnode{
    int num;
    struct BSTnode* left;
    struct BSTnode* right;
    struct BSTnode* parent;
};

struct BSTREE{
    struct BSTnode* root;
};

struct BSTnode* mkTnode(int num);
struct BSTREE* mkBSTree(int num);
struct BSTnode* insert(struct BSTREE* tree, int num);
char removeNode(struct BSTREE* tree, struct BSTnode* BSTnode);
char removeNum(struct BSTREE* tree, int num);
struct BSTnode* find(struct BSTREE* tree, int num);
struct BSTnode* minNode(struct BSTREE* tree);
struct BSTnode* maxNode(struct BSTREE* tree);
int max(struct BSTREE* tree);
int min(struct BSTREE* tree);
char popMax(struct BSTREE* tree);
char popMin(struct BSTREE* tree);
void dellTree(struct BSTREE* tree);
