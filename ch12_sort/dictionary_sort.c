#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(a, b, c) ((c) = (a), (a) = (b), (b) = (c))
#define MAX_WORD_SIZE 20

typedef struct element
{
    char word[MAX_WORD_SIZE];
    char meaning[MAX_WORD_SIZE];
} element;

#define MAX_QUEUE_SIZE 100

typedef struct Queue {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(Queue* q)
{
    q->front = q->rear = 0;
    for (int i = 0; i < MAX_WORD_SIZE; i++) {
        q->data->meaning[i] = NULL;
        q->data->word[i] = NULL;
    } 
}

int is_empty(Queue* q)
{
    return (q->front == q->rear);
}

int is_full(Queue* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(Queue* q, element data)
{
    if (is_full(q))
        error("already full");

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    
    q->data[q->rear] = data;
}

element dequeue(Queue* q)
{
    if (is_empty(q))
        error("empty Queue");
    
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

char tolower(char a)
{
    if ('a' <= a && a <= 'z') return a;
    
    return a + 32;
}

#define BUCKETS 26
#define DIGITS 20
#define SIZE 3

void radix_sort(element list[], int n)
{
    int i,b,d,factor = MAX_WORD_SIZE - 1;
    Queue queues[BUCKETS];

    for (b = 0; b < BUCKETS; b++) init(&queues[b]);

    for (d = 0; d < factor; d++) 
    {
        for (i = 0; i < n; i++) {
            int index = (list[i].word[d] == NULL) ? 0 : tolower(list[i].word[d]) - 'a';
            enqueue(&queues[index], list[i]);
        }
        
        
        /* 버킷의 값을 리스트로 이동 */
        for (b = i = 0; b < BUCKETS; b++)
            while (!is_empty(&queues[b]))
                list[i++] = dequeue(&queues[b]);

        factor --;
    }
}

element list[SIZE];

int main(void)
{
    int i;

    printf("input word and meaing in one line\n");

    for (i = 0; i < SIZE; i++) {
        scanf("%s[^\n]", list[i].word); // 엔터키만 제외
        scanf("%s[^\n]", list[i].meaning);
    }

    radix_sort(list, SIZE);

    for (i = 0; i < SIZE; i++) 
        printf("%s -> ", list[i].word);
}