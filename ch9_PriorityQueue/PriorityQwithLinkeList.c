#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
    int data;
    struct node* next;
} node;

typedef struct LinkedList {
    node* root;
    int size;
} LinkedList;

void init(LinkedList* ll) {
    ll->size = 0;
}

LinkedList* create() {
    return (LinkedList*)malloc(sizeof(LinkedList));
}

/* 정렬된 연결리스트 */
LinkedList* insert(LinkedList* head, int data)
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp->data = data;

    if (head->size == 0) {
        tmp->next = NULL;
        head->root = tmp;
        head->size++;
        return head;
    } 
    else if (head->size == 1) {
        if (head->root->data < data) {
            tmp->next = head->root;
            head->root = tmp;
        } else {
            head->root->next = tmp;
            tmp->next = NULL;
        }

        head->size++;
        return head;
    }

    node* pre = head->root;
    node* front = head->root->next;

    while (pre && front && front->data > data) {
        pre = pre->next;
        front = front->next;
    } 

    if (front == NULL) {
        pre->next = tmp;
        tmp->next = NULL;
    } else {
        pre->next = tmp;
        tmp->next = front;
    }

    head->size++;

    return head;
}

int delete(LinkedList* head)
{
    node* nde = head->root;
    head->root = head->root->next;
    head->size--;

    return nde->data;
}

int main()
{
    LinkedList* list = create();
    init(list);

    insert(list, 10);
    insert(list, 12);
    insert(list, 5);
    insert(list, 7);
    insert(list, 2);

    printf("%d ", delete(list));
    printf("%d ", delete(list));
    printf("%d ", delete(list));
    printf("%d ", delete(list));
    printf("%d ", delete(list));
}