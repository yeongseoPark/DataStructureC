#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100

typedef struct GraphNode {
    int vertex;
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
void insert_edge(GraphType* g, int u, int v)
{
    GraphNode *node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "vertex number error");
        return;
    }

    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

int topo_sort(GraphType *g)
{
    int i;
    stack s;
    GraphNode *node;

    int *in_degree = (int*)malloc(sizeof(int) * g->n); // 정점들의 진입차수 배열
    int visited[g->n]; 

    /* 진입차수 배열(및 visited) 초기화 */
    for (i = 0; i < g->n; i++){
        in_degree[i] = 0;
        visited[i] = FALSE;
    }
    for (i = 0; i < g->n; i++) {
        node = g->adj_list[i];
        while (node != NULL) {
            in_degree[node->vertex]++;
            node = node->link;
        }
    }

    /* 진입차수 0인 노드 스택에 삽입 */
    init_stack(&s);
    for (i = 0 ; i < g->n; i++) {
        if (in_degree[i] == 0) {
            push(&s, i);
            visited[i] = TRUE;
        }
    }

    while (!is_empty(&s)) {
            int poped = pop(&s);
            visited[poped] = TRUE;
            printf("%d -> ", poped);

            /* 스택에서 꺼낸 후보 정점에 인접한 정점들의 차수 1씩 감소 */
            node = g->adj_list[poped];
            while (node != NULL) {
                in_degree[node->vertex]--;
                node = node->link;
            }
            /* 새로이 in_degree가 0 된 후보정점들 탐색 */
            for (i = 0 ; i < g->n; i++) {
                if (in_degree[i] == 0 && !visited[i]) {
                    push(&s, i);
                }
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

    insert_edge(&g, 0, 2);
    insert_edge(&g, 1, 4);
    insert_edge(&g, 0, 3);
    insert_edge(&g, 1, 3);
    insert_edge(&g, 2, 3);
    insert_edge(&g, 3, 5);
    insert_edge(&g, 2, 5);
    insert_edge(&g, 4, 5);

    topo_sort(&g);
    return 0;
}