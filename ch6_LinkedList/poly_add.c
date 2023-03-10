#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ListNode {
	int coef;
	int expon;
	struct ListNode* link;
} ListNode;

typedef struct ListType { // 헤더 노드
	int size; 
	ListNode* head;
	ListNode* tail;
} ListType;

void error_poly(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListType* create() // 끝과 마지막을 가르키는 헤더노드 생성
{
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->head = plist->tail = NULL;
	plist->size = 0;
	return plist;
}

void insert_last(ListType* plist, int coef, int expon) // 새로운노드를 다항식의 마지막에 추가 
{
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL) error_poly("메모리 할당 에러");
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	
	plist->size++;
}

void poly_add(ListType* plist1, ListType* plist2, ListType* plist3)
{
	ListNode* a = plist1->head;
	ListNode* b = plist2->head;
	int sum;

	while (a && b) {
		if (a->expon == b->expon) {
			sum = a->coef + b->coef;
			if (sum != 0) insert_last(plist3, sum, a->expon);
			a = a->link; b = b->link;
		} 
		else if (a->expon < b->expon) {
			insert_last(plist3, b->coef, b->expon);
			b = b->link;
		}
		else {
			insert_last(plist3, a->coef, a->expon);
			a = a->link;
		}
	}

	for (;a != NULL; a = a->link)
	{
		insert_last(plist3, a->coef, a->expon);
	}
	for (; b != NULL; b = b->link)
	{
		insert_last(plist3, b->coef, b->expon);
	}
}


void poly_print(ListType* plist)
{
	ListNode* p = plist->head;

	for (; p != NULL; p = p->link) {
		printf("%d^%d + ", p->coef, p->expon);
	}

	printf("\n");
}

int poly_eval(ListType* head, int x)
{
	ListNode* p = head->head;

	int res = 0;

	while (p != NULL) {
		res += pow(x, p->expon) * p->coef;
		p = p->link;
	}

	return res;
}


int main3(void)
{
	ListType* list1, * list2, * list3;

	list1 = create();
	list2 = create();
	list3 = create();

	insert_last(list1, 3, 12);
	insert_last(list1, 2, 8);
	insert_last(list1, 1, 0);

	poly_print(list1);

	printf("%d\n", poly_eval(list1, 3));
}