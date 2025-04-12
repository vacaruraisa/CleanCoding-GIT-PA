// parcurgerge graf cu DFS/BFS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct Graph
{
    int vertices;
    int *visited;
    NODE **adjacency_lists;
} GPH;

/// creeaza un nod
NODE *create_node(int v)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

/// creeaza graful
GPH *create_graph(int vertices)
{
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = calloc(vertices, sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
    }
    return graph;
}

/// adauga muchie
void add_edge(GPH *graph, int src, int dest)
{
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

/// functie care citeste muchiile
void insedg(int nr_of_vertices, int nr_of_edges, GPH *graph)
{
    int src, dest;
    printf("adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);
    for (int i = 0; i < nr_of_edges; i++)
    {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

/// verificam daca coada e goala
int is_empty(NODE *queue)
{
    return queue == NULL;
}

/// adauga in coada (folosim lista simpla)
void enqueue(NODE **queue, int data)
{
    NODE *new_node = create_node(data);
    if (*queue == NULL)
    {
        *queue = new_node;
    }
    else
    {
        NODE *temp = *queue;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

/// scoate din coada
int dequeue(NODE **queue)
{
    if (*queue == NULL)
        return -1;
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

/// DFS (depth-first search)
void DFS(GPH *graph, int vertex_nr)
{
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d->", vertex_nr);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

/// BFS (breadth-first search)
void BFS(GPH *graph, int start)
{
    NODE *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacency_lists[current];
        while (temp)
        {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

/// resetam vectorul de vizite
void wipe_visited_list(GPH *graph, int nr_of_vertices)
{
    for (int i = 0; i < nr_of_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

int main()
{
    int nr_of_vertices;
    int nr_of_edges;
    int starting_vertex;
    int starting_blin; // =)))
    int *adj_matrix;

    printf("cate noduri are graful?");
    scanf("%d", &nr_of_vertices);

    printf("cate muchii are graful?");
    scanf("%d", &nr_of_edges);

    GPH *graph = create_graph(nr_of_vertices);

    insedg(nr_of_vertices, nr_of_edges, graph);

    printf("de unde plecam in DFS?");
    scanf("%d", &starting_blin);
    printf("parcurgere cu DFS: ");
    DFS(graph, starting_blin);

    wipe_visited_list(graph, nr_of_vertices);
    printf("\n");

    printf("de unde plecam in BFS?");
    scanf("%d", &starting_vertex);
    printf("parcurgere cu BFS: ");
    BFS(graph, starting_vertex);

    return 0;
}
