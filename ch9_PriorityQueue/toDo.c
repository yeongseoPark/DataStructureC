#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 200
#define WORK 30

typedef struct element{
    char work[WORK];
    int priority;
} element; 

typedef struct heap {
    element heap[MAX_ELEMENT];
    int heap_size;
} heap;

heap* create()
{
    return (heap*)malloc(sizeof(heap));
}

void init(heap* h)
{
    h->heap_size = 0;
}

void insert_max_heap(heap* h, element data)
{
    int i = ++(h->heap_size);
    h->heap[i] = data;
    int parent = i / 2;

    while (parent >= 1 && (h->heap[parent].priority < data.priority)) {
        h->heap[i] = h->heap[parent];

        i = parent;
        parent /= 2;
    }

    h->heap[i] = data;
}

element delete_max_heap(heap* h)
{
    int parent, child;

    element item, temp;

    temp = h->heap[h->heap_size--]; // 말단
    item = h->heap[1]; // 삭제될 최상위 노드

    h->heap[1] = temp;
    parent = 1;
    child = 2;

    while (child <= h->heap_size) 
    {
        if (child < h->heap_size) {
            if (h->heap[child].priority < h->heap[child+1].priority) child++;
        }

        if (temp.priority >= h->heap[child].priority) break;

        h->heap[parent] = h->heap[child];

        parent = child;
        child *= 2;
    }

    h->heap[parent] = temp;
    return item;
}

int main(void)
{
    element e = {0,0};

    heap* h = create();
    init(h);

    char input;

    do {
        printf("insert(i), delete(d) : ");
        input = getchar();
        while (getchar() != '\n') {};

        switch (input)
        {
        case 'i':
            printf("\nwork to do :");
            char work[WORK];
            scanf("%s", work);
            getchar();

            printf("\npriority : ");
            int priority;
            scanf("%d", &priority);
            getchar();
            
            strcpy(e.work, work);
            e.priority = priority;

            insert_max_heap(h, e);
            break;
        
        case 'd':
            e = delete_max_heap(h);

            printf("top priority work is %s\n", e.work);

            break;
        }
    } while (input != 'q');   


}