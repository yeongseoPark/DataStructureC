#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct DListNode {
	element data;
	struct DListNode* Llink;
	struct DListNode* Rlink;
} DListNode;

DListNode* current;

void init(DListNode* head)
{
	head->Llink = head;
	head->Rlink = head;
}

void print_dlist(DListNode* head)
{
	DListNode* p = head;

	for (p = head->Rlink; p != head; p = p->Rlink) {
		if (p == current) {
			printf("<- | #%s# | ->", p->data);
		}
		else {
			printf("<- | %s | ->", p->data);
		}
	}

	printf("\n");
}

void insert(DListNode* before, element data) // before의 오른쪽 삽입
{
	DListNode* tmp = (DListNode*)malloc(sizeof(DListNode));
	strcpy_s(tmp->data, sizeof(data) , data);

	tmp->Llink = before;
	tmp->Rlink = before->Rlink;
	before->Rlink->Llink = tmp;
	before->Rlink = tmp;
}

void delete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;
	removed->Llink->Rlink = removed->Rlink;
	removed->Rlink->Llink = removed->Llink;
	free(removed);
}

DListNode* search(DListNode* head, element data) {
	DListNode* p = head;
	p = p->Rlink;
	while (p != head) {
		if (strcmp(p->data, data) == 0) {
			return p;
		}
		p = p->Rlink;
	}

	fprintf(stderr, "no such element");
}

int mp3()
{
	char ch;
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);

	insert(head, "one");
	insert(head, "two");
	insert(head, "three");

	current = head->Rlink;
	print_dlist(head);

	do {
		printf("\n명령어 입력(<, >, q):");
		ch = getchar();
		if (ch == '<') 
		{
			current = current->Llink;
			if (current == head) {
				current = current->Llink;
			}
		}
		else if (ch == '>')
		{
			current = current->Rlink;
			if (current == head) {
				current = current->Rlink;
			}
		}
		print_dlist(head);
		getchar(); // 버퍼에 남은 \n 소모

	} while (ch != 'q');


	return 0;
}

int main(void)
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);

	printf("데이터의 개수 입력: ");
	int len;
	scanf_s("%d", &len,sizeof(int));

	int i;

	for (i = 1; i <= len; i++)
	{
		printf("\n노드 #%d의 데이터를 입력하시오 : ", i);
		char data[10];
		scanf_s("%s", data, sizeof(data));
		insert(head, data);
	}

	printf("데이터를 역순으로 출력 : ");
	DListNode* searcher = head->Llink;

	while (searcher != head) {
		printf("%s ", searcher->data);
		searcher = searcher->Llink;
	}
}