#include <stdio.h>
#include "QUEUE.H"
#define NULL 0

struct qnode* mkqnodeRaw(Data) char* Data; {
    struct qnode* newNode; newNode = alloc(sizeof(*newNode));
    newNode->data = Data;
    newNode->next = NULL;
    return newNode;
}
struct qnode* mkqnode(Num) int Num; {
    struct qnode* newNode; newNode = alloc(sizeof(*newNode));
    newNode->data = NULL + Num;
    newNode->next = NULL;
    return newNode;
}
struct queue* mkqueueRaw(data) char* data; {
    struct queue* q; q = alloc(sizeof(*q));
    struct qnode* newNode; newNode = mkqnodeRaw(data);
    q->head = newNode;
    q->tail = newNode;
    q->size = 1;
    return q;
}
struct queue* mkqueue(Num) int Num; {
    struct queue* q; q = alloc(sizeof(*q));
    struct qnode* newNode; newNode = mkqnode(Num);
    q->head = newNode;
    q->tail = newNode;
    q->size = 1;
    return q;
}

void dellqueue(q) struct queue* q; {
    struct qnode* Next; struct qnode* current;
    current = q->head;
    while(current != NULL){
        Next = current->next;
        free(current);
        current = Next; 
    }
    free(q);
}

void enqueueRaw(q, data) struct queue* q; char* data; {
    struct qnode* newNode; newNode = mkqnodeRaw(data);
    if(q->head == NULL){q->head = newNode;}
    else{q->tail->next = newNode;}
    q->tail = newNode;
    q->size++;
}
char* dequeueRaw(q) struct queue* q; {
    if(q->head == NULL){return NULL;}
    struct qnode* oldHead; oldHead = q->head;
    char* Data; Data = oldHead->data;
    q->head = oldHead->next;
    free(oldHead);
    q->size--;
    if(q->size == 0){q->tail = NULL;}
    return Data;
}
void enqueue(q, num) struct queue* q; int num; {
    enqueueRaw(q, (NULL + num));
}
int dequeue(q) struct queue* q; {
    if(q->head == NULL){return -1;}
    return 0 + dequeueRaw(q);
}

char* peakRaw(q) struct queue* q; {
    if(q->head == NULL){return NULL;}
    return q->head->data;
}
int peak(q) struct queue* q; {
    if(q->head == NULL){return -1;}
    return 0 + q->head->data;
}