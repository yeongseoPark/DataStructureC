#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

/* 최소 dist[v] 값을 갖는 정점v 반환 */
int get_min_distance_vertex(int n)
{
    int v,i;
    for (i = 0; i < n; i++)
    {
        if (!selected[i]) {
            v = i; // 비교의 기준점 설정
            break;
        }
    }

    for (i = 0; i < n; i++)
    {
        if(!selected[i] && (distance[i] < distance[v])) v = i;
    }

    return v;
}

void prim(GraphType* g, int s) 
{
    int v;
    for (int i = 0; i < g->n; i++)
        distance[i] = INF;
    distance[s] = 0;

    for (int i = 0; i < g->n; i++) {
        v = get_min_distance_vertex(g->n);  //이전 노드와 연결된 노드 중 가장 dist값이 작은, 혹은 시작점인 시작
        if (distance[v] == INF) return; // 갈수있는 노드가 없음, 실패
        selected[v] = TRUE;
 
        printf("vertext %d selected. \n", v);

        for (int i = 0; i < g->n; i++)
        {
            if (g->weight[v][i] != INF) {
                if (!selected[i] && g->weight[v][i] < distance[i])
                    distance[i] = g->weight[v][i];
            }
        }
    }
}

int main(void)
{
    GraphType g = {7,
        {
            {0, 29, INF, INF, INF, 10, INF},
            {29, 0, 16, INF, INF, INF, 15},
            {INF, 16, 0, 12, INF, INF, INF},
            {INF, INF, 12, 0, 22, INF, 18},
            {INF, INF, INF, 22, 0, 27, 25},
            {10, INF, INF, INF, 27, 0, INF},
            {INF, 15, INF, 18, 25, INF, 0}
        }};

    prim(&g, 0);
    return 0;
}
