#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define BUCKETS 10
#define DIGITS 4

void radix_sort(int list[], int n)
{
    int i,b,d,factor = 1;
    Queue queues[BUCKETS];

    for (b = 0; b < BUCKETS; b++) init(&queues[b]);

    for (d = 0; d < DIGITS; d++) 
    {
        for (i = 0; i < n; i++)
            enqueue(&queues[(list[i] / factor) % 10], list[i]);
        
        /* 버킷의 값을 리스트로 이동 */
        for (b = i = 0; b < BUCKETS; b++)
            while (!is_empty(&queues[b]))
                list[i++] = dequeue(&queues[b]);

        /* 높은 자리수로 이동 */
        factor *= 10;
    }
}

int arr[9] = {532,312,818,42,9,100,6001,234,762};

int main(void)
{
    radix_sort(arr, 9);

    for (int i = 0; i < 9; i++)
        printf("%d ", arr[i]);

    return 0;
}