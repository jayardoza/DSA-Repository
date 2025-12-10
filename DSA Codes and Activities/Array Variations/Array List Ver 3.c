#include <stdio.h>
#include <stdlib.h>

#define LENGHT 10

typedef struct{
    int *elemPtr;
    int count;
    int max;

}List;

List initialize(List L) {
    L.max = LENGHT;
    L.elemPtr = malloc(L.max * sizeof(int));
    L.count = 0;
    
    return L;
}

List insertPos(List L, int data, int position) {
    int i;
    L.count++;
    for(i=L.count; i > position; i--){
        L.elemPtr[i] = L.elemPtr[i-1];
    }
    L.elemPtr[i] = data;
    
    return L;
}

List deletePos(List L, int position) {
    int i;
    L.count--;
    for(i=position; i<L.count; i++) {
        L.elemPtr[i] = L.elemPtr[i+1];
    }
    
    return L;
}

int locate(List L, int data) {
    int i;
    for(i=0; i<L.count; i++) {
        if(L.elemPtr[i] == data) {
            return i;
        }
    }
    return -1;
}

List insertSorted(List L, int data) {
    int i, x;
    L.count ++;
    for(i = 0; L.elemPtr[i] < data && i < L.count; i++);
    for(x = L.count-1; x>i && x > i; x--) {
        L.elemPtr[x] = L.elemPtr[x-1];
    }
    L.elemPtr[x] = data;
    
    return L;
}

void display(List L) {
    int i;
    
    printf("Data: ");
    
    for(i=0; i < L.count; i++) {
        printf("%d ", L.elemPtr[i]);
    }
    printf("\nCount: %d\n", L.count);
    
}

List resize(List L) {
    int *arr;
    arr = realloc(L.elemPtr, L.max);
    L.elemPtr = arr;
    return L;
}

int main() {
    List L;
    int i;
    
    L = initialize(L);
    
    L.elemPtr[0] = 1;
    L.elemPtr[1] = 3;
    L.elemPtr[2] = 4;
    L.elemPtr[3] = 9;
    L.count = 4;

    display(L);
    
    L = insertPos(L, 2, 1);
    
    display(L);
    
    L = deletePos(L, 2);
    
    display(L);
    
    printf("%d\n", locate(L, 1));
    
    L = insertSorted(L, 10);
    
    display(L);
    
    L = resize(L);
    
    printf("%d\n", L.max);

   
    return 0;
}
