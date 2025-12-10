#include <stdio.h>
#include <stdlib.h>

#define LENGHT 10

typedef struct{
    int *elemPtr;
    int count;
    int max;

}List;

void initialize(List *L) {
    L->max = LENGHT;
    L->elemPtr = malloc(L->max * sizeof(int));
    L->count = 0;
    
}

void insertPos(List *L, int data, int position) {
    int i;
    L->count++;
    for(i=L->count; i > position; i--){
        L->elemPtr[i] = L->elemPtr[i-1];
    }
    L->elemPtr[i] = data;
    
}

void deletePos(List *L, int position) {
    int i;
    L->count--;
    for(i=position; i<L->count; i++) {
        L->elemPtr[i] = L->elemPtr[i+1];
    }
    
}

int locate(List *L, int data) {
    int i;
    for(i=0; i<L->count; i++) {
        if(L->elemPtr[i] == data) {
            return i;
        }
    }
    return -1;
}

int retrieve(List *L, int position) {
    return L->elemPtr[position];
}

void insertSorted(List *L, int data) {
    int i, x;
    L->count ++;
    for(i = 0; L->elemPtr[i] < data && i < L->count; i++);
    for(x = L->count-1; x>i && x > i; x--) {
        L->elemPtr[x] = L->elemPtr[x-1];
    }
    L->elemPtr[x] = data;
    
}

void display(List *L) {
    int i;
    
    printf("Data: ");
    
    for(i=0; i < L->count; i++) {
        printf("%d ", L->elemPtr[i]);
    }
    printf("\nCount: %d\n", L->count);
    
}

void resize(List *L) {
    int *arr;
    arr = realloc(L->elemPtr, L->max);
    L->elemPtr = arr;
}

void makeNULL(List *L) {
    free(L);
}


int main() {
    List Li;
    List *L = &Li;
    
    initialize(L);
    
    L->elemPtr[0] = 1;
    L->elemPtr[1] = 3;
    L->elemPtr[2] = 4;
    L->elemPtr[3] = 9;
    L->count = 4;

    display(L);
    
    insertPos(L, 7, 3);
    
    display(L);
    
    deletePos(L, 3);
    
    display(L);
    
    printf("%d\n", locate(L, 4));
    
    printf("%d\n", retrieve(L, 2));
    
    insertSorted(L, 0);
    
    display(L);
    
    resize(L);

    makeNULL(L);
   
    return 0;
}
