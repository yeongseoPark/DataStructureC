#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct QueueNode {
	element data;
	struct QueueNode* link;
} QueueNode;

typedef struct {
	QueueNode* front, * rear;
} LinkedQueueType;

void init_q(LinkedQueueType* q)
{
	q->front = NULL;
	q->rear = NULL;
}

int is_empty_q(LinkedQueueType* q)
{
	return q->front == NULL;
}

int is_full_q(LinkedQueueType* q)
{
	return 0;
}

void enque(LinkedQueueType* q, element data)
{
	QueueNode* tmp = (QueueNode*)malloc(sizeof(QueueNode));
	tmp->data = data;
	tmp->link = NULL;

	if (is_empty_q(q)) {
		q->front = q->rear = tmp;
	}
	else {
		q->rear->link = tmp;
		q->rear = q->rear->link;
	}
}

element deque(LinkedQueueType* q)
{
	QueueNode* tmp = q->front;
	element data;

	if (is_empty_q(q)) {
		fprintf(stderr, "Queue empty\n");
		exit(1);
	}
	else {
		data = tmp->data;
		q->front = q->front->link;
		if (q->front == NULL) { // 노드 1개에서 삭제시
			q->rear = NULL;
		}
		free(tmp);
		return data;
	}
}

void print_queue(LinkedQueueType* q)
{
	QueueNode* p = q->front;
	while (p != NULL) {
		printf("%d -> ", p->data);
		p = p->link;
	}

	printf("NULL \n");
}

int main(void)
{
	LinkedQueueType q;

	init_q(&q);

	enque(&q, 1); print_queue(&q);
	enque(&q, 2); print_queue(&q);
	enque(&q, 3); print_queue(&q);
	deque(&q); print_queue(&q);
	deque(&q); print_queue(&q);
	deque(&q); print_queue(&q);
	return 0;
}