#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 // 실제 무한대는 아님 (연결이 없는경우)


/** 인접리스트로 구현한 그래프의 다익스트라 알고리즘 **/

typedef struct GraphNode {
    int vertex;
    int weight; // adj_list의 해당인덱스부터 node까지의 가중치
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n; // 정점의 개수
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

void graph_init(GraphType* g)
{
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        g->adj_list[i] = NULL;
}

// 정점 삽입 
void insert_vertex(GraphType* g, int v)
{
    if ((g->n) + 1 > MAX_VERTICES) {
        fprintf(stderr, "vertex number overflow");
    }

    g->n++;
}

/* v를 u의 인접 리스트에 삽입 */
void insert_edge(GraphType* g, int u, int v, int weight)
{
    GraphNode *node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "vertex number error");
        return;
    }

    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->weight = weight;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}


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

void print_status(GraphType* g)
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

void shortest_path(GraphType* g, int start)
{
    int i, minpos;
    GraphNode* node = g->adj_list[start];

    while (node != NULL)
    {
        distance[node->vertex] = node->weight;
        node = node->link;
    }

    for (i = 0; i < g->n; i++) {
        if (i != start && distance[i] == 0) distance[i] = INF;
        found[i] = FALSE;
    }

    found[start] = TRUE;
    distance[start] = 0;
    
    for (i = 0; i < g->n-1; i++) 
    {
        print_status(g);
        minpos = choose(distance, g->n, found);
        found[minpos] = TRUE;
        node = g->adj_list[minpos];
        while (node != NULL)
        {
            if (!found[node->vertex]) 
            {   
                if (distance[minpos] + node->weight < distance[node->vertex]) {
                    distance[node->vertex] = distance[minpos] + node->weight;
                }
            }
            node = node->link;
        }
    }
}

int main(void) 
{
    GraphType g;

    graph_init(&g);
    insert_vertex(&g, 0);
    insert_vertex(&g, 1);
    insert_vertex(&g, 2);
    insert_vertex(&g, 3);
    insert_vertex(&g, 4);
    insert_vertex(&g, 5);
    insert_vertex(&g, 6);

    insert_edge(&g, 0, 1, 7);
    insert_edge(&g, 1, 0, 7);
    insert_edge(&g, 0, 4, 3);
    insert_edge(&g, 4, 0, 3);
    insert_edge(&g, 0, 5, 10);
    insert_edge(&g, 5, 0, 10);
    insert_edge(&g, 1, 2, 4);
    insert_edge(&g, 2, 1, 4);
    insert_edge(&g, 1, 3, 10);
    insert_edge(&g, 3, 1, 10);
    insert_edge(&g, 1, 5, 6);
    insert_edge(&g, 5, 1, 6);
    insert_edge(&g, 1, 4, 2);
    insert_edge(&g, 4, 1, 2);
    insert_edge(&g, 2, 3, 2);
    insert_edge(&g, 3, 2, 2);
    insert_edge(&g, 3, 4, 11);
    insert_edge(&g, 4, 3, 11);
    insert_edge(&g, 3, 5, 9);
    insert_edge(&g, 5, 3, 9);
    insert_edge(&g, 3, 6, 4);
    insert_edge(&g, 6, 3, 4);
    insert_edge(&g, 4, 6, 5);
    insert_edge(&g, 6, 4, 5);

    shortest_path(&g, 0);
}