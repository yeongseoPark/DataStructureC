#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

int eval(char exp[])
{
	int first, second, value, i;
	int len = strlen(exp);
	char ch;
	StackType s;

	init_stack(&s);

	for (i = 0; i < len; i++) {
		ch = exp[i];

		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0';
			push(&s, value);
		}
		else {
			second = pop(&s);
			first = pop(&s);
			switch (ch) {
			case '+': push(&s, first + second); break;
			case '-': push(&s, first - second); break;
			case '*': push(&s, first * second); break;
			case '/': push(&s, first / second); break;
			}
		}
	}
	return pop(&s);
}

int main7(void) {
	int result = eval("82/3-32*+");
	printf("%d \n", result);
	return 0;
}