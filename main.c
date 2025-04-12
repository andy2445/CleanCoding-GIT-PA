#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct Graph {
    int vertex_count;
    int* visited;
    Node** adjacency_lists;
} Graph;

// -------------------------------
// Node & Graph Creation
// -------------------------------

Node* create_node(int value) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

Graph* create_graph(int vertex_count) {
    Graph* graph = malloc(sizeof(Graph));
    graph->vertex_count = vertex_count;

    graph->adjacency_lists = malloc(vertex_count * sizeof(Node*));
    graph->visited = calloc(vertex_count, sizeof(int)); // zero-initialized

    for (int i = 0; i < vertex_count; i++) {
        graph->adjacency_lists[i] = NULL;
    }

    return graph;
}

// -------------------------------
// Graph Edge Utilities
// -------------------------------

void add_edge(Graph* graph, int source, int destination) {
    Node* new_node = create_node(destination);
    new_node->next = graph->adjacency_lists[source];
    graph->adjacency_lists[source] = new_node;

    new_node = create_node(source);
    new_node->next = graph->adjacency_lists[destination];
    graph->adjacency_lists[destination] = new_node;
}

void read_edges(Graph* graph, int edge_count) {
    int src, dest;

    printf("Introduce %d muchii (noduri de la 0 la %d):\n", edge_count, graph->vertex_count - 1);
    for (int i = 0; i < edge_count; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

// -------------------------------
// Queue Implementation (BFS)
// -------------------------------

int is_queue_empty(Node* queue) {
    return queue == NULL;
}

void enqueue(Node** queue, int value) {
    Node* node = create_node(value);

    if (is_queue_empty(*queue)) {
        *queue = node;
        return;
    }

    Node* temp = *queue;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = node;
}

int dequeue(Node** queue) {
    if (is_queue_empty(*queue)) {
        return -1;
    }

    int value = (*queue)->value;
    Node* temp = *queue;
    *queue = (*queue)->next;
    free(temp);

    return value;
}

// -------------------------------
// Visited Utilities
// -------------------------------

void reset_visited(Graph* graph) {
    for (int i = 0; i < graph->vertex_count; i++) {
        graph->visited[i] = 0;
    }
}

// -------------------------------
// DFS & BFS Traversals
// -------------------------------

void dfs(Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    Node* neighbor = graph->adjacency_lists[vertex];
    while (neighbor != NULL) {
        int adjacent = neighbor->value;
        if (!graph->visited[adjacent]) {
            dfs(graph, adjacent);
        }
        neighbor = neighbor->next;
    }
}

void bfs(Graph* graph, int start_vertex) {
    Node* queue = NULL;

    graph->visited[start_vertex] = 1;
    enqueue(&queue, start_vertex);

    while (!is_queue_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node* neighbor = graph->adjacency_lists[current];
        while (neighbor != NULL) {
            int adjacent = neighbor->value;
            if (!graph->visited[adjacent]) {
                graph->visited[adjacent] = 1;
                enqueue(&queue, adjacent);
            }
            neighbor = neighbor->next;
        }
    }
}

// -------------------------------
// Entry Point
// -------------------------------

int main() {
    int vertex_count = 0;
    int edge_count = 0;
    int start_vertex = 0;

    printf("Numar de noduri: ");
    scanf("%d", &vertex_count);

    printf("Numar de muchii: ");
    scanf("%d", &edge_count);

    Graph* graph = create_graph(vertex_count);
    read_edges(graph, edge_count);

    printf("Nod pornire pentru DFS: ");
    scanf("%d", &start_vertex);

    printf("Parcurgere DFS: ");
    dfs(graph, start_vertex);
    printf("\n");

    reset_visited(graph);

    printf("Nod pornire pentru BFS: ");
    scanf("%d", &start_vertex);

    printf("Parcurgere BFS: ");
    bfs(graph, start_vertex);
    printf("\n");

    return 0;
}

