#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

/* 연산자의 우선순위 반환 */
int prec(char op)
{
	switch (op) 
	{
		case '(': case ')': return 0;
		case '+': case '-': return 1;
		case '*': case '/': return 2;
	}
	return -1;
}

void infix_to_postfix(char exp[])
{
	int i = 0;
	char ch, top_op; // top_op는 오른쪽 괄호 만났을 시 사용
	int len = strlen(exp);
	StackType s;

	init_stack(&s);

	for (int i = 0; i < len; i++)
	{
		ch = exp[i];
		switch (ch)
		{
		case '+': case '-': case '*': case '/': // 연산자 case
			/* 현재 연산자보다 스택에 있는 연산자의 순위가 크거나 같으면 출력 */
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) 
				printf("%c", pop(&s));
			push(&s, ch);
			break;

		case '(': // 왼쪽 괄호 case
			push(&s, ch);
			break;

		case ')': // 오른쪽 괄호 case
			top_op = pop(&s);
			while (top_op != '(') { // 왼쪽 괄호 나올때까지 스택의 연산자 출력
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;

		default: // 피연산자
			printf("%c", ch);
		}
	}

	while (!is_empty(&s))
		printf("%c" , pop(&s));
}

int main9(void)
{
	char* s = "(2+3)*4+9";
	printf("중위표시수식 %s \n", s);
	printf("후위표시수식 ");
	infix_to_postfix(s);
	printf("\n");
	return 0;
}