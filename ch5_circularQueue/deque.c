#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE]; // ����ť�� ����ϴ� �迭�� ���̴� ����
} DequeType;

void error2(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_deque(DequeType* q)
{
	q->rear = 0;
	q->front = 0;
}

int is_empty_deque(DequeType* q)
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

int is_full_deque(DequeType* q)
{
	int nextRear = (q->rear + 1) % MAX_QUEUE_SIZE;
	if (nextRear == q->front)
		return 1;
	else
		return 0;
}

void dequeue_print(DequeType* q)
{
	printf("DEQUEUE(front=%d rear=%d) = ", q->front, q->rear);

	if (!is_empty_deque(q)) {
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

void add_rear(DequeType* q, int item) // = ť�� enque
{
	if (is_full_deque(q)) {
		error2("��ȭ�����Դϴ�");
	}

	int nextRear = (q->rear + 1) % MAX_QUEUE_SIZE;

	q->rear = nextRear;

	q->data[q->rear] = item;
}

element delete_front(DequeType* q)// = ť�� dequeue
{
	if (is_empty_deque(q)) {
		error2("��������Դϴ�");
	}

	int nextFront = (q->front + 1) % MAX_QUEUE_SIZE;

	q->front = nextFront;

	return q->data[q->front];
}

element get_front(DequeType* q) // = ť�� peek
{
	if (is_empty_deque(q))
		error2("��������Դϴ�");

	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

/* ������� deque�� �߰��� ��� */

void add_front(DequeType* q, element val)
{
	if (is_full_deque(q))
		error2("��ȭ�����Դϴ�");

	q->data[q->front] = val;

	int newFront = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; // front�� �ð�ݴ�������� ȸ��
	q->front = newFront;
}

void delete_rear(DequeType* q)
{
	int prev = q->rear;

	if (is_empty_deque(q))
		error2("��������Դϴ�");
	
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; // rear�� �ð�ݴ�������� ȸ��

	return q->data[prev];
}

element get_rear(DequeType* q)
{
	if (is_empty_deque(q))
		error2("��������Դϴ�");

	return q->data[q->rear];
}

int palindrome(char i[], int len)
{
	int start = 0;
	len--;
	
	while (start < len) {
		char first_half = i[start++];
		char last_half = i[len--];

		if (first_half != last_half) return 0;
	}

	return 1;
}

int main(void)
{
	DequeType dq;

	init_deque(&dq);

	char buf[] = "radar"; // String literal �ʱ�ȭ, �ڵ������� /0 �߰��� �� ���ܹ��� ��

	/* char buf[] = {'r','a','d','a','r'}; �� �ʱ�ȭ�ҽ�, /0�� �߰����� �ʴ� �迭 �ʱ�ȭ�̱⿡
	  strlen ���� �߸��� ��
	  �̰�� sizeof(buf)/sizeof(buf[0]);�� ���� ���(�Լ��� �Ű������� �ѱ�� ����)
	*/

	int len = strlen(buf);

	if (palindrome(buf, len)) {
		printf("palindrome!");
	}
	else {
		printf("not!");
	}

	return 0;
}