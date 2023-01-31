#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#define MAX_QUEUE_SIZE 5

typedef struct {
	int id;
	int arrival_time;
	int service_time;
} element;

typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
} BankingQueueType;

void init_queue(BankingQueueType* q);
void queue_print(BankingQueueType* q);
int is_full(BankingQueueType* q);
int is_empty(BankingQueueType* q);
void enqueue(BankingQueueType* q, element item);
element dequeue(BankingQueueType* q);
element peek(BankingQueueType* q);

#endif