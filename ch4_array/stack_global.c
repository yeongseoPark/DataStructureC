#include <stdio.h>
#include <stdlib.h>

/* ������ ���������� �����ȴ� */
#define MAX_STACK_SIZE 100
typedef int element;
element stack[MAX_STACK_SIZE];
int top = -1;

int is_empty()
{
	return (top == -1);
}

int is_full() 
{
	return (top == MAX_STACK_SIZE - 1);
}

void push(element item)
{
	if (is_full()) {
		fprintf(stderr, "���� ��ȭ \n");
		return;
	}

	else stack[++top] = item;
}

element pop()
{
	if (is_empty()) {
		fprintf(stderr, "���� ���� \n");
		exit(1);
	}

	else return stack[top--];
}

element peek()
{
	if (is_empty()) {
		fprintf(stderr, "���� ���� \n");
		exit(1);
	}

	else return stack[top];
}

int main2(void)
{
	push(1);
	push(2);
	push(3);
	push(4);
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	return 0;
}