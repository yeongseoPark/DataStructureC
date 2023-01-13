#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

int main11(void) {
	printf("문자열을 입력하시오 : \n");
	char input[MAX_STACK_SIZE];
	scanf_s("%s", input, sizeof(input));

	StackType s1; // 회수 - 문자 - 회수 - 문자 식으로 push
	StackType s2; // s1을 역순으로 출력

	init_stack(&s1);
	init_stack(&s2);

	int i = 0, count;

	while (input[i] != NULL) {
		count = 1;

		char cur = input[i++];
		/* 1. 입력과 다음 input 일치  2. 입력이 소문자, 다음이 대문자   3. 입력이 대문자, 다음이 소문자 */
		while (cur == input[i] || cur + ('A' - 'a') == input[i] || cur - ('A' - 'a') == input[i]) {
			count++;
			i++;
		}

		push(&s1, count + '0'); // s1에 회수 넣기
		/* s1에 문자 넣기(소문자로 통일) */
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

	printf("출력 : ");
	while (!is_empty(&s2)) {
		printf("%c", pop(&s2));
	}

	return 0;
}