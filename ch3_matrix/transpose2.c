#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int row;
	int col;
	int value;
} element;

typedef struct SparseMatrix {
	element data[100];
	int rows;  // 행 개수
	int cols;  // 열 개수
	int terms; // 항의 개수
} SparseMatrix;

SparseMatrix matrix_transpose2(SparseMatrix a)
{
	SparseMatrix b;

	int bindex; 
	b.rows = a.cols;
	b.cols = a.rows;
	b.terms = a.terms;

	if (a.terms > 0) {
		bindex = 0;
		for (int c = 0; c < a.cols; c++) { // 행의 오름차순으로 저장해야 하기 때문에, 열 -> 행임을 감안하여 낮은 열부터 행으로 변환
			for (int i = 0; i < a.terms; i++) {
				if (a.data[i].col == c) {
					b.data[bindex].row = a.data[i].col;
					b.data[bindex].col = a.data[i].row;
					b.data[bindex].value = a.data[i].value;
					bindex++;
				}
			}
		}
	}

	return b;
}

void matrix_print2(SparseMatrix a)
{
	printf("=================\n");
	for (int i = 0; i < a.terms; i++) {
		printf("(%d, %d, %d) \n", a.data[i].row, a.data[i].col, a.data[i].value);
	}
	printf("=================\n");
}


int main2(void)
{
	SparseMatrix m = {
		{{0, 3, 7}, {1, 0, 9}, {1, 5, 8}, {3, 0 ,6}, {3, 1 ,5}, {4, 5, 1}, {5,2,2}},
		6,
		6,
		7
	};

	SparseMatrix res;

	res = matrix_transpose2(m);
	matrix_print2(res);
	return 0;
}