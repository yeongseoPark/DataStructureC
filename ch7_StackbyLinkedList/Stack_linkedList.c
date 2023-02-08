#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s)
{
	s->top = NULL;
}

int is_empty(LinkedStackType* s)
{
	return 0; // malloc만된다면 노드 생성할 수 있기에 포화상태는 없는것과 마찬가지 
}

int is_full(LinkedStackType* s)
{
	return 0;
}

void push(LinkedStackType* s, element item)
{
	StackNode* tmp = (StackNode*)malloc(sizeof(StackNode));
	tmp->data = item;
	tmp->link = s->top;

	s->top = tmp;
}

void print_stack(LinkedStackType* s)
{
	StackNode* p = s->top;

	while (p != NULL)
	{
		printf("%d ->", p->data);
		p = p->link;
	}

	printf("NULL \n");
}

element pop(LinkedStackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "stack empty\n");
		exit(1);
	}
	else {
		StackNode* tmp = s->top;
		int data = tmp->data;
		s->top = s->top->link;
		free(tmp);
		return data;
	}
}

element peek(LinkedStackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "stack empty\n");
		exit(1);
	}
	else {
		return s->top->data;
	}
}

int main2(void)
{
	LinkedStackType s;
	init(&s);
	push(&s, 1); print_stack(&s);
	push(&s, 2); print_stack(&s);
	push(&s, 3); print_stack(&s);

	pop(&s); print_stack(&s);
	pop(&s); print_stack(&s);
	pop(&s); print_stack(&s);
	return 0;
}