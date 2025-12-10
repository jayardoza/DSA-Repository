#include <stdio.h>
#include <stdbool.h>

#define MAX 10

// ==================== VARIATION 2 ====================
// next field contains the position (0-based) of the next element in the list

typedef struct {
    int elem;
    int next;
} Cell2;

typedef struct {
    Cell2 HeapSpace[MAX];
    int avail;
} VHeap2;

typedef int List2;

// Helper function to get index from position
int getIndexAtPosV2(VHeap2 V, List2 L, int pos) {
    int trav = L;
    for (int i = 0; i < pos && trav != -1; i++) {
        trav = V.HeapSpace[trav].next;
    }
    return trav;
}

void initializeV2(VHeap2 *V) {
    for (int i = 0; i < MAX - 1; i++) {
        V->HeapSpace[i].next = i + 1;
    }
    V->HeapSpace[MAX - 1].next = -1;
    V->avail = 0;
}

int allocSpaceV2(VHeap2* V) {
    if (V->avail == -1) {
        printf("No available space in heap!\n");
        return -1;
    }
    int index = V->avail;
    V->avail = V->HeapSpace[V->avail].next;
    return index;
}

void deallocSpaceV2(VHeap2* V, int index) {
    V->HeapSpace[index].next = V->avail;
    V->avail = index;
}

void insertFirstV2(List2* L, VHeap2* V, int elem) {
    int newIdx = allocSpaceV2(V);
    if (newIdx == -1) return;
    
    V->HeapSpace[newIdx].elem = elem;
    V->HeapSpace[newIdx].next = *L;
    *L = newIdx;
    printf("Inserted %d at first position (V2)\n", elem);
}

void insertLastV2(List2* L, VHeap2* V, int elem) {
    int newIdx = allocSpaceV2(V);
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
    printf("Inserted %d at last position (V2)\n", elem);
}

void insertPosV2(List2* L, VHeap2* V, int elem, int pos) {
    int newIdx = allocSpaceV2(V);
    if (newIdx == -1) return;
    
    V->HeapSpace[newIdx].elem = elem;
    
    if (pos == 0) {
        V->HeapSpace[newIdx].next = *L;
        *L = newIdx;
    } else {
        int trav = *L;
        for (int i = 0; i < pos - 1 && trav != -1; i++) {
            trav = V->HeapSpace[trav].next;
        }
        if (trav != -1) {
            V->HeapSpace[newIdx].next = V->HeapSpace[trav].next;
            V->HeapSpace[trav].next = newIdx;
        }
    }
    printf("Inserted %d at position %d (V2)\n", elem, pos);
}

void insertSortedV2(List2* L, VHeap2* V, int elem) {
    int newIdx = allocSpaceV2(V);
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
    printf("Inserted %d in sorted order (V2)\n", elem);
}

void deleteV2(List2* L, VHeap2* V, int elem) {
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
        deallocSpaceV2(V, temp);
        printf("Deleted %d (V2)\n", elem);
    } else {
        printf("Element %d not found (V2)\n", elem);
    }
}

void deleteAllOccurrenceV2(List2* L, VHeap2* V, int elem) {
    int *trav = L;
    int count = 0;
    
    while (*trav != -1) {
        if (V->HeapSpace[*trav].elem == elem) {
            int temp = *trav;
            *trav = V->HeapSpace[*trav].next;
            deallocSpaceV2(V, temp);
            count++;
        } else {
            trav = &(V->HeapSpace[*trav].next);
        }
    }
    printf("Deleted %d occurrences of %d (V2)\n", count, elem);
}

void displayV2(List2 L, VHeap2 V) {
    if (L == -1) {
        printf("List is empty!\n");
        return;
    }
    printf("List (V2): ");
    int trav = L;
    while (trav != -1) {
        printf("%d ", V.HeapSpace[trav].elem);
        trav = V.HeapSpace[trav].next;
    }
    printf("\n");
}

void displayHeapV2(VHeap2 V) {
    printf("\nHeap Space (V2):\n");
    printf("Index | Elem | Next\n");
    printf("------|------|-----\n");
    for (int i = 0; i < MAX; i++) {
        printf("  %d   |  %2d  |  %2d\n", i, V.HeapSpace[i].elem, V.HeapSpace[i].next);
    }
    printf("Avail: %d\n\n", V.avail);
}


int main() {
   	printf("\n========== CURSOR-BASED LIST VARIATION 2 ==========\n");
    printf("(next field stores INDEX of next element - same as V1)\n\n");
    
    VHeap2 V2;
    List2 L2 = -1;
    initializeV2(&V2);
    
    insertFirstV2(&L2, &V2, 10);
    insertFirstV2(&L2, &V2, 5);
    insertLastV2(&L2, &V2, 20);
    displayV2(L2, V2);
    displayHeapV2(V2);
    
    insertSortedV2(&L2, &V2, 15);
    insertSortedV2(&L2, &V2, 3);
    displayV2(L2, V2);
    
    deleteV2(&L2, &V2, 10);
    displayV2(L2, V2);
    
    insertFirstV2(&L2, &V2, 5);
    insertLastV2(&L2, &V2, 5);
    displayV2(L2, V2);
    
    deleteAllOccurrenceV2(&L2, &V2, 5);
    displayV2(L2, V2);
    displayHeapV2(V2);
}
