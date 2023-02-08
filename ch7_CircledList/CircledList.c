#include <stdio.h>
#include <stdlib.h>

#include <string.h>

typedef char element[100];
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

void print_list(ListNode* head) // head는 원형 연결리스트의 마지막 노드 가리킴
{
	ListNode* p = head;

	do {
		p = p->link;
		printf("%s -> ", p->data);
	} while (p != head);

	printf("\n");
}

ListNode* insert_first(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));

	strcpy_s(node->data , sizeof(data), data);

	if (head == NULL) {
		head = node;
		head->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
	}

	return head;
}

ListNode* insert_last(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));

	strcpy_s(node->data, sizeof(data), data);

	if (head == NULL) {
		head = node;
		head->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
		head = head->link;
	}

	return head;
}

ListNode* search(ListNode* head, element data)
{
	ListNode* p = head;

	do {
		p = p->link;
		if (strcmp(p->data, data) == 0) {
			return p;
		}
	} while (p != head);

	fprintf(stderr, "\nno such element : %s", data);
	exit(1);
}

int get_size(ListNode* head) {
	int size = 0;
	ListNode* p = head;
	if (p == NULL) return 0;

	do {
		p = p->link;
		size++;
	} while (p != head);

	return size;
}

int main(void)
{
	ListNode* head = NULL;

	head = insert_first(head, "k");
	head = insert_first(head, "p");
	head = insert_first(head, "c");
	print_list(head);


	ListNode* found = search(head, "c");
	printf("%s\n", found->data);

	printf("%d \n", get_size(head));
}