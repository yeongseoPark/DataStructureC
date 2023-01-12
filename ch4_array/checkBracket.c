#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

int check_matching(const char* in) {
	StackType s;
	char ch, open_ch; //ch: 다음 문자 , open_ch : 스택에서 나온 왼쪽 괄호
	int i;
	int n = strlen(in); // n = 문자열의 길이
	init_stack(&s);
	
	for (i = 0; i < n; i++) {
		ch = in[i];  
		
		switch (ch)
		{
		case '(': case '[': case '{':
			push(&s, ch);
			break; // break out of switch 

		case ')': case ']': case '}':
			if (is_empty(&s)) return 0;
			else {
				open_ch = pop(&s);
				if ((open_ch == '(' && ch != ')') ||
					(open_ch == '{' && ch != '}') ||
					(open_ch == '[' && ch != ']')) {
					return 0;
				}
			}
		}
	}

	if (!is_empty(&s)) return 0; // 스택이 비어있지 않다 => 개수가 맞지 않는다
	return 1;
}

int main6(void) {
	char* p = "{A[(i+1])=0;}";
	if (check_matching(p) == 1)
		printf("%s success \n", p);
	else
		printf("%s fail \n", p);
	return 0;
}