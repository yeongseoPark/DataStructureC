#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE]; // 선형큐와 사용하는 배열의 차이는 없다
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

void add_rear(DequeType* q, int item) // = 큐의 enque
{
	if (is_full_deque(q)) {
		error2("포화상태입니다");
	}

	int nextRear = (q->rear + 1) % MAX_QUEUE_SIZE;

	q->rear = nextRear;

	q->data[q->rear] = item;
}

element delete_front(DequeType* q)// = 큐의 dequeue
{
	if (is_empty_deque(q)) {
		error2("공백상태입니다");
	}

	int nextFront = (q->front + 1) % MAX_QUEUE_SIZE;

	q->front = nextFront;

	return q->data[q->front];
}

element get_front(DequeType* q) // = 큐의 peek
{
	if (is_empty_deque(q))
		error2("공백상태입니다");

	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

/* 여기부터 deque에 추가된 기능 */

void add_front(DequeType* q, element val)
{
	if (is_full_deque(q))
		error2("포화상태입니다");

	q->data[q->front] = val;

	int newFront = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; // front를 시계반대방향으로 회전
	q->front = newFront;
}

void delete_rear(DequeType* q)
{
	int prev = q->rear;

	if (is_empty_deque(q))
		error2("공백상태입니다");
	
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; // rear를 시계반대방향으로 회전

	return q->data[prev];
}

element get_rear(DequeType* q)
{
	if (is_empty_deque(q))
		error2("공백상태입니다");

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

	char buf[] = "radar"; // String literal 초기화, 자동적으로 /0 추가된 널 종단문자 됨

	/* char buf[] = {'r','a','d','a','r'}; 로 초기화할시, /0가 추가되지 않는 배열 초기화이기에
	  strlen 사용시 잘못된 값
	  이경우 sizeof(buf)/sizeof(buf[0]);로 길이 계산(함수에 매개변수로 넘기기 전에)
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