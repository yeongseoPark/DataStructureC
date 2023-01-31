#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef struct {
	int id;
	int arrival_time;
	int service_time;
} element;

typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE]; // ����ť�� ����ϴ� �迭�� ���̴� ����
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

void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);

	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}

	printf("\n");
}

int is_full(QueueType* q)
{
	int nextRear = (q->rear + 1) % MAX_QUEUE_SIZE;
	if (nextRear == q->front)
		return 1;
	else
		return 0;
}

int is_empty(QueueType* q)
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}


void enqueue(QueueType* q, element item)
{
	if (is_full(q)) {
		error("��ȭ�����Դϴ�");
	}

	int nextRear = (q->rear + 1) % MAX_QUEUE_SIZE;

	q->rear = nextRear;

	q->data[q->rear] = item;
}

element dequeue(QueueType* q)
{
	if (is_empty(q)) {
		error("��������Դϴ�");
	}

	int nextFront = (q->front + 1) % MAX_QUEUE_SIZE;

	q->front = nextFront;

	return q->data[q->front];
}

element peek(QueueType* q)
{
	if (is_empty(q))
		error("��������Դϴ�");

	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main(void) {
	int minutes = 60;
	int total_wait = 0;
	int total_customer = 0;
	int service_time = 0;
	int service_customer;
	QueueType queue;
	init_queue(&queue);

	srand(time(NULL));
	for (int clock = 0; clock < minutes; clock++)
	{
		printf("����ð� %d \n", clock);
		if ((rand() % 10) < 3) {
			element customer; 
			customer.id = total_customer++;
			customer.arrival_time = clock;
			customer.service_time = rand() % 3 + 1;
			enqueue(&queue, customer);
			printf("�� %d �� %d �п� ����, ó���ð� = %d \n",
				customer.id, customer.arrival_time, customer.service_time);
		}

		if (service_time > 0)
		{
			printf("�� ���� ó���� %d \n", service_customer);
			service_time--;
		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				printf("�� %d �� %d �п� ���� ����, ���ð� = %d \n",
					customer.id, clock, clock - customer.arrival_time);
				total_wait += clock - customer.arrival_time;
			}
		}
	}

	printf("��ü ��� �ð� %d�� \n", total_wait);
	return 0;
}