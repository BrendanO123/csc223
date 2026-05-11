#include <stdio.h>
#include "QUEUE.H"
#define NULL 0

struct node* mkqnode(Num) int Num; {
    struct node* newNode; newNode = alloc(sizeof(*newNode));
    newNode->num = Num;
    newNode->next = NULL;
    return newNode;
}
struct queue* mkqueue(Num) int Num; {
    struct queue* q; q = alloc(sizeof(*q));
    struct node* newNode; newNode = mkqnode(Num);
    q->head = newNode;
    q->tail = newNode;
    q->size = 1;
    return q;
}
void dellqueue(q) struct queue* q; {
    struct node* Next; struct node* current;
    current = q->head;
    while(current != NULL){
        Next = current->next;
        free(current);
        current = Next; 
    }
    free(q);
}
void enqueue(q, num) struct queue* q; int num; {
    struct node* newNode; newNode = mkqnode(num);
    if(q->head == NULL){q->head = newNode;}
    else{q->tail->next = newNode;}
    q->tail = newNode;
    q->size++;
}
int dequeue(q) struct queue* q; {
    if(q->head == NULL){return -1;}
    struct node* oldHead; oldHead = q->head;
    int Num; Num = oldHead->num;
    q->head = oldHead->next;
    free(oldHead);
    q->size--;
    if(q->size == 0){q->tail = NULL;}
    return Num;
}
int peak(q) struct queue* q; {
    if(q->head == NULL){return -1;}
    return q->head->num;
}