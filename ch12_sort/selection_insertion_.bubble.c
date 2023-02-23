#include <stdio.h>
#define SWAP(x,y,t) ( (t) = (x), (x) = (y), (y) = (t))

/* 오름차순 */

void selection_sort(int list[], int n)
{
    int i,j,least,k;

    for (i = 0; i < n-1; i++) {
        least = i;
        for(j = i+1; j < n; j++) {
            if (list[j] < list[least]) {
                least = j;
            }
        }

        if (least == i) continue; // 자기자신과의 이동 막음(정렬된경우)
        SWAP(list[i], list[least], k);
    }
}


void insertion_sort(int list[], int n)
{
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = list[i];
        j = i-1;
        while (j >= 0 && list[j] > key) {
            list[j+1] = list[j];
            j -= 1;
        }

        list[j+1] = key;
    }
}

void bubble_sort(int list[], int n)
{
    int i, j, tmp;

    for (i = n-1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (list[j] > list[j+1]) {
                SWAP(list[j], list[j+1], tmp);
            }
        }
    }
}

int main(void) 
{
    int arr[9] = {3,1,4,6,2,9,8,11,10};

    bubble_sort(arr, 9);

    for (int i = 0; i < 9; i++) printf("%d -> ", arr[i]);
}