#include <stdio.h>
#define INDEX_SIZE 3

typedef struct itable {
    int key;
    int index;
} itable;

itable index_list[INDEX_SIZE] = {{3,0}, {22,3}, {67,6}};

int list[9] = { // 주자료 테이블
    3, 9, 15, 22, 31, 55, 67, 88, 91
}; 

int search_index(int key, int n)
{
    int i, low, high;

    if (key < list[0] || key > list[n-1]) return -1;

    for (i = 0; i < INDEX_SIZE; i++) 
    {
        if(index_list[i].key <= key && key < index_list[i+1].key) break;
    }

    /* i가 INDEX_SIZE -1 에 도달하면 무조건 위의 조건 충족할 수 없기에 i = INDEX_SIZE가 됨 */
    if (i == INDEX_SIZE) 
    {
        low = index_list[INDEX_SIZE - 1].index;
        high = n;
    }
    else 
    {
        low = index_list[i].index;
        high = index_list[i+1].index;
    }

    for (i = low; i < high; i++)
        if (list[i] == key) return i;
    
    return -1;
}

int main(void)
{
    printf("%d \n", search_index(9, 9));
    printf("%d \n", search_index(22, 9));
    printf("%d \n", search_index(55, 9));
    printf("%d \n", search_index(67, 9));
    printf("%d \n", search_index(91, 9));
    printf("%d \n", search_index(92, 9));
}