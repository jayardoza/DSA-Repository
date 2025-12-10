#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct{
    int elem[MAX];
    int count;

}Etype, *EPtr;

void initialize(EPtr L) {
    L->count = 0;
}

void insertPos(EPtr L, int data, int position){
    int i;
    for(i = L->count; i > position; i--){
        L->elem[i] = L->elem[i-1];
    }
    
    L->elem[i] = data;
    L->count++;


}

void deletePos(EPtr L, int position){
    int i;
    
    for(i=position; i < L->count; i++) {
        L->elem[i] = L->elem[i+1];
    }
    L->elem[i] = 0;
    L->count -= 1;
    
}

int locate(EPtr L, int data){
    int i;
    for(i=0; i<L->count; i++){
        if(L->elem[i] == data) {
            return i;
        }
    }
}

int retrieve(EPtr L, int position) {
    return L->elem[position];
}

void insertSorted(EPtr L, int data){
    int i, x;
    L->count++;
    for(i=0; data > L->elem[i]; i++);
    for(x = L->count-1; x > i; x--){
            L->elem[x] = L->elem[x-1];
    }
    L->elem[x] = data;
    
}

void display(EPtr L){
    int i = 0;
    printf("data: ");
    for(i=0; i<L->count; i++){
        printf("%d", L->elem[i]);
    }
    printf("\ncount: %d\n", L->count);
}

void makeNULL(EPtr L) {
    free(L);
}


int main() {
    Etype Li;
    EPtr L = &Li;
    
    initialize(L);
    
    L->elem[0] = 1;
    L->elem[1] = 3;
    L->elem[2] = 7;
    L->elem[3] = 9;
    L->count = 4;
    
    display(L);
    
    insertPos(L, 4, 2);
    
    display(L);
    
    deletePos(L, 1);
    
    display(L);
    
    printf("\n%d\n" ,locate(L, 4));
    
    printf("%d\n", retrieve(L, 2));
    
    insertSorted(L, 5);
    
    display(L);
    
    makeNULL(L);
    
    display (L);

    return 0;
}
