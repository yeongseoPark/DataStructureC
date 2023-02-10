#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 20

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

typedef TreeNode* element;
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

void level_order(TreeNode* ptr)
{
	QueueType q;

	init_queue(&q);

	if (ptr == NULL) return;

	enqueue(&q, ptr);

	while (!is_empty(&q))
	{
		TreeNode* p = dequeue(&q);
		printf("%d -> ", p->data);
		if (p->left != NULL) {
			enqueue(&q, p->left);
		}

		if (p->right != NULL) {
			enqueue(&q, p->right);
		}
	}
}




int main2(void)
{

	TreeNode n1 = { 1, NULL, NULL };
	TreeNode n2 = { 4, &n1, NULL };
	TreeNode n3 = { 16, NULL, NULL };
	TreeNode n4 = { 25, NULL, NULL };
	TreeNode n5 = { 20, &n3, &n4 };
	TreeNode n6 = { 15, &n2, &n5 };
	TreeNode* root = &n6;

	level_order(root);
	printf("\n");

	return 0;
}