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
	element data[MAX_QUEUE_SIZE]; // 선형큐와 사용하는 배열의 차이는 없다
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
		error("포화상태입니다");
	}

	int nextRear = (q->rear + 1) % MAX_QUEUE_SIZE;

	q->rear = nextRear;

	q->data[q->rear] = item;
}

element dequeue(QueueType* q)
{
	if (is_empty(q)) {
		error("공백상태입니다");
	}

	int nextFront = (q->front + 1) % MAX_QUEUE_SIZE;

	q->front = nextFront;

	return q->data[q->front];
}

element peek(QueueType* q)
{
	if (is_empty(q))
		error("공백상태입니다");

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
		printf("현재시각 %d \n", clock);
		if ((rand() % 10) < 3) {
			element customer; 
			customer.id = total_customer++;
			customer.arrival_time = clock;
			customer.service_time = rand() % 3 + 1;
			enqueue(&queue, customer);
			printf("고객 %d 이 %d 분에 들어옴, 처리시간 = %d \n",
				customer.id, customer.arrival_time, customer.service_time);
		}

		if (service_time > 0)
		{
			printf("고객 업무 처리중 %d \n", service_customer);
			service_time--;
		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				printf("고객 %d 이 %d 분에 업무 시작, 대기시간 = %d \n",
					customer.id, clock, clock - customer.arrival_time);
				total_wait += clock - customer.arrival_time;
			}
		}
	}

	printf("전체 대기 시간 %d분 \n", total_wait);
	return 0;
}