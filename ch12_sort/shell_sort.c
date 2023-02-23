#include <stdio.h>

/* 정렬의 범위 first ~ last */
void insertion_sort_shell(int list[], int first, int last, int gap)
{
    int i,j,key;

    for (i = first + gap; i <= last; i = i + gap) {
        key = list[i];
        for (j = i - gap; j >= first && key < list[j]; j = j - gap) {
            list[j+gap] = list[j];
        }

        list[j+gap] = key;
    }
}

void shell_sort(int list[], int n) 
{
    int i, gap;
    gap = n/2;

    while (gap != 0)
    {
        /* 부분리스트의 개수는 gap */
        for (i = 0; i < gap; i++)
            insertion_sort_shell(list, i, n-1, gap);
        gap = gap / 2;
    }
}

int main(void) 
{
    int arr[9] = {3,1,4,6,2,9,8,11,10};

    shell_sort(arr, 9);

    for (int i = 0; i < 9; i++) printf("%d -> ", arr[i]);
}