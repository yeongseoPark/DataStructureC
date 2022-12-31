#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101

typedef struct {
	float coef;
	int expon;
} polynomial;

polynomial terms[MAX_TERMS] = { {8,3} ,{7,1}, {1,0}, {10,3}, {3,2}, {1,0} }; // ���� ���׽� ��� �迭 
int avail = 6;

/* �ΰ��� ������ �� */ 
char compare(int a, int b)
{
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

/* ���ο� �� ���׽Ŀ� �߰� */
void attach(float coef, int expon)
{
	if (avail > MAX_TERMS) {
		fprintf(stderr, "���� ������ �ʹ� ���� \n");
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
		switch (compare(terms[As].expon, terms[Bs].expon)) // ���� ������ ���ؼ� ���ϱ� ���� ����  
		{
		case '>':
			attach(terms[As].coef, terms[As].expon);
			As++;	break;
		case '=':
			tempcoef = terms[As].coef + terms[Bs].coef;
			if (tempcoef) // 0 �� �ƴϸ�(0�� �������� �ʱ⿡)
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