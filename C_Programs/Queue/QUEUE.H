struct node{
    int num;
    struct node* next;
};

struct queue{
    struct node* head;
    struct node* tail;
    int size;
};

struct queue* mkqueue(int num);
struct node* mkqnode(int num);
void dellqueue(struct queue* q);
void enqueue(struct queue* q, int num);
int dequeue(struct queue* q);
int peak(struct queue* q);