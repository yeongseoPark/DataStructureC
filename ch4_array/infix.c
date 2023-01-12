#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

/* �������� �켱���� ��ȯ */
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
	char ch, top_op; // top_op�� ������ ��ȣ ������ �� ���
	int len = strlen(exp);
	StackType s;

	init_stack(&s);

	for (int i = 0; i < len; i++)
	{
		ch = exp[i];
		switch (ch)
		{
		case '+': case '-': case '*': case '/': // ������ case
			/* ���� �����ں��� ���ÿ� �ִ� �������� ������ ũ�ų� ������ ��� */
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) 
				printf("%c", pop(&s));
			push(&s, ch);
			break;

		case '(': // ���� ��ȣ case
			push(&s, ch);
			break;

		case ')': // ������ ��ȣ case
			top_op = pop(&s);
			while (top_op != '(') { // ���� ��ȣ ���ö����� ������ ������ ���
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;

		default: // �ǿ�����
			printf("%c", ch);
		}
	}

	while (!is_empty(&s))
		printf("%c" , pop(&s));
}

int main9(void)
{
	char* s = "(2+3)*4+9";
	printf("����ǥ�ü��� %s \n", s);
	printf("����ǥ�ü��� ");
	infix_to_postfix(s);
	printf("\n");
	return 0;
}