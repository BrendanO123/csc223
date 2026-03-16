struct MaxHeap{
    int size;
    int capacity;
    int* data;
};

struct MaxHeap* mkMaxHeap(int capacity);
char insert(struct MaxHeap* heap, int e);
int peakMax(struct MaxHeap* heap);
int removeMax(struct MaxHeap* heap);
void swap(int* a, int* b);
char grow(struct MaxHeap* heap);