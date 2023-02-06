#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#define MAX_LIST_SIZE 100

typedef struct {
	int list[MAX_LIST_SIZE];
	int length;
} ArrayList;


void error_al(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_al(ArrayList* al)
{
	al->length = 0;
}

bool is_full_al(ArrayList* al)
{
	return (al->length == MAX_LIST_SIZE);
}

void add_al(ArrayList* al, int item)
{
	if (is_full_al(al)) error_al("already full");

	int i = 0;
	for (i = 0; i < al->length; i++) {
		if (item < al->list[i]) {
			for (int j = al->length; j > i; j--) {
				al->list[j] = al->list[j - 1];
			}
			break;
		}
	}

	al->list[i] = item;
	al->length++;
}

bool is_in_list_al(ArrayList* al, int item)
{
	for (int i = 0; i < al->length; i++) {
		if (al->list[i] == item) return true;
	}

	return false;
}

void delete_al(ArrayList* al, int item)
{
	if (!is_in_list_al(al, item)) 
		error("not in list\n");

	for (int i = 0; i < al->length; i++)
	{
		if ((al->list[i]) == item) {
			for (int j = i; j < al->length - 1; j++) {
				al->list[j] = al->list[j + 1];
			}
			break;
		}
	}

	al->length--;
}

void clear_al(ArrayList* al)
{
	al->length = 0;
}

int get_length_al(ArrayList* al)
{
	return al->length;
}

bool is_empty_al(ArrayList* al)
{
	return (al->length == 0);
}

void display_al(ArrayList* al)
{
	for (int i = 0; i < al->length; i++)
		printf("%d -> ", al->list[i]);
	printf("\n");
}

int main4(void)
{
	ArrayList* al = (ArrayList*)malloc(sizeof(ArrayList));
	init_al(al);
	add_al(al, 3);
	add_al(al, 2);
	add_al(al, 5);
	add_al(al, 4);
	add_al(al, 6);

	display_al(al);

	delete_al(al, 3);

	display_al(al);

	printf("%d\n", get_length_al(al));
	
	printf("%s\n", is_full_al(al) ? "true" : "false");

	clear_al(al);

	printf("%s\n", is_empty_al(al) ? "true" : "false");
}
