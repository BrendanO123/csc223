struct arrayList {
    int *data;
    int size;
    int capacity;
};

struct arrayList* mkArrayList(int capacity);
char insert(struct arrayList* list, int e);
int get(struct arrayList* list, int index);
int peak(struct arrayList* list);
int removeAt(struct arrayList* list, int index);
char swap(int* a, int* b);
char grow(struct arrayList* list);
void append(struct arrayList* list, int e);