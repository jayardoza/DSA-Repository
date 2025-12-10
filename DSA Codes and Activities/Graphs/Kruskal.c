#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, w;
} Edge;

typedef struct {
    int parent, rank;
} Subset;

int compare(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void unionSet(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int main() {
    Edge edges[] = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5},
        {1, 3, 15}, {2, 3, 4}
    };
    int V = 4, E = 5;

    qsort(edges, E, sizeof(Edge), compare);

    Subset* subsets = malloc(V * sizeof(Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    printf("Edges in MST:\n");
    for (int i = 0, e = 0; e < V - 1 && i < E; i++) {
        Edge next = edges[i];
        int x = find(subsets, next.u);
        int y = find(subsets, next.v);

        if (x != y) {
            printf("%d -- %d == %d\n", next.u, next.v, next.w);
            unionSet(subsets, x, y);
            e++;
        }
    }

    free(subsets);
    return 0;
}

