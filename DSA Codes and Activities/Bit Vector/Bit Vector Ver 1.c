#include <stdio.h>
#include <stdbool.h>

#define MAX_BITS 8
#define ARRAY_SIZE 8

// ==================== VARIATION 1: Computer Word / Bitmask ====================

void initializeV1(unsigned char *set) {
    *set = 0;
}

void insertV1(unsigned char *set, int element) {
    if (element < 0 || element >= MAX_BITS) {
        printf("Error: Element %d out of range [0-%d]\n", element, MAX_BITS-1);
        return;
    }
    unsigned char mask = 1 << element;
    *set |= mask;
}

void deleteV1(unsigned char *set, int element) {
    if (element < 0 || element >= MAX_BITS) {
        printf("Error: Element %d out of range [0-%d]\n", element, MAX_BITS-1);
        return;
    }
    unsigned char mask = 1 << element;
    mask = ~mask;
    *set &= mask;
}

bool findV1(unsigned char set, int element) {
    if (element < 0 || element >= MAX_BITS) {
        return false;
    }
    unsigned char mask = 1 << element;
    return (set & mask) != 0;
}

unsigned char unionV1(unsigned char A, unsigned char B) {
    return A | B;
}

unsigned char intersectionV1(unsigned char A, unsigned char B) {
    return A & B;
}

unsigned char differenceV1(unsigned char A, unsigned char B) {
    return A & (~B);
}

void displayV1(unsigned char set) {
    printf("{");
    bool first = true;
    for (int i = 0; i < MAX_BITS; i++) {
        if (findV1(set, i)) {
            if (!first) printf(", ");
            printf("%d", i);
            first = false;
        }
    }
    printf("}");
}

void displayBinaryV1(unsigned char set) {
    printf("(");
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        printf("%d", (set >> i) & 1);
    }
    printf(")");
}

int main() {
    printf("========== VARIATION 1: Computer Word / Bitmask ==========\n\n");
    
    unsigned char A = 0;
    initializeV1(&A);
    
    printf("Initial: ");
    displayV1(A);
    printf(" = %d ", A);
    displayBinaryV1(A);
    printf("\n\n");
    
    insertV1(&A, 1);
    printf("After insert(1): ");
    displayV1(A);
    printf(" = %d ", A);
    displayBinaryV1(A);
    printf("\n");
    
    insertV1(&A, 6);
    printf("After insert(6): ");
    displayV1(A);
    printf(" = %d ", A);
    displayBinaryV1(A);
    printf("\n\n");
    
    unsigned char B = 0;
    insertV1(&B, 3);
    insertV1(&B, 6);
    insertV1(&B, 7);
    printf("Set B: ");
    displayV1(B);
    printf(" = %d ", B);
    displayBinaryV1(B);
    printf("\n\n");
    
    unsigned char C = unionV1(A, B);
    printf("Union(A, B): ");
    displayV1(C);
    printf(" = %d ", C);
    displayBinaryV1(C);
    printf("\n");
    
    C = intersectionV1(A, B);
    printf("Intersection(A, B): ");
    displayV1(C);
    printf(" = %d ", C);
    displayBinaryV1(C);
    printf("\n");
    
    C = differenceV1(A, B);
    printf("Difference(A, B): ");
    displayV1(C);
    printf(" = %d ", C);
    displayBinaryV1(C);
    printf("\n");
    
    deleteV1(&A, 6);
    printf("\nAfter delete(6): ");
    displayV1(A);
    printf(" = %d ", A);
    displayBinaryV1(A);
    printf("\n");
    
    deleteV1(&A, 1);
    printf("After delete(1): ");
    displayV1(A);
    printf(" = %d ", A);
    displayBinaryV1(A);
    printf("\n\n");
}
