#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; // 부모 포인터포현의 1차원 배열 구현

void set_init(int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = -1;
    }
}

/* curr이 속하는 집합을 반환 */
int set_find(int curr)
{
    if (parent[curr] == -1) return curr;

    while (parent[curr] != -1) curr = parent[curr];

    return curr;
}

/* 두개의 원소가 속한 집합을 합친다 */
void set_union(int a, int b)
{
    int a_root = set_find(a);
    int b_root = set_find(b);

    if (a_root != b_root)
        parent[a_root] = b_root;
}

/* 간선을 나타내는 구조체 */
struct Edge {
    int start, end, weight;
};

typedef struct Graph {
    int n; // 간선의 개수
    int vertex; // 정점의 개수
    struct Edge edges[2*MAX_VERTICES]; 
} Graph;

void graph_init(Graph* g)
{
    g->n = g->vertex = 0;
    for (int i = 0; i < 2*MAX_VERTICES; i++)
    {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

/* 간선 삽입 연산 */
void insert_edge(Graph* g, int start, int end, int w)
{
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

/* qsort의 네번째 인자인 비교 함수 */
int compare(const void* a, const void *b)
{
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}

void kruskal(Graph* g)
{
    int edge_accepted; // 현재까지 선택된 간선의 수
    int uset, vset; // 정점u와 v의 집합번호
    struct Edge e;

    set_init(g->vertex);
    qsort(g->edges, g->n, sizeof(struct Edge), compare); // g의 edges배열을 오름차순 정렬 

    printf("kruskal MST algorithm \n");
    int i = 0;
    while (edge_accepted < (g->vertex - 1)) // 최소신장트리의 간선개수는 정점개수 - 1
    {
        e = g->edges[i];
        uset = set_find(e.start);
        vset = set_find(e.end);

        if (uset != vset) { // 사이클을 형성하지 않는 (=서로 다른 집합에 속하는)
            printf("edge (%d, %d) of weight %d selected\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
        i++;
    }
}

int main(void)
{
    Graph* g;
    g = (Graph*)malloc(sizeof(Graph));
    graph_init(g);

    g->vertex = 7;
    insert_edge(g, 0, 1, 29);
    insert_edge(g, 1, 2, 16);
    insert_edge(g, 2, 3, 12);
    insert_edge(g, 3, 4, 22);
    insert_edge(g, 4, 5, 27);
    insert_edge(g, 5, 0, 10);
    insert_edge(g, 6, 1, 15);
    insert_edge(g, 6, 3, 18);
    insert_edge(g, 6, 4, 25);

    kruskal(g);
    free(g);
    return 0;
}