#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

int main(void) {
	printf("���ڿ��� �Է��Ͻÿ� : ");
	char input_arr[MAX_STACK_SIZE];
	scanf_s("%s", input_arr, sizeof(input_arr));

	StackType s;
	init_stack(&s);

	int i = 0;
	while (input_arr[i] != NULL) {
		if ('a' <= input_arr[i] && input_arr[i] <= 'z') {
			push(&s, input_arr[i]);
		}
		else if ('A' <= input_arr[i] && input_arr[i] <= 'Z') { // �빮�ڵ� �ҹ��ڷ� ����
			push(&s, input_arr[i] - ('A' - 'a'));
		}
		else {
			continue;
		}
		i++;
	}

	int j = 0;
	while (!is_empty(&s)) {
		if ('a' <= input_arr[j] && input_arr[i] <= 'z') {
			if (pop(&s) != input_arr[j]) {
				printf("ȸ���� �ƴմϴ�");
				exit(1);
			}
		}
		else if ('A' <= input_arr[j] && input_arr[i] <= 'Z') {
			if (pop(&s) != input_arr[j] + 32) {
				printf("ȸ���� �ƴմϴ�");
				exit(1);
			}
		}
		j++;
	}

	printf("ȸ���Դϴ�");
}