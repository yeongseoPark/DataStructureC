#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10

typedef int element;
typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
} QueueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q)
{
	q->rear = 0;
	q->front = 0;
}

int is_empty_q(QueueType *q)
{
    return (q->front == q->rear);
}

int is_full_q(QueueType* q)
{
    return (q->rear+1) % MAX_QUEUE_SIZE == q->front;
}

void enqueue(QueueType* q, element item)
{
    if (is_full_q(q))
        error("queue is full");
    
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element dequeue(QueueType* q)
{
    if (is_empty_q(q))
        error("queue is empty");
    
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}