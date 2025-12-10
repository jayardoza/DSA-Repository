#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct{
    int elem[MAX];
    int count;

}List;

List initialize(List L) {
    L.count = 0;
    
    return L;
}

List insertPos(List L, int data, int position){
    int i;
    for(i = L.count; i > position; i--){
        L.elem[i] = L.elem[i-1];
    }
    
    L.elem[i] = data;
    L.count++;

    return L;
}

List deletePos(List L, int position){
    int i;
    
    for(i=position; i < L.count; i++) {
        L.elem[i] = L.elem[i+1];
    }
    L.elem[i] = 0;
    L.count -= 1;
    
    return L;
}

int locate(List L, int data){
    int i;
    for(i=0; i<L.count; i++){
        if(L.elem[i] == data) {
            return i;
        }
    }
    
    return -1;
}

List insertSorted(List L, int data){
    int i, x;
    L.count++;
    for(i=0; data > L.elem[i]; i++);
    for(x = L.count-1; x > i; x--){
            L.elem[x] = L.elem[x-1];
    }
    L.elem[x] = data;
    
    return L;
}

void display(List L){
    int i = 0;
    for(i=0; i<L.count; i++){
        printf("%d", L.elem[i]);
    }
    printf("\n");
}


int main() {
    List L;
    int i;
    
    L = initialize(L);
    
    L.elem[0] = 1;
    L.elem[1] = 3;
    L.elem[2] = 7;
    L.elem[3] = 9;
    L.count = 4;
    
    display(L);
    
    L = insertPos(L, 4, 2);
    
    display(L);
    
    L = deletePos(L, 1);
    
    display(L);
    
    printf("\n%d\n" ,locate(L, 4));
    
    L = insertSorted(L, 5);
    
    display(L);

    return 0;
}
