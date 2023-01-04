#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_STRING 100

typedef struct {
	int student_no;
	char name[MAX_STRING];
	char address[MAX_STRING];
} element2;

element2 stack2[MAX_STACK_SIZE];
int top2 = -1;

int is_empty2()
{
	return (top2 == -1);
}

int is_full2()
{
	return (top2 == MAX_STACK_SIZE - 1);
}

void push2(element2 item)
{
	if (is_full2()) {
		fprintf(stderr, "스택 포화 \n");
		return;
	}

	else stack2[++top2] = item;
}

element2 pop2()
{
	if (is_empty2()) {
		fprintf(stderr, "스택 공백 \n");
		exit(1);
	}

	else return stack2[top2--];
}

element2 peek2()
{
	if (is_empty()) {
		fprintf(stderr, "스택 공백 \n");
		exit(1);
	}

	else return stack2[top2];
}

int main2(void)
{
	element2 ie = { 2019123, "park", "yeong" };
	element2 oe;

	push2(ie);
	oe = pop2();

	printf("%d\n", oe.student_no);
	printf("%s\n", oe.name);
	printf("%s\n", oe.address);
	return 0;
}