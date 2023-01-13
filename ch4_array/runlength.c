#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

int main11(void) {
	printf("���ڿ��� �Է��Ͻÿ� : \n");
	char input[MAX_STACK_SIZE];
	scanf_s("%s", input, sizeof(input));

	StackType s1; // ȸ�� - ���� - ȸ�� - ���� ������ push
	StackType s2; // s1�� �������� ���

	init_stack(&s1);
	init_stack(&s2);

	int i = 0, count;

	while (input[i] != NULL) {
		count = 1;

		char cur = input[i++];
		/* 1. �Է°� ���� input ��ġ  2. �Է��� �ҹ���, ������ �빮��   3. �Է��� �빮��, ������ �ҹ��� */
		while (cur == input[i] || cur + ('A' - 'a') == input[i] || cur - ('A' - 'a') == input[i]) {
			count++;
			i++;
		}

		push(&s1, count + '0'); // s1�� ȸ�� �ֱ�
		/* s1�� ���� �ֱ�(�ҹ��ڷ� ����) */
		if ('a' <= cur <= 'z') {
			push(&s1, cur);
		}
		else {
			push(&s1, cur + ('a' - 'A'));
		}
	}

	while (!is_empty(&s1)) {
		push(&s2, pop(&s1));
	}

	printf("��� : ");
	while (!is_empty(&s2)) {
		printf("%c", pop(&s2));
	}

	return 0;
}