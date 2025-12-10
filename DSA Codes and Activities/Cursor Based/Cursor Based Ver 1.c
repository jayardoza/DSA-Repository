#include <stdio.h>
#include <stdbool.h>

#define MAX 10

// ==================== VARIATION 1 ====================
// next field contains the index of the next element in the list

typedef struct {
    int elem;
    int next;
} Cell;

typedef struct {
    Cell HeapSpace[MAX];
    int avail;
} VHeap;

typedef int List;

// Variation 1 Operations
void initializeV1(VHeap *V) {
    int i;
    for (i = 0; i < MAX - 1; i++) {
        V->HeapSpace[i].next = i + 1;
    }
    V->HeapSpace[MAX - 1].next = -1;
    V->avail = 0;
}

int allocSpaceV1(VHeap* V) {
    if (V->avail == -1) {
        printf("No available space in heap!\n");
        return -1;
    }
    int index = V->avail;
    V->avail = V->HeapSpace[V->avail].next;
    return index;
}

void deallocSpaceV1(VHeap* V, int index) {
    V->HeapSpace[index].next = V->avail;
    V->avail = index;
}

void insertFirstV1(List* L, VHeap* V, int elem) {
    int newIdx = allocSpaceV1(V);
    if (newIdx == -1) return;
    
    V->HeapSpace[newIdx].elem = elem;
    V->HeapSpace[newIdx].next = *L;
    *L = newIdx;
    printf("Inserted %d at first position (V1)\n", elem);
}

void insertLastV1(List* L, VHeap* V, int elem) {
    int newIdx = allocSpaceV1(V);
    if (newIdx == -1) return;
    
    V->HeapSpace[newIdx].elem = elem;
    V->HeapSpace[newIdx].next = -1;
    
    if (*L == -1) {
        *L = newIdx;
    } else {
        int trav = *L;
        while (V->HeapSpace[trav].next != -1) {
            trav = V->HeapSpace[trav].next;
        }
        V->HeapSpace[trav].next = newIdx;
    }
    printf("Inserted %d at last position (V1)\n", elem);
}

void insertPosV1(List* L, VHeap* V, int elem, int pos) {
    int newIdx = allocSpaceV1(V);
    if (newIdx == -1) return;
    
    V->HeapSpace[newIdx].elem = elem;
    
    if (pos == 0) {
        V->HeapSpace[newIdx].next = *L;
        *L = newIdx;
    } else {
        int trav = *L;
        int i;
        for (i = 0; i < pos - 1 && trav != -1; i++) {
            trav = V->HeapSpace[trav].next;
        }
        if (trav != -1) {
            V->HeapSpace[newIdx].next = V->HeapSpace[trav].next;
            V->HeapSpace[trav].next = newIdx;
        }
    }
    printf("Inserted %d at position %d (V1)\n", elem, pos);
}

void insertSortedV1(List* L, VHeap* V, int elem) {
    int newIdx = allocSpaceV1(V);
    if (newIdx == -1) return;
    
    V->HeapSpace[newIdx].elem = elem;
    
    if (*L == -1 || V->HeapSpace[*L].elem >= elem) {
        V->HeapSpace[newIdx].next = *L;
        *L = newIdx;
    } else {
        int trav = *L;
        while (V->HeapSpace[trav].next != -1 && 
               V->HeapSpace[V->HeapSpace[trav].next].elem < elem) {
            trav = V->HeapSpace[trav].next;
        }
        V->HeapSpace[newIdx].next = V->HeapSpace[trav].next;
        V->HeapSpace[trav].next = newIdx;
    }
    printf("Inserted %d in sorted order (V1)\n", elem);
}

void deleteV1(List* L, VHeap* V, int elem) {
    if (*L == -1) {
        printf("List is empty!\n");
        return;
    }
    
    int *trav = L;
    while (*trav != -1 && V->HeapSpace[*trav].elem != elem) {
        trav = &(V->HeapSpace[*trav].next);
    }
    
    if (*trav != -1) {
        int temp = *trav;
        *trav = V->HeapSpace[*trav].next;
        deallocSpaceV1(V, temp);
        printf("Deleted %d (V1)\n", elem);
    } else {
        printf("Element %d not found (V1)\n", elem);
    }
}

void deleteAllOccurrenceV1(List* L, VHeap* V, int elem) {
    int *trav = L;
    int count = 0;
    
    while (*trav != -1) {
        if (V->HeapSpace[*trav].elem == elem) {
            int temp = *trav;
            *trav = V->HeapSpace[*trav].next;
            deallocSpaceV1(V, temp);
            count++;
        } else {
            trav = &(V->HeapSpace[*trav].next);
        }
    }
    printf("Deleted %d occurrences of %d (V1)\n", count, elem);
}

void displayV1(List L, VHeap V) {
    if (L == -1) {
        printf("List is empty!\n");
        return;
    }
    printf("List (V1): ");
    int trav = L;
    while (trav != -1) {
        printf("%d ", V.HeapSpace[trav].elem);
        trav = V.HeapSpace[trav].next;
    }
    printf("\n");
}

void displayHeapV1(VHeap V) {
    printf("\nHeap Space (V1):\n");
    printf("Index | Elem | Next\n");
    printf("------|------|-----\n");
    for (int i = 0; i < MAX; i++) {
        printf("  %d   |  %2d  |  %2d\n", i, V.HeapSpace[i].elem, V.HeapSpace[i].next);
    }
    printf("Avail: %d\n\n", V.avail);
}


int main() {
    printf("========== CURSOR-BASED LIST VARIATION 1 ==========\n");
    printf("(next field stores INDEX of next element)\n\n");
    
    VHeap V1;
    List L1 = -1;
    initializeV1(&V1);
    
    insertFirstV1(&L1, &V1, 10);
    insertFirstV1(&L1, &V1, 5);
    insertLastV1(&L1, &V1, 20);
    displayV1(L1, V1);
    displayHeapV1(V1);
    
    insertSortedV1(&L1, &V1, 15);
    insertSortedV1(&L1, &V1, 3);
    displayV1(L1, V1);
    
    deleteV1(&L1, &V1, 10);
    displayV1(L1, V1);
    
    insertFirstV1(&L1, &V1, 5);
    insertLastV1(&L1, &V1, 5);
    displayV1(L1, V1);
    
    deleteAllOccurrenceV1(&L1, &V1, 5);
    displayV1(L1, V1);
    displayHeapV1(V1);
}
