#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 10

// ==================== ADJACENCY MATRIX ====================

typedef struct {
    int vertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} GraphMatrix;

// Initialize adjacency matrix
void initMatrix(GraphMatrix* g, int vertices) {
    g->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }
}

// Add edge (undirected graph)
void addEdgeMatrix(GraphMatrix* g, int src, int dest) {
    if (src >= 0 && src < g->vertices && dest >= 0 && dest < g->vertices) {
        g->adjMatrix[src][dest] = 1;
        g->adjMatrix[dest][src] = 1;  // For undirected graph
    }
}

// Add directed edge
void addDirectedEdgeMatrix(GraphMatrix* g, int src, int dest) {
    if (src >= 0 && src < g->vertices && dest >= 0 && dest < g->vertices) {
        g->adjMatrix[src][dest] = 1;
    }
}

// Add weighted edge (undirected)
void addWeightedEdgeMatrix(GraphMatrix* g, int src, int dest, int weight) {
    if (src >= 0 && src < g->vertices && dest >= 0 && dest < g->vertices) {
        g->adjMatrix[src][dest] = weight;
        g->adjMatrix[dest][src] = weight;  // For undirected graph
    }
}

// Remove edge
void removeEdgeMatrix(GraphMatrix* g, int src, int dest) {
    if (src >= 0 && src < g->vertices && dest >= 0 && dest < g->vertices) {
        g->adjMatrix[src][dest] = 0;
        g->adjMatrix[dest][src] = 0;
    }
}

// Check if edge exists
bool hasEdgeMatrix(GraphMatrix* g, int src, int dest) {
    if (src >= 0 && src < g->vertices && dest >= 0 && dest < g->vertices) {
        return g->adjMatrix[src][dest] != 0;
    }
    return false;
}

// Display adjacency matrix
void displayMatrix(GraphMatrix* g) {
    printf("\nAdjacency Matrix:\n");
    printf("   ");
    for (int i = 0; i < g->vertices; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    
    for (int i = 0; i < g->vertices; i++) {
        printf("%2d ", i);
        for (int j = 0; j < g->vertices; j++) {
            printf("%2d ", g->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Get degree of a vertex
int getDegreeMatrix(GraphMatrix* g, int vertex) {
    int degree = 0;
    if (vertex >= 0 && vertex < g->vertices) {
        for (int i = 0; i < g->vertices; i++) {
            if (g->adjMatrix[vertex][i] != 0) {
                degree++;
            }
        }
    }
    return degree;
}

// Display neighbors of a vertex
void displayNeighborsMatrix(GraphMatrix* g, int vertex) {
    if (vertex >= 0 && vertex < g->vertices) {
        printf("Neighbors of vertex %d: ", vertex);
        bool first = true;
        for (int i = 0; i < g->vertices; i++) {
            if (g->adjMatrix[vertex][i] != 0) {
                if (!first) printf(", ");
                printf("%d", i);
                first = false;
            }
        }
        if (first) printf("None");
        printf("\n");
    }
}

// ==================== ADJACENCY LIST ====================

typedef struct Node {
    int vertex;
    int weight;  // For weighted graphs
    struct Node* next;
} Node;

typedef struct {
    int vertices;
    Node** adjList;
} GraphList;

// Create a new node
Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Initialize adjacency list
GraphList* initList(int vertices) {
    GraphList* g = (GraphList*)malloc(sizeof(GraphList));
    g->vertices = vertices;
    g->adjList = (Node**)malloc(vertices * sizeof(Node*));
    
    for (int i = 0; i < vertices; i++) {
        g->adjList[i] = NULL;
    }
    
    return g;
}

// Add edge (undirected graph)
void addEdgeList(GraphList* g, int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest, 1);
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;
    
    // Add edge from dest to src (undirected)
    newNode = createNode(src, 1);
    newNode->next = g->adjList[dest];
    g->adjList[dest] = newNode;
}

// Add directed edge
void addDirectedEdgeList(GraphList* g, int src, int dest) {
    Node* newNode = createNode(dest, 1);
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;
}

// Add weighted edge (undirected)
void addWeightedEdgeList(GraphList* g, int src, int dest, int weight) {
    // Add edge from src to dest
    Node* newNode = createNode(dest, weight);
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;
    
    // Add edge from dest to src (undirected)
    newNode = createNode(src, weight);
    newNode->next = g->adjList[dest];
    g->adjList[dest] = newNode;
}

// Remove edge
void removeEdgeList(GraphList* g, int src, int dest) {
    // Remove dest from src's list
    Node* temp = g->adjList[src];
    Node* prev = NULL;
    
    while (temp != NULL && temp->vertex != dest) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp != NULL) {
        if (prev == NULL) {
            g->adjList[src] = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
    }
    
    // Remove src from dest's list (undirected)
    temp = g->adjList[dest];
    prev = NULL;
    
    while (temp != NULL && temp->vertex != src) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp != NULL) {
        if (prev == NULL) {
            g->adjList[dest] = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
    }
}

// Check if edge exists
bool hasEdgeList(GraphList* g, int src, int dest) {
    Node* temp = g->adjList[src];
    while (temp != NULL) {
        if (temp->vertex == dest) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Display adjacency list
void displayList(GraphList* g) {
    printf("\nAdjacency List:\n");
    for (int i = 0; i < g->vertices; i++) {
        printf("Vertex %d: ", i);
        Node* temp = g->adjList[i];
        if (temp == NULL) {
            printf("NULL");
        }
        while (temp != NULL) {
            printf("-> %d", temp->vertex);
            if (temp->weight != 1) {
                printf("(w:%d)", temp->weight);
            }
            temp = temp->next;
        }
        printf("\n");
    }
}

// Get degree of a vertex
int getDegreeList(GraphList* g, int vertex) {
    int degree = 0;
    Node* temp = g->adjList[vertex];
    while (temp != NULL) {
        degree++;
        temp = temp->next;
    }
    return degree;
}

// Display neighbors of a vertex
void displayNeighborsList(GraphList* g, int vertex) {
    printf("Neighbors of vertex %d: ", vertex);
    Node* temp = g->adjList[vertex];
    if (temp == NULL) {
        printf("None");
    }
    bool first = true;
    while (temp != NULL) {
        if (!first) printf(", ");
        printf("%d", temp->vertex);
        first = false;
        temp = temp->next;
    }
    printf("\n");
}

// Free adjacency list memory
void freeList(GraphList* g) {
    for (int i = 0; i < g->vertices; i++) {
        Node* temp = g->adjList[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(g->adjList);
    free(g);
}

// ==================== MAIN FUNCTION ====================

int main() {
    printf("========== ADJACENCY MATRIX DEMONSTRATION ==========\n");
    
    GraphMatrix gm;
    initMatrix(&gm, 5);
    
    // Add edges to create a sample graph
    printf("\nAdding edges: (0-1), (0-4), (1-2), (1-3), (1-4), (2-3), (3-4)\n");
    addEdgeMatrix(&gm, 0, 1);
    addEdgeMatrix(&gm, 0, 4);
    addEdgeMatrix(&gm, 1, 2);
    addEdgeMatrix(&gm, 1, 3);
    addEdgeMatrix(&gm, 1, 4);
    addEdgeMatrix(&gm, 2, 3);
    addEdgeMatrix(&gm, 3, 4);
    
    displayMatrix(&gm);
    
    printf("\nVertex degrees:\n");
    for (int i = 0; i < gm.vertices; i++) {
        printf("Vertex %d: degree = %d\n", i, getDegreeMatrix(&gm, i));
    }
    
    printf("\n");
    displayNeighborsMatrix(&gm, 1);
    displayNeighborsMatrix(&gm, 4);
    
    printf("\nChecking if edge exists between 1 and 3: %s\n", 
           hasEdgeMatrix(&gm, 1, 3) ? "Yes" : "No");
    printf("Checking if edge exists between 0 and 3: %s\n", 
           hasEdgeMatrix(&gm, 0, 3) ? "Yes" : "No");
    
    printf("\nRemoving edge (1-3)...\n");
    removeEdgeMatrix(&gm, 1, 3);
    displayMatrix(&gm);
    
    printf("\n\n========== ADJACENCY LIST DEMONSTRATION ==========\n");
    
    GraphList* gl = initList(5);
    
    printf("\nAdding edges: (0-1), (0-4), (1-2), (1-3), (1-4), (2-3), (3-4)\n");
    addEdgeList(gl, 0, 1);
    addEdgeList(gl, 0, 4);
    addEdgeList(gl, 1, 2);
    addEdgeList(gl, 1, 3);
    addEdgeList(gl, 1, 4);
    addEdgeList(gl, 2, 3);
    addEdgeList(gl, 3, 4);
    
    displayList(gl);
    
    printf("\nVertex degrees:\n");
    for (int i = 0; i < gl->vertices; i++) {
        printf("Vertex %d: degree = %d\n", i, getDegreeList(gl, i));
    }
    
    printf("\n");
    displayNeighborsList(gl, 1);
    displayNeighborsList(gl, 4);
    
    printf("\nChecking if edge exists between 1 and 3: %s\n", 
           hasEdgeList(gl, 1, 3) ? "Yes" : "No");
    printf("Checking if edge exists between 0 and 3: %s\n", 
           hasEdgeList(gl, 0, 3) ? "Yes" : "No");
    
    printf("\nRemoving edge (1-3)...\n");
    removeEdgeList(gl, 1, 3);
    displayList(gl);
    
    printf("\n\n========== WEIGHTED GRAPH DEMONSTRATION ==========\n");
    
    GraphList* wgl = initList(4);
    printf("\nAdding weighted edges:\n");
    addWeightedEdgeList(wgl, 0, 1, 5);
    addWeightedEdgeList(wgl, 0, 2, 3);
    addWeightedEdgeList(wgl, 1, 2, 2);
    addWeightedEdgeList(wgl, 1, 3, 7);
    addWeightedEdgeList(wgl, 2, 3, 4);
    
    displayList(wgl);
    
    printf("\n\n========== DIRECTED GRAPH DEMONSTRATION ==========\n");
    
    GraphMatrix dgm;
    initMatrix(&dgm, 4);
    printf("\nAdding directed edges: 0->1, 0->2, 1->2, 2->0, 2->3, 3->3\n");
    addDirectedEdgeMatrix(&dgm, 0, 1);
    addDirectedEdgeMatrix(&dgm, 0, 2);
    addDirectedEdgeMatrix(&dgm, 1, 2);
    addDirectedEdgeMatrix(&dgm, 2, 0);
    addDirectedEdgeMatrix(&dgm, 2, 3);
    addDirectedEdgeMatrix(&dgm, 3, 3);  // Self-loop
    
    displayMatrix(&dgm);
    
    // Free memory
    freeList(gl);
    freeList(wgl);
    
    return 0;
}
