struct node{
    int num;
    struct node* left;
    struct node* right;
    struct node* parent;
};

struct BSTREE{
    struct node* root;
};

struct node* mknode(int num);
struct BSTREE* mkBSTree(int num);
struct node* insert(struct BSTREE* tree, int num);
char removeNode(struct BSTREE* tree, struct node* node);
char removeNum(struct BSTREE* tree, int num);
struct node* find(struct BSTREE* tree, int num);
struct node* minNode(struct BSTREE* tree);
struct node* maxNode(struct BSTREE* tree);
int max(struct BSTREE* tree);
int min(struct BSTREE* tree);
char popMax(struct BSTREE* tree);
char popMin(struct BSTREE* tree);
void dellTree(struct BSTREE* tree);
