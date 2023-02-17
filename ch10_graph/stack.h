#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef struct stack {
    int data[MAX_STACK_SIZE];
    int top;
} stack;

void init_stack(stack* s)
{
    s->top = -1;
}

int is_empty(stack* s)
{
    return s->top == -1;
}

int is_full(stack* s)
{
    return (s->top == MAX_STACK_SIZE - 1);
}

void push(stack* s, int item)
{
    if (is_full(s)) {
        fprintf(stderr,"stack is full");
        return;
    }

    s->data[++(s->top)] = item;
}

int pop(stack* s)
{
    if (is_empty(s)) {
        fprintf(stderr,"stack is empty");
        return;
    }

    return s->data[(s->top)--];
}