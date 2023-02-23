#include <stdio.h>
#include <stdlib.h>
#define SWAP(a, b, c) ((c) = (a), (a) = (b), (b) = (c))

int arr[9] = {5,3,8,4,9,1,6,2,7};

int partition(int list[], int left, int right)
{
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];

    do {
        do
        {
            low++;
        } while (list[low] < pivot);
        
        do
        {
            high--;
        } while (list[high] > pivot);

        if (low < high) SWAP(list[low], list[high], temp);
    } while (low < high);

    SWAP(list[left], list[high], temp);
    return high;
}

void quick_sort(int list[], int left, int right)
{
    if (left < right)
    {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}

int main(void)
{
    quick_sort(arr, 0, 8);

    for (int i = 0; i < 9; i++)
        printf("%d ", arr[i]);

    
    return 0;
}