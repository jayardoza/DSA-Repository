#include <stdio.h>
#include <stdbool.h>

#define MAX_BITS 8
#define ARRAY_SIZE 8

// ==================== VARIATION 2: Bit Fields ====================

typedef struct {
    unsigned char field : 8;  // 8-bit field
} Set;

void initializeV2(Set *set) {
    set->field = 0;
}

void insertV2(Set *set, int element) {
    if (element < 0 || element >= MAX_BITS) {
        printf("Error: Element %d out of range [0-%d]\n", element, MAX_BITS-1);
        return;
    }
    unsigned char mask = 1 << element;
    set->field |= mask;
}

void deleteV2(Set *set, int element) {
    if (element < 0 || element >= MAX_BITS) {
        printf("Error: Element %d out of range [0-%d]\n", element, MAX_BITS-1);
        return;
    }
    unsigned char mask = 1 << element;
    mask = ~mask;
    set->field &= mask;
}

bool findV2(Set set, int element) {
    if (element < 0 || element >= MAX_BITS) {
        return false;
    }
    unsigned char mask = 1 << element;
    return (set.field & mask) != 0;
}

Set unionV2(Set A, Set B) {
    Set result;
    result.field = A.field | B.field;
    return result;
}

Set intersectionV2(Set A, Set B) {
    Set result;
    result.field = A.field & B.field;
    return result;
}

Set differenceV2(Set A, Set B) {
    Set result;
    result.field = A.field & (~B.field);
    return result;
}

void displayV2(Set set) {
    printf("{");
    bool first = true;
    for (int i = 0; i < MAX_BITS; i++) {
        if (findV2(set, i)) {
            if (!first) printf(", ");
            printf("%d", i);
            first = false;
        }
    }
    printf("}");
}

void displayBinaryV2(Set set) {
    printf("(");
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        printf("%d", (set.field >> i) & 1);
    }
    printf(")");
}

int main() {
 	printf("========== VARIATION 2: Bit Fields ==========\n\n");
    
    Set setA;
    initializeV2(&setA);
    
    printf("Initial: ");
    displayV2(setA);
    printf(" field = %d ", setA.field);
    displayBinaryV2(setA);
    printf("\n\n");
    
    insertV2(&setA, 0);
    printf("After insert(0): ");
    displayV2(setA);
    printf(" field = %d ", setA.field);
    displayBinaryV2(setA);
    printf("\n");
    
    insertV2(&setA, 4);
    printf("After insert(4): ");
    displayV2(setA);
    printf(" field = %d ", setA.field);
    displayBinaryV2(setA);
    printf("\n");
    
    insertV2(&setA, 5);
    printf("After insert(5): ");
    displayV2(setA);
    printf(" field = %d ", setA.field);
    displayBinaryV2(setA);
    printf("\n\n");
    
    Set setB;
    initializeV2(&setB);
    insertV2(&setB, 2);
    insertV2(&setB, 5);
    printf("Set B: ");
    displayV2(setB);
    printf(" field = %d ", setB.field);
    displayBinaryV2(setB);
    printf("\n\n");
    
    Set setC = unionV2(setA, setB);
    printf("Union(A, B): ");
    displayV2(setC);
    printf(" field = %d ", setC.field);
    displayBinaryV2(setC);
    printf("\n");
    
    setC = intersectionV2(setA, setB);
    printf("Intersection(A, B): ");
    displayV2(setC);
    printf(" field = %d ", setC.field);
    displayBinaryV2(setC);
    printf("\n");
    
    setC = differenceV2(setA, setB);
    printf("Difference(A, B): ");
    displayV2(setC);
    printf(" field = %d ", setC.field);
    displayBinaryV2(setC);
    printf("\n");
    
    deleteV2(&setA, 5);
    printf("\nAfter delete(5): ");
    displayV2(setA);
    printf(" field = %d ", setA.field);
    displayBinaryV2(setA);
    printf("\n");
    
    deleteV2(&setA, 4);
    printf("After delete(4): ");
    displayV2(setA);
    printf(" field = %d ", setA.field);
    displayBinaryV2(setA);
    printf("\n\n");
    
}
