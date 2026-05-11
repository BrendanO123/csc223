struct qnode{
    char* data;
    struct qnode* next;
};

struct queue{
    struct qnode* head;
    struct qnode* tail;
    int size;
};

struct queue* mkqueueRaw(char* data);
struct qnode* mkqnodeRaw(char* data);
struct queue* mkqueue(int data);
struct qnode* mkqnode(int data);
void dellqueue(struct queue* q);
void enqueue(struct queue* q, int data);
int dequeue(struct queue* q);
void enqueueRaw(struct queue* q, char* data);
char* dequeueRaw(struct queue* q);
int peak(struct queue* q);
char* peakRaw(struct queue* q);