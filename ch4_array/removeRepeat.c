#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

int main12(void) {
	printf("정수를 입력하시오 : ");
	char input[MAX_STACK_SIZE];
	scanf_s("%s", input, sizeof(input));

	StackType s;
	init_stack(&s);

	int i = sizeof(input) / sizeof(char) - 1;
	while (i >= 0) {
		push(&s, input[i--]);
	}

	char cur = pop(&s);
	printf("%c", cur);
	while (!is_empty(&s)) {
		if (cur == peek(&s)) {
			pop(&s);
		}
		else {
			cur = pop(&s);
			printf("%c", cur);
		}
	}
}