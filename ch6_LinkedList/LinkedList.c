#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode* head, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;

	return head;
}

/* pre뒤에 새로운 노드 삽입 */
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;

	pre->link = p;

	return head;
}

ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;
	head = head->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("Null \n");
}

element get_entry(ListNode* L, int index)
{
	for (int i = 0; i < index; i++) {
		L = L->link;
	}
	return L->data;
}

ListNode* search_list(ListNode* head, element x)
{
	ListNode* p = head;

	while (p != NULL) {
		if (p->data == x) return p;
		p = p->link;
	}

	return NULL;
}

int get_length(ListNode* head)
{
	int len = 0;
	while (head != NULL) {
		len++;
		head = head->link;
	}
	return len;
}

ListNode* concat(ListNode* head1, ListNode* head2)
{
	if (head1 == NULL) return head2;
	if (head2 == NULL) return head1;

	ListNode* p = head1;
	while (p->link != NULL)
		p = p->link;
	p->link = head2;

	return head1;
}

ListNode* reverse(ListNode* head)
{
	ListNode *next, *middle, *before;
	next = head;
	middle  = NULL;

	while (next != NULL) {
		before = middle;
		middle = next;

		next = next->link;
		middle->link = before;
	}

	return middle;
}

void certain_delete(ListNode* head, element val)
{
	ListNode* pre = head;
	ListNode* cur = head;

	if (cur->data == val) {
		head = head->link;
		return;
	}

	cur = cur->link;
	while (cur->data != val) {
		pre = pre->link;
		cur = cur->link;
	}

	pre->link = cur->link;
	return;
}

element* find_maxmin(ListNode* head) {
	static element minMax[2] = {INT_MAX,INT_MIN};

	ListNode* p = head;

	while (p != NULL) {
		if (minMax[0] > p->data) minMax[0] = p->data;

		if (minMax[1] < p->data) minMax[1] = p->data;

		p = p->link;
	}

	return minMax;
}




int main(void)
{
	ListNode* head = NULL;
	ListNode* head2 = NULL;

	for (int i = 0; i < 5; i++)
	{
		head = insert_first(head, i);
	}

	for (int i = 5; i < 10; i++)
	{
		head2 = insert_first(head2, i);
	}

	concat(head, head2);
	print_list(head);
	
	ListNode* reversed = NULL;
	reversed = reverse(head);
	print_list(reversed);

	certain_delete(reversed, 2);
	print_list(reversed);

	int* p = find_maxmin(reversed);
	printf("min : %d , max : %d\n", *(p +0), *(p+1));

	return 0;
}