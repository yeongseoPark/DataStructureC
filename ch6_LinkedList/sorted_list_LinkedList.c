#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

typedef struct listnode {
	int num;
	struct listnode* link;
} listnode;

typedef struct {
	listnode* head;
	listnode* tail;
	int length;
} lltype;


listnode* create_ll(int data) 
{
	listnode* node;
	node = (listnode*)malloc(sizeof(listnode));
	node->num = data;
	node->link = NULL;
	return node;
}

lltype* init_ll()
{
	lltype* ll = (lltype*)malloc(sizeof(lltype));

	ll->head = ll->tail = NULL;
	ll->length = 0;
	return ll;
}

void add_ll(lltype* ll, int item)
{
	listnode* tmp = (listnode*)malloc(sizeof(listnode));
	tmp->num = item;

	listnode* front = ll->head;
	listnode* back = NULL;

	if (front == NULL) {
		tmp->link = NULL;
		ll->head = ll->tail = tmp;
		ll->length = 1;
		return;
	}

	while (front != NULL && item >= front->num) {
		back = front;
		front = front->link;
	}

	if (back == NULL) {
		tmp->link = ll->head;
		ll->head = tmp;
	}
	else {
		if (front == NULL) {
			ll->tail->link = tmp;
			tmp->link = NULL;
			ll->tail = ll->tail->link;
		}
		else {
			back->link = tmp;
			tmp->link = front;
		}
	}

	ll->length++;
}

void delete_ll(lltype* ll, int item)
{
	listnode* removed = ll->head;
	listnode* pre = NULL;

	while (removed->num != item) {
		pre = removed;
		removed = removed->link;
	}

	if (pre == NULL) {// 시작지점 삭제
		ll->head = ll->head->link;
	}
	else {
		pre->link = removed->link;
	}

	ll->length--;
}

void clear_ll(lltype* ll)
{
	ll->head = NULL;
	ll->tail = NULL;
	ll->length = 0;
}

bool is_in_ll(lltype* ll, int item)
{
	listnode* p = ll->head;
	while (p != NULL) {
		if (p->num == item) return true;
		p = p->link;
	}

	return false;
}

int get_length_ll(lltype* ll)
{
	return ll->length;
}

bool is_empty_ll(lltype* ll)
{
	return (ll->length == 0);
}

bool is_full_ll(lltype* ll)
{
	listnode* new_node = create_ll(0);
	return (new_node == NULL);
}

void display_ll(lltype* ll)
{
	listnode* p = ll->head;
	while (p != NULL) {
		printf("%d -> ", p->num);
		p = p->link;
	}
	printf("\n");
}

int main(void) {

	lltype* ll = init_ll();

	add_ll(ll, 3);
	add_ll(ll, 2);
	add_ll(ll, 5);
	add_ll(ll, 4);
	add_ll(ll, 1);

	display_ll(ll);

	delete_ll(ll, 3);
	printf("%s\n", is_in_ll(ll, 3) ? "true" : "false");
	printf("%s\n", is_in_ll(ll, 4) ? "true" : "false");

	display_ll(ll);

	printf("%d\n", get_length_ll(ll));
	printf("%s\n", is_empty_ll(ll) ? "true" : "false");

	clear_ll(ll);
	printf("%s\n", is_empty_ll(ll) ? "true" : "false");
	display_ll(ll);
}