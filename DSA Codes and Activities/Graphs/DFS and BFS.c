#include <stdio.h>
#include <stdlib.h>
#define MAX 9
#define VISITED -1
#define UNVISITED 100

typedef struct node {
    int data;
    struct node *link;
} *ptr, Node;

typedef ptr Graph[MAX];

typedef struct {
    int data[MAX];
    int front, rear;
} Queue;

// DFS function
void dfs(Graph G, int V, int Mark[]) {
    Mark[V] = VISITED;
    printf("%d ", V);

    ptr trav;
    for(trav = G[V]; trav != NULL; trav = trav->link) {
        if(Mark[trav->data] == UNVISITED) {
            dfs(G, trav->data, Mark);
        }
    }
}

// BFS function
void bfs(Graph G, int V) {
    Queue Q;
    ptr trav;
    int mark[MAX], w;

    for(int i = 0; i < MAX; i++) mark[i] = UNVISITED;

    Q.front = 0;
    Q.rear = 0;
    Q.data[Q.rear] = V;
    mark[V] = VISITED;

    while(Q.front != Q.rear + 1 && Q.front < MAX) {
        w = Q.data[Q.front];
        printf("%d ", w);
        Q.front++;

        for(trav = G[w]; trav != NULL; trav = trav->link) {
            if(mark[trav->data] == UNVISITED) {
                Q.rear++;
                Q.data[Q.rear] = trav->data;
                mark[trav->data] = VISITED;
            }
        }
    }
}

// Helper to add edge
void addEdge(Graph G, int u, int v) {
    ptr newNode = (ptr)malloc(sizeof(Node));
    newNode->data = v;
    newNode->link = G[u];
    G[u] = newNode;
}

int main() {
    Graph G = {NULL};
    int Mark[MAX];

    for(int i = 0; i < MAX; i++)
        Mark[i] = UNVISITED;

    // Example graph
    addEdge(G, 0, 1);
    addEdge(G, 0, 2);
    addEdge(G, 1, 3);
    addEdge(G, 1, 4);
    addEdge(G, 2, 5);
    addEdge(G, 2, 6);

    printf("DFS starting from vertex 0: ");
    dfs(G, 0, Mark);

    printf("\nBFS starting from vertex 0: ");
    bfs(G, 0);

    return 0;
}

