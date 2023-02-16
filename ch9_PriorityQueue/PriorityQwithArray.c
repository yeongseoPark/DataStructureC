#include <stdio.h>
#include <stdlib.h>
#define MAX_ARRAY 100

typedef struct element {
    int data;
} element;

typedef struct Pqueue {
    element arr[MAX_ARRAY];
    int size;
} Pqueue;

Pqueue* create()
{
    return (Pqueue*)malloc(sizeof(Pqueue));
}

void init(Pqueue* p) 
{
    p->size = 0;
}

void insert(Pqueue* p, element e)
{
    p->arr[(p->size)++] = e;
}

element delete(Pqueue* p)
{
    int i;
    element top_priority;
    int max_index = 0;

    for (i = 1; i < p->size; i++)
    {
        if (p->arr[i].data > p->arr[max_index].data) 
            max_index = i;
    }
    top_priority = p->arr[max_index];

    for (i = max_index; i < p->size - 1; i++) 
    {
        p->arr[i] = p->arr[i+1];
    }
    p->size--;


    return top_priority;
}

int main()
{
    Pqueue* p = create();
    init(p);

    element e = {2};
    element e1 = {1};
    element e2 = {4};
    element e3 = {3};
    element e4 = {6};
    element e5 = {5};

    insert(p, e);
    insert(p, e1);
    printf("%d ", delete(p).data);
    insert(p, e2);
    insert(p, e3);
    insert(p, e4);
    insert(p, e5);

    for (int i = 0; i < 5; i++) 
        printf("%d ", delete(p).data);
}
