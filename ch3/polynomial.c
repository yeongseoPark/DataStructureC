#include <stdio.h>
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MAX_DEGREE 101

typedef struct {
	int degree;
	float coef[MAX_DEGREE]; // 다항식의 계수 배열
} polynomial;

/* 다항식의 덧셈 */
polynomial poly_add1(polynomial A, polynomial B) {
	polynomial C;

	int Apos = 0, Bpos = 0, Cpos = 0; // 배열 인덱스 변수
	int degree_a = A.degree;
	int degree_b = B.degree;

	C.degree = MAX(A.degree, B.degree); // 결과 다항식의 차수

	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) { // a가 b 보다 차수가 클때 -> a의 계수를 그대로 기록하면 됨
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) { // a와 b의 차수가 같으면 둘의 계수를 더한다
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--; degree_b--;
		}
		else { // b차수 > a차수
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

void print_poly(polynomial p) {
	for (int i = p.degree; i > 0; i--) 
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
	printf("%3.1f \n", p.coef[p.degree]);
}

int main2(void)
{
	polynomial a = { 5, {3,6,0,0,0,10} };
	polynomial b = { 4, {7,0,5,0,1} };
	polynomial c;

	print_poly(a);
	print_poly(b);
	c = poly_add1(a, b);
	printf("----------------------\n");
	print_poly(c);
	return 0;
}