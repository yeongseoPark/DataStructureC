#include <stdio.h>
#define ROWS 3
#define COLS 3

/* 2차원 배열을 이용하여 모든 항목을 표시 */
void matrix_transpose(int A[ROWS][COLS], int B[ROWS][COLS])
{
	for (int r = 0; r < ROWS; r++)
		for (int c = 0; c < COLS; c++)
			B[c][r] = A[r][c];
}

void matrix_print(int A[ROWS][COLS])
{
	printf("=================\n");
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++)
			printf("%d ", A[r][c]);
		printf("\n");
	}
	printf("=================\n");
}

void add_matrix(int A[ROWS][COLS], int B[ROWS][COLS], int added[ROWS][COLS])
{
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++)
			added[r][c] = A[r][c] + B[r][c];
	}

}

int main(void)
{
	int arr1[ROWS][COLS] = { {2,3,0}, {8,9,1}, {7,0,5} };
	int arr2[ROWS][COLS];
	int added[ROWS][COLS];

	matrix_transpose(arr1, arr2);
	matrix_print(arr2);
	add_matrix(arr1, arr2, added);
	matrix_print(added);

	return 0;
}