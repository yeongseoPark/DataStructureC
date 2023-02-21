#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct Graph
{
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
} Graph;

int A[MAX_VERTICES][MAX_VERTICES];

void printA(Graph* g)
{
    int i, j;

    printf("=============================\n");
    for (i = 0; i< g->n; i++) {
        for (j=0; j <g->n; j++) {
            if (A[i][j] == INF)
                printf(" * ");
            else
                printf("%2d ", A[i][j]);
        }
        printf("\n");
    }
    printf("=============================\n");

}

void floyd(Graph *g)
{
    int i, j, k;
    for (i = 0; i < g->n; i++)
        for (j = 0; j < g->n; j++)
            A[i][j] = g->weight[i][j];
    
    for (k = 0; k < g->n; k++) {
        for (i = 0; i < g->n; i++) {
            for (j = 0; j < g->n; j++) {
                if (A[i][k] + A[k][j] < A[i][j])
                    A[i][j] = A[i][k] + A[k][j];
            }
        }

        printA(g);
    }
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

    floyd(&g);
    return 0;
}