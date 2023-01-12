#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element* data;
	int capacity; // 현재 크기
	int top;
} StackType;

// 스택 생성
static void init_stack(StackType* s)
{
	s->top = -1;
	s->capacity = 1;
	s->data = (element*)malloc(s->capacity * sizeof(element));
}

// 공백 상태 검출
static int is_empty(StackType* s)
{
	return (s->top == -1);
}

// 포화 상태 검출
static int is_full(StackType* s)
{
	return (s->top == (s->capacity - 1));
}

static void push(StackType* s, element item)
{
	if (is_full(s)) {
		s->capacity *= 2;
		s->data = (element*)realloc(s->data, s->capacity * sizeof(element)); // 동적 메모리 재할당
	}

	s->data[++(s->top)] = item;
}

static element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러 \n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

int main4(void)
{
	StackType s;
	init_stack(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	free(s.data);
	return 0;
}
