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

ListNode* delete_odd(ListNode* head) { // 홀수 노드만 삭ㅈ[
	int i = 1;
	ListNode* front = head;
	ListNode* back = front;
	front = front->link;
	back = back->link;
	ListNode* ans = back;

	while (front != NULL) {
		if (i % 2 == 0) {
			back->link = front->link;
			back = back->link;
		}
		i++;
		front = front->link;
	}

	return ans;
}

ListNode* alternate(ListNode* first, ListNode* second)
{
	ListNode* a = first;
	ListNode* b = second;
	ListNode* c = a;
	a = a->link; // 없으면 c가 자신을 무한참조
	ListNode* ans = c;

	int i = 1;

	while (a != NULL && b != NULL) 
	{
		if (i % 2 == 0) {
			c->link = a;
			a = a->link;
			c = c->link;
		}
		else {
			c->link = b;
			b = b->link;
			c = c->link;
		}

		i++;
	}

	if (a != NULL) {
		c->link = a;
	}

	if (b != NULL) {
		c->link = b;
	}

	return ans;
}

ListNode* merge(ListNode* first, ListNode* second) // 오름차순 정렬상태 유지하며 합병
{
	ListNode* a = first;
	ListNode* b = second;
	ListNode* c;

	if (a->data > b->data) {
		c = b;
		b = b->link;
	}
	else {
		c = a;
		a = a->link;
	}

	ListNode* ans = c;

	while (a != NULL && b != NULL) 
	{
		if (a->data > b->data) {
			c->link = b;
			c = c->link;
			b = b->link;
		}
		else {
			c->link = a;
			c = c->link;
			a = a->link;
		}
	}

	if (a != NULL) {
		c->link = a;
	}

	if (b != NULL) {
		c->link = b;
	}

	return ans;
}

void insert_node_back(ListNode** phead, ListNode* new_node) {
	if (*phead == NULL) {
		new_node->link = NULL;
		*phead = new_node;
	}
	else {
		new_node->link = NULL;
		ListNode* p = *phead;
		while (p->link != NULL)
			p = p->link;
		p->link = new_node;
	}
}

ListNode* split(ListNode** ans1, ListNode** ans2, ListNode* node) 
{
	ListNode* goer = node;
	*ans1 = NULL;
	*ans2 = NULL;

	int i = 1;

	while (goer != NULL)
	{
		ListNode* tmp = (ListNode*)malloc(sizeof(ListNode));
		tmp->data = goer->data;
		tmp->link = NULL;

		if (i % 2 == 1) {
			insert_node_back(ans1, tmp);
		}
		else {
			insert_node_back(ans2, tmp);
		}

		goer = goer->link;
		i++;
	}
}


int main2(void)
{
	ListNode* head = NULL;
	ListNode* head2 = NULL;

	for (int i = 9; i >= 0; i--)
	{
		if (i % 2 == 0) 
			head = insert_first(head, i);
	}

	for (int i = 9; i >= 5; i--)
	{
		head2 = insert_first(head2, i);
	}

	print_list(head);
	print_list(head2);

	ListNode* c = merge(head, head2);
	print_list(c);

	ListNode* a, *b;
	split(&a, &b, c);
	print_list(a);
	print_list(b);

	return 0;
}

