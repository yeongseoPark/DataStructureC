#include<stdio.h>

#define MAX_SIZE 100

typedef struct Stacktype {
	int stack[MAX_SIZE];
	int top;
} Stacktype;

void Stack_init(Stacktype* s) {
	s->top = -1;
}

void Stack_push(Stacktype* s, int item) {
	if (s->top == MAX_SIZE - 1) return;

	s->stack[++(s->top)] = item;
	return;
}

int is_empty_stack(Stacktype* s) {
	return s->top == -1;
}

int Stack_pop(Stacktype* s) {
	if (is_empty_stack(s)) return -1;

	return s->stack[(s->top)--];
}

typedef struct Queuetype {
	Stacktype s1, s2;
} Queuetype;

void Queue_init(Queuetype* q) {
	Stack_init(&(q->s1));
	Stack_init(&(q->s2));
}

void Queue_push(Queuetype* q, int item) {
	Stack_push(&(q->s1), item);
}

int Queue_pop(Queuetype* q) {
	if (is_empty_stack(&(q->s2))) {
		while (!is_empty_stack(&(q->s1))) {
			int tmp = Stack_pop(&(q->s1));
			Stack_push(&(q->s2), tmp);
		}
	}

	return Stack_pop(&(q->s2));
}

int main2(void) {
	Queuetype q;
	Queue_init(&q);
	Queue_push(&q, 5);
	Queue_push(&q, 4);
	Queue_push(&q, 3);
	printf("%d\n", Queue_pop(&q));
	printf("%d\n", Queue_pop(&q));
	printf("%d\n", Queue_pop(&q));
}