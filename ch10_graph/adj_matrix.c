#include "queue.h"
#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

typedef struct graph {
    int n; // 정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} graph;

void init(graph *graph)
{
    int r, c;
    graph ->n = 0;

    for (r = 0; r < MAX_VERTICES; r++)
        for (c = 0; c < MAX_VERTICES; c++)
            graph->adj_mat[r][c] = 0;
}

void insert_vertex(graph* graph, int v)
{
    if ((graph->n + 1) > MAX_VERTICES) {
        fprintf(stderr, "more than graph max vertices");
        return;
    }

    graph->n++;
}

void insert_edge(graph* graph, int start, int end)
{
    if (start >= graph->n || end >= graph->n) {
        fprintf(stderr, "no such vertex");
        return;
    }

    graph->adj_mat[start][end] = 1;
    graph->adj_mat[end][start] = 1;
}

void print_adj_mat(graph* graph)
{
    for (int i =0; i<graph->n; i++) {
        for (int j =0; j<graph->n; j++) {
            printf("%2d ", graph->adj_mat[i][j]);
        }
        printf("\n");
    }
}

/* 정점의 차수를 계산 */
int get_degree(graph* g, int v)
{
    int degree = 0;
    for (int i =0; i < g->n; i++) 
    {
        if (g->adj_mat[v][i] == 1) degree++;
    }

    return degree;
}

int visited[MAX_VERTICES]; // dfs용 방문 여부 배열 

void dfs_mat(graph* g, int v)
{
    printf("%d -> ", v);
    visited[v] = 1;

    for (int i = 0; i < g->n; i++) {
        if (g->adj_mat[v][i] == 1 && visited[i] != 1) {
            dfs_mat(g, i);
        }
    }

    printf("\n");
}

int visited_bfs[MAX_VERTICES];
void bfs_mat(graph* g, int v)
{
    QueueType *q = malloc(sizeof(QueueType));
    init_queue(q);
    visited_bfs[v] = TRUE;
    printf("%d -> ", v);

    enqueue(q, v);
    while(!is_empty_q(q)) {
        v = dequeue(q);
        for (int i = 0; i < g->n; i++) {
            if(g->adj_mat[v][i] && !visited_bfs[i]) {
                visited_bfs[i] = TRUE;
                printf("%d -> ", i);
                enqueue(q, i);
            }
        }
    }
}

/* 12번 */
void read_graph_mat(graph* g, char* name) 
{
    FILE* fr;

    int vertices;
    
    fr = fopen(name, "r");
    fscanf(fr, "%d", &vertices);
    g->n = vertices;

    for (int i =0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            fscanf(fr, "%d", &g->adj_mat[i][j]);
        }
    }

    fclose(fr);
}

void write_graph_mat(graph* g, char* name) 
{
    int vertices = g->n;
    FILE* fr = fopen(name, "w");
    fprintf(fr, "%d\n", vertices);
    
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            fprintf(fr, "%d ", g->adj_mat[i][j]);
        }
        fprintf(fr, "\n");
    }
}

int main()
{
    graph* g;
    g = (graph*)malloc(sizeof(graph));
    init(g);

    for (int i =0; i < 4; i++) 
        insert_vertex(g, i);
    
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);
    print_adj_mat(g);
    printf("\n");

    write_graph_mat(g, "write.txt");

    free(g);
}