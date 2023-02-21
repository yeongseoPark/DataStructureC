#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 // 실제 무한대는 아님 (연결이 없는경우)

typedef struct Graph {
    int n; // 정점 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} Graph;

int distance[MAX_VERTICES]; // 시작정점으로부터 최단경로 거리
int found[MAX_VERTICES];    // 최단거리를 기록한(방문한) 정점

/* 최단경로 배열의 최소값의 인덱스 */
int choose(int distance[], int n, int found[])
{
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;

    for (i = 0; i < n; i++)
    {
        if(distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }

    return minpos;
}

/* 탐색 과정 출력 */
void print_status(Graph* g)
{
    static int step = 1;
    printf("STEP %d: ", step++);
    printf("distance: ");

    for (int i = 0; i < g->n; i++) 
    {
        if (distance[i] == INF)
            printf(" * ");
        else 
            printf("%2d ", distance[i]);
    }

    printf("\nfound : ");
    for (int i = 0; i < g->n; i++) {
        printf("%2d ", found[i]);
    }
    printf("\n");
}



void shortest_path(Graph* g, int start) 
{
    int path[g->n];
    int pathIndex = 0;
    path[pathIndex++] = start;

    int i, j, minpos;
    for (i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i];
        found[i] = FALSE;
    }
    
    found[start] = TRUE;
    distance[start] = 0;

    for (i = 0; i < g->n-1; i++) // start에서 한번 연산을 실행했으므로 vertex개수 -1 만큼 반복문 진행
    {
        print_status(g);
        minpos = choose(distance, g->n, found);
        path[pathIndex++] = minpos;

        found[minpos] = TRUE;

        for(j = 0; j < g->n; j++) {
            if (!found[j]) {
                if (distance[minpos] + g->weight[minpos][j] < distance[j]) {
                    distance[j] = distance[minpos] + g->weight[minpos][j];
                }
            }
        }
    }

    printf("\npath : ");
    for (i = 0 ; i < g->n; i++)
        printf("%2d ->", path[i]);
}

int main(void)
{
    Graph g = {7,
        {
            {0, 7, INF, INF, 3, 10, INF},
            {7, 0, 4, 10, 2, 6, INF},
            {INF, 4, 0, 2, INF, INF, INF},
            {INF, 10, 2, 0, 11, 9, 4},
            {3, 2, INF, 22, 0, INF, 5},
            {10, 6, INF, 9, INF, 0, INF},
            {INF, INF, INF, 4, 5, INF, 0}
        }};

    shortest_path(&g, 0);
    return 0;
}