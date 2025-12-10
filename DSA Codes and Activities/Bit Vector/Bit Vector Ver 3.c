#include <stdio.h>
#include <stdbool.h>

#define MAX_BITS 8
#define ARRAY_SIZE 8

// ==================== VARIATION 3: Boolean/Enum Array ====================

typedef bool SetArray[ARRAY_SIZE];

void initializeV3(SetArray set) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        set[i] = false;
    }
}

void insertV3(SetArray set, int element) {
    if (element < 0 || element >= ARRAY_SIZE) {
        printf("Error: Element %d out of range [0-%d]\n", element, ARRAY_SIZE-1);
        return;
    }
    set[element] = true;
}

void deleteV3(SetArray set, int element) {
    if (element < 0 || element >= ARRAY_SIZE) {
        printf("Error: Element %d out of range [0-%d]\n", element, ARRAY_SIZE-1);
        return;
    }
    set[element] = false;
}

bool findV3(SetArray set, int element) {
    if (element < 0 || element >= ARRAY_SIZE) {
        return false;
    }
    return set[element];
}

void unionV3(SetArray A, SetArray B, SetArray C) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        C[i] = A[i] || B[i];
    }
}

void intersectionV3(SetArray A, SetArray B, SetArray C) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        C[i] = A[i] && B[i];
    }
}

void differenceV3(SetArray A, SetArray B, SetArray C) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        C[i] = A[i] && !B[i];
    }
}

void displayV3(SetArray set) {
    printf("{");
    bool first = true;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (set[i]) {
            if (!first) printf(", ");
            printf("%d", i);
            first = false;
        }
    }
    printf("}");
}

void displayArrayV3(SetArray set) {
    printf("[");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d", set[i] ? 1 : 0);
        if (i < ARRAY_SIZE - 1) printf(",");
    }
    printf("]");
}

int main() {
 	printf("========== VARIATION 3: Boolean/Enum Array ==========\n\n");
    
    SetArray arrA;
    initializeV3(arrA);
    
    printf("Initial: ");
    displayV3(arrA);
    printf(" = ");
    displayArrayV3(arrA);
    printf("\n\n");
    
    insertV3(arrA, 0);
    printf("After insert(0): ");
    displayV3(arrA);
    printf(" = ");
    displayArrayV3(arrA);
    printf("\n");
    
    insertV3(arrA, 2);
    printf("After insert(2): ");
    displayV3(arrA);
    printf(" = ");
    displayArrayV3(arrA);
    printf("\n");
    
    insertV3(arrA, 7);
    printf("After insert(7): ");
    displayV3(arrA);
    printf(" = ");
    displayArrayV3(arrA);
    printf("\n\n");
    
    SetArray arrB;
    initializeV3(arrB);
    insertV3(arrB, 2);
    insertV3(arrB, 4);
    insertV3(arrB, 5);
    printf("Set B: ");
    displayV3(arrB);
    printf(" = ");
    displayArrayV3(arrB);
    printf("\n\n");
    
    SetArray arrC;
    unionV3(arrA, arrB, arrC);
    printf("Union(A, B): ");
    displayV3(arrC);
    printf(" = ");
    displayArrayV3(arrC);
    printf("\n");
    
    intersectionV3(arrA, arrB, arrC);
    printf("Intersection(A, B): ");
    displayV3(arrC);
    printf(" = ");
    displayArrayV3(arrC);
    printf("\n");
    
    differenceV3(arrA, arrB, arrC);
    printf("Difference(A, B): ");
    displayV3(arrC);
    printf(" = ");
    displayArrayV3(arrC);
    printf("\n");
    
    deleteV3(arrA, 0);
    printf("\nAfter delete(0): ");
    displayV3(arrA);
    printf(" = ");
    displayArrayV3(arrA);
    printf("\n");
    
    deleteV3(arrA, 7);
    printf("After delete(7): ");
    displayV3(arrA);
    printf(" = ");
    displayArrayV3(arrA);
    printf("\n");
    
}
