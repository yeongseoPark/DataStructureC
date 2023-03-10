#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 6
#define MAX_STACK_SIZE 100

typedef struct {
	short r;
	short c;
} element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s)
{
	return (s->top == -1);
}

int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 \n");
		return;
	}

	else s->data[++(s->top)] = item;
}

element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 \n");
		exit(1);
	}

	else return s->data[(s->top)--];
}

element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 \n");
		exit(1);
	}

	else return s->data[s->top];
}

element here = { 1,0 }, entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = { // 1은 벽, 0은 길
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};

/* 스택에 위치 삽입 */
void push_loc(StackType* s, int r, int c)
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

/* 미로 화면 출력 */
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}

/* 미로 탐색 */
int main(void) {
	int r, c;
	StackType s;

	init_stack(&s);
	here = entry;

	element road[MAX_STACK_SIZE] = {0, };

	int i = 1;
	while (maze[here.r][here.c] != 'x')
	{
		r = here.r;
		c = here.c;
		maze[r][c] = '.';

		road[i].r = r;
		road[i++].c = c;
		
		maze_print(maze);

		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);

		if (is_empty(&s)) {
			printf("fail");
			return;
		}
		else {
			here = pop(&s);
		}
	}

	/* 지나온 경로 출력 */
	for (int j = 1; j < i; j++) {
		printf("경로 : { %d , %d } \n", road[j].r, road[j].c);
	}

	printf("success");
	return 0;
}