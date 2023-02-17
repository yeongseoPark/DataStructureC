#include "stack.h"
#include "queue.h"

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
typedef struct GraphNode
{
    int vertext;
    struct GraphNode* link;
} GraphNode;

typedef struct Graph 
{
    int number; // 정점의 개수
    GraphNode* adj_list[MAX_VERTICES];
} Graph;

void init(Graph* g){
    g->number = 0;
    for (int v = 0; v < MAX_VERTICES; v++)
    {
        g->adj_list[v] = NULL;
    }
}

void insert_vertex(Graph* g, int v)
{
    if ((g->number) + 1 > MAX_VERTICES) {
        fprintf(stderr, "more than maximum vertex number");
        return;
    } 

    g->number++;
}

/* v를 u의 인접 리스트에 삽입 */
void insert_edge(Graph*g, int u, int v)
{
    GraphNode* node;
    if (u >= g->number || v >= g->number) {
        fprintf(stderr, "no such vertex number");
        return;
    }

    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertext = v;

    // 연결리스트 맨처음에 삽입
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

void print_adj_list(Graph* g)
{
    for (int i = 0; i < g->number; i++){
        GraphNode* p = g->adj_list[i];
        printf("linked list of Vertext %d : ", i);
        while (p!=NULL) {
            printf("%d -> ", p->vertext);
            p = p->link;
        }
        printf("\n");
    }
}

int get_degree(Graph* g, int v)
{
    int degree = 0;
    GraphNode* p = g->adj_list[v];
    while (p != NULL)
    {
        degree++;
        p = p->link;
    }

    return degree;
}

int visited[MAX_VERTICES];
void dfs_list(Graph* g, int v)
{
    visited[v] = TRUE;
    printf("%d -> ", v);
    GraphNode* p = g->adj_list[v];

    while (p != NULL)
    {
        if (visited[p->vertext] == FALSE)
            dfs_list(g, p->vertext);
        p = p->link;
    }
}

int visted_stack[MAX_VERTICES];
void dfs_iterative(Graph* g, int v)
{
    GraphNode *tmp;
    stack* s = (stack*)malloc(sizeof(stack));
    init_stack(s);
    push(s,v);
    while (!is_empty(s)) {
        v = pop(s);
        if (visted_stack[v] == 0) {
            visted_stack[v] = 1;
            printf("%d -> ", v);

            for(tmp = g->adj_list[v]; tmp; tmp = tmp->link) {
                if (visited[tmp->vertext] == FALSE) 
                    push(s, tmp->vertext);
            }
        }
    }
}

int visited_bfs[MAX_VERTICES];
void bfs_list(Graph* g, int v)
{
    GraphNode* p;
    QueueType q;

    init_queue(&q);
    visited_bfs[v] = TRUE;
    printf("%d -> ", v);
    enqueue(&q, v);
    while (!is_empty_q(&q)) {
        v = dequeue(&q);
        for (p = g->adj_list[v]; p; p =p->link)
        {
            if (!visited_bfs[p->vertext]) {
                printf("%d -> ", p->vertext);
                visited_bfs[p->vertext]= TRUE;
                enqueue(&q, p->vertext);
            }
        }
    }
}

int main()
{
    Graph* g;
    g = (Graph*)malloc(sizeof(Graph));
    init(g);
    for (int i=0; i < 4; i++)
        insert_vertex(g, i);
    insert_edge(g, 0, 1);
    insert_edge(g, 1, 0);
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 0);
    insert_edge(g, 0, 3);
    insert_edge(g, 3, 0);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 2);
    print_adj_list(g);
    bfs_list(g, 0);

    free(g);
    return 0;
}