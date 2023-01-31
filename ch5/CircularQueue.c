#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 20

typedef int element;
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


void enqueue(QueueType* q, int item)
{
	if (is_full(q)) {
		error("��ȭ�����Դϴ�");
	}

	int nextRear = (q->rear + 1) % MAX_QUEUE_SIZE;

	q->rear = nextRear;

	q->data[q->rear] = item;
}

int dequeue(QueueType* q)
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

/* �������� 8�� */
int get_count(QueueType* q)
{
	if (is_empty(q)) return 0;

	int front = q->front;
	int rear = q->rear;

	if (front < rear) {
		return rear - front;
	}
	else {
		return MAX_QUEUE_SIZE - (front - rear);
	}
}

/* �������� 10�� */
int fibonacci(QueueType* q, int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;

	enqueue(q, 0);
	enqueue(q, 1);

	int result = 0;

	for (int i = 2; i <= n; i++) {
		int NminusOne = dequeue(q);
		int NminusTwo = peek(q);

		result = NminusOne + NminusTwo;

		enqueue(q, NminusOne + NminusTwo);
	}
	
	return q->data[q->rear];
}


int main3(void)
{
	QueueType q;
	int element;

	init_queue(&q);
	srand(time(NULL)); 
	// seed���� ���� ������ ����
	// seed���� ����ø��� �ٲ�� �ϱ� ���Ͽ� time(NULL)�� 1970.1.1���� ���α׷� ����ñ��� �帥 �ð� �־���

	for (int i = 0; i < 100; i++)
	{
		if (rand() % 5 == 0) { // rand()�� srand()�� ������
			enqueue(&q, rand() % 100);
		} 
		queue_print(&q);
		if (rand() % 10 == 0) {
			int data = dequeue(&q);
		}
		queue_print(&q);
	}




	return 0;
}