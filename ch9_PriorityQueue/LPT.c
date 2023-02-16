#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct {
    int id;
    int availTime;
} element;

typedef struct heapTree {
    element heap[MAX_ELEMENT];
    int heapSize;
} heapTree;

heapTree* create()
{
    return (heapTree*)malloc(sizeof(heapTree));
}

void init(heapTree* h)
{
    h->heapSize = 0;
}

void insert_min_heap(heapTree* h, element data)
{
    int i = ++(h->heapSize);
    h->heap[i] = data;
    int parent = i / 2;

    while (parent >= 1 && (h->heap[parent].availTime > data.availTime)) {
        h->heap[i] = h->heap[parent];

        i = parent;
        parent /= 2;
    }

    h->heap[i] = data;
}

element delete_min_heap(heapTree* h)
{
    int parent, child;

    element item, temp;

    temp = h->heap[h->heapSize--]; // 말단
    item = h->heap[1]; // 삭제될 최상위 노드

    h->heap[1] = temp;
    parent = 1;
    child = 2;

    while (child <= h->heapSize) 
    {
        if (child < h->heapSize) {
            if (h->heap[child].availTime > h->heap[child+1].availTime) child++;
        }

        if (temp.availTime <= h->heap[child].availTime) break;

        h->heap[parent] = h->heap[child];

        parent = child;
        child *= 2;
    }

    h->heap[parent] = temp;
    return item;
}

#define JOBS 7
#define MACHINES 3

int main(void) 
{
    int jobs[JOBS] = {8,7,6,5,3,2,1};
    element m = {0,0};
    heapTree* h;
    h = create();
    init(h);

    for (int i = 0; i<MACHINES; i++)
    {
        m.id = i + 1;
        m.availTime = 0;
        insert_min_heap(h, m);
    }

    for (int i = 0; i <JOBS; i++)
    {
        m = delete_min_heap(h);
        printf("allocate -JOB %d- from time %d ~ to %d to machine no.%d\n", 
        i, m.availTime, m.availTime + jobs[i] - 1, m.id);

        m.availTime += jobs[i];
        insert_min_heap(h,m);
    }
    return 0;
}



