#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct Queue {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(Queue* q)
{
    q->front = q->rear = 0;
}

int is_empty(Queue* q)
{
    return (q->front == q->rear);
}

int is_full(Queue* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(Queue* q, element data)
{
    if (is_full(q))
        error("already full");

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    
    q->data[q->rear] = data;
}

element dequeue(Queue* q)
{
    if (is_empty(q))
        error("empty Queue");
    
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}
