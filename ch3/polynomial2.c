#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101

typedef struct {
	float coef;
	int expon;
} polynomial;

polynomial terms[MAX_TERMS] = { {8,3} ,{7,1}, {1,0}, {10,3}, {3,2}, {1,0} }; // 여러 다항식 담는 배열 
int avail = 6;

/* 두개의 정수를 비교 */ 
char compare(int a, int b)
{
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

/* 새로운 항 다항식에 추가 */
void attach(float coef, int expon)
{
	if (avail > MAX_TERMS) {
		fprintf(stderr, "항의 개수가 너무 많음 \n");
		exit(1);
	}

	terms[avail].coef = coef;
	terms[avail].expon = expon;
	avail++;
}

void poly_add2(int As, int Ae, int Bs, int Be, int* Cs, int* Ce) 
{
	float tempcoef;
	*Cs = avail; 
	while (As <= Ae && Bs <= Be)
		switch (compare(terms[As].expon, terms[Bs].expon)) // 둘의 차수를 비교해서 더하기 형태 결정  
		{
		case '>':
			attach(terms[As].coef, terms[As].expon);
			As++;	break;
		case '=':
			tempcoef = terms[As].coef + terms[Bs].coef;
			if (tempcoef) // 0 이 아니면(0은 저장하지 않기에)
				attach(tempcoef, terms[As].expon);
			As++; Bs++;		break;
		case '<':
			attach(terms[Bs].coef, terms[Bs].expon);
			Bs++;	break;
		}

	for (; As <= Ae; As++) // = while(As <= Ae) { .... As++ }
		attach(terms[As].coef, terms[As].expon);
	for (; Bs <= Be; Bs++)
		attach(terms[Bs].coef, terms[Bs].expon);
	*Ce = avail - 1; 
}

void print_poly2(int s, int e) {
	for (int i = s; i < e; i++) {
		printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
	}
	printf("%3.1fx^%d + ", terms[e].coef, terms[e].expon);
}

int main_2(void) {
	int As = 0, Ae = 2, Bs = 3, Be = 5, Cs, Ce;
	poly_add2(As, Ae, Bs, Be, &Cs, &Ce);
	print_poly2(As, Ae);
	print_poly2(Bs, Be);
	printf("-----------------------\n");
	print_poly2(Cs, Ce);
	return 0;
}