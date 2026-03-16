#include "MaxHeap.h"
#include <stdio.h>
#define NULL 0

void swap(a,b) 
    int* a; 
    int* b;
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

struct MaxHeap* mkMaxHeap(cap) 
    int cap;
{
    struct MaxHeap* heap; heap = alloc(sizeof(*heap));
    heap->capacity = cap;
    heap->size = 0;
    heap->data = alloc(sizeof(*heap->data) * heap->capacity);
    return heap;
}

char grow(heap) 
    struct MaxHeap* heap;
{
    int* dat; dat = alloc(heap->capacity * 2);
    if(dat == NULL){return -1;}
    int i;
    for(i = 0; i < heap->size && heap->data != NULL; i++){
        dat[i] = heap->data[i];
        /*printf("%d\r\n",dat[i]);*/
    }
    /*free(heap->data);*/
    heap->data = dat;
    heap->capacity = 2 * heap->capacity;
    return 0;
}

char insert(heap, num)
    struct MaxHeap* heap;
    int num;
{
    if(heap->size == heap->capacity){
        if(grow(heap) != 0){
            return -1;
        }
    }
    int* dat; dat = heap->data;
    int i; i = heap->size; heap->size++;
    dat[i] = num;
    while(i > 0){
        if(num > dat[(i-1)/2]){
            swap(dat + i, dat + ((i-1)/2));
            i = (i-1) / 2;
        }
        else{break;}
    }
    return 0;
}
int peakMax(heap)
    struct MaxHeap* heap;
{
    if(heap->size == 0 || heap->data == NULL){return -1;}
    return heap->data[0];
}
int removeMax(heap)
    struct MaxHeap* heap;
{
    int returnValue; returnValue = heap->data[0];
    int* dat; dat = heap->data;
    int i; i = 0;
    if(heap->size == 0 || heap->data == NULL){
        return -1; /*do better caller*/
    }
    dat[0] = dat[heap->size - 1]; heap->size--;
    while(i < heap->size){
        int maxIndex; int leftIndex; int rightIndex;
        leftIndex = 2*i + 1;
        rightIndex = 2 * i + 2;
        maxIndex = i;

        if(leftIndex < heap->size && (dat[leftIndex] > dat[rightIndex] || rightIndex >= heap->size)){
            maxIndex = leftIndex;
        }
        else if(rightIndex < heap->size && (dat[rightIndex] > dat[leftIndex] || leftIndex >= heap->size)){
            maxIndex = rightIndex;
        }

        if(maxIndex == i || dat[maxIndex] < dat[i]){break;}
        swap(dat + i, dat + maxIndex);
        i = maxIndex;
    }
    return returnValue;
}