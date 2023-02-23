#include <stdio.h>
#define MAX_SIZE 1000

int count = 0;
int sorted[MAX_SIZE];

void merge(int list[], int left, int mid, int right)
{
    count++;
    int i,j; // 왼쪽리스트 인덱스 | 오른쪽 리스트 인덱스
    int k; // 정렬될 리스트에 대한 인덱스
    int p;

    i = left;
    j = mid + 1;
    k = left;

    while (i <= mid && j <= right)
    {
        if (list[i] <= list[j])
            sorted[k++] = list[i++];
        if (list[i] > list[j])
            sorted[k++] = list[j++];
    }

    if (i > mid)
        for (p = j; p <= right; p++)
            sorted[k++] = list[p];
    else
        for (p = i; p <= mid; p++)
            sorted[k++] = list[p];
    
    for (p = left; p <= right; p++)
        list[p] = sorted[p];
}

void merge_sort(int list[], int left, int right)
{
    int mid;
    
    if (left < right)
    {
        mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid+1, right);
        merge(list, left, mid, right);
    }
}

int main(void)
{
    int arr[8] = {8, 2, 5, 7, 6, 4, 1, 3};

    merge_sort(arr, 0, 7);

    for (int i = 0; i < 7; i++) printf("%d -> ", arr[i]);
}