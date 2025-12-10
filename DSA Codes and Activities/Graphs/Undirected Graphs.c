#include <stdio.h>
#include <stdlib.h>
#define M 5
#define INFINITY 999
typedef int GRAPH[5][5];

void initGraph(GRAPH D);
void createArc(GRAPH D, int x, int y);
int findIncident(GRAPH D, int x, int y);
void displayGraph(GRAPH G);
void findPairs(GRAPH G);
void main() {
    GRAPH G;
    initGraph(G);
    createArc(G, 0,1);
    createArc(G, 0,2);
    createArc(G, 1,2);
    createArc(G, 1,3);
    createArc(G, 1,0);
    createArc(G, 2,1);
    createArc(G, 2,4);
    createArc(G, 2,0);
    createArc(G, 3,1);
    createArc(G, 3,4);
    createArc(G, 4,7);
    createArc(G, 4,3);
    displayGraph(G);
    int head, tail;
    printf("Choose a head to be found 0-4: \n");
    scanf("%d", &head);
    printf("Choose a tail to be found 0-4: \n");
    scanf("%d", &tail);
    int arc = findIncident(G,head,tail);
    if(arc == 1) {
        printf("There is an incident between %d %d",head,tail);
    }else {
        printf("There is no incident between %d %d",head,tail);
    }

}

void initGraph(GRAPH D) {
    int x, y;
    for(x = 0; x < M;x++) {
        for(y = 0; y < M; y++) {
            D[x][y] = INFINITY;
        }
    }
}

void displayGraph(GRAPH G) {
    int x, y;
    for(x = 0; x < M; x++) {
        for(y = 0; y < M; y++) {
            if(G[x][y] == INFINITY) {
                printf("\u221E ");
            }else {
                printf("%d ", G[x][y]);
            }
        }
        printf("\n");
    }
}

void createArc(GRAPH D, int x, int y) {
    if(x < M && y < M) {
        D[x][y] = 1;
    }else {
        printf("%d %d too large to be inserted as arcs here\n\n",x,y);
    }
}

int findIncident(GRAPH D, int x, int y) {
    return (D[x][y] == 1)? 1 : 0; 
}

//kapoy realloc

int *Dijkstra(GRAPH G, int startV){
    int S[M], i, j, x, sum = 0, w, Scount = 0, min = INFINITY;
    int V[M] = {0, 1, 2 ,3 ,4};
    //int *D = (int*)malloc(sizeof(int)*SIZE);
    int *D = (int*)calloc(1,sizeof(int)*M);

    if(D != NULL){
        S[Scount++] = startV;
        
        for(i = 1; i < M; i++){
            D[i] = G[startV][i]; //Initializes D
        }
       
        for(i = 1; i < M; i++){
             //A. Choose a vertex w in V-S such taht D[w] is a minimum (except source vertex)
            for(x = 0; x < M; x++){
                for(j = 0; j < Scount && V[x] != S[j]; j++){}
                if(j == Scount && D[V[x]] < min){
                    min = D[V[x]];
                    w = V[x];
                }
            }
            //B. Add w to S
            S[Scount++] = w;
            //C. for each vertex w in V-S
            for(x = 0; x < M; x++){
                for(j = 0; j < Scount && V[x] != S[j]; j++){}
                if(j == Scount){
                    sum = D[w] + G[w][V[x]];
                    D[V[x]] =( D[V[x]] < sum ) ? D[V[x]] : sum;
                }
            }
            min = INFINITY; //resets
        }
    }
    return D;
}