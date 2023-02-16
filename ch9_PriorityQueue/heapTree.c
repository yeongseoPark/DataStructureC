#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct {
    int key;
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

void insert_max_heap(heapTree* h, element data)
{
    int i = ++(h->heapSize);
    h->heap[i] = data;
    int parent = i / 2;

    while (parent >= 1 && (h->heap[parent].key < data.key)) {
        h->heap[i] = h->heap[parent];

        i = parent;
        parent /= 2;
    }

    h->heap[i] = data;
}

element delete_max_heap(heapTree* h)
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
            if (h->heap[child].key < h->heap[child+1].key) child++;
        }

        if (temp.key >= h->heap[child].key) break;

        h->heap[parent] = h->heap[child];

        parent = child;
        child *= 2;
    }

    h->heap[parent] = temp;
    return item;
}

element delete_some_heap(heapTree* h, element target)
{
    int i;
    int p, c;
    element deleted;
    for (i = 1; i <= h->heapSize; i++) {
        if (h->heap[i].key == target.key) {
            deleted = h->heap[i];
            p = i;
            c = p*2;
            break;
        }
    }

    int temp = h->heap[h->heapSize--].key;
    while (c<=h->heapSize) {
        if (c < h->heapSize) {
            if (h->heap[c].key < h->heap[c+1].key) 
                c++;
        }

        if (temp > h->heap[c].key)
            break;
        
        h->heap[p] = h->heap[c];
        p = c;
        c *= 2;
    }

    h->heap[p].key = temp;
    return deleted;
}

void heap_sort(element a[], int n) // n은 배열의 크기
/* n개의 요소를 삽입 - 삭제하므로 O(nlogn)*/
{
    int i;
    heapTree* h = create();
    init(h);

    for (i = 0; i < n; i++)
        insert_max_heap(h, a[i]);
    
    for (i = n-1; i >= 0 ; i--)
        a[i] = delete_max_heap(h);
    
    free(h);
}

#define SIZE 8
int main(void) 
{
    element e1 = {10}, e2 = {5}, e3 = {30}, es = {23};
    element e4, e5, e6;
    heapTree* heap;

    heap = create();
    init(heap);

    insert_max_heap(heap, e1);
    insert_max_heap(heap, e2);
    insert_max_heap(heap, e3);
    insert_max_heap(heap, es);

    e4 = delete_max_heap(heap);
    printf(" %d ", e4.key);
    e5 = delete_max_heap(heap);
    printf(" %d ", e5.key);
    e6 = delete_max_heap(heap);
    printf(" %d ", e6.key);

    free(heap);

    printf("\n");
    element list[SIZE] = {23, 56, 11, 9 ,56, 99, 27, 34};
    heap_sort(list, SIZE);
    for (int i =0; i < SIZE; i++)
        printf("%d ", list[i].key);
    printf("\n");

    return 0;
}