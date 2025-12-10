#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define DELETED_KEY -1

typedef struct {
    int key;
    char value[50];
    int isOccupied;
    int isDeleted;  
} Entry;

typedef struct {
    Entry* entries;
    int size;
    int count;  
} ClosedHashTable;


int hashFunction1(int key) {
    return key % TABLE_SIZE;
}

int hashFunction2(int key) {
    return 7 - (key % 7);  
}

void initClosedHashTable(ClosedHashTable* ht) {
    ht->size = TABLE_SIZE;
    ht->count = 0;
    ht->entries = (Entry*)malloc(TABLE_SIZE * sizeof(Entry));
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->entries[i].key = 0;
        ht->entries[i].isOccupied = 0;
        ht->entries[i].isDeleted = 0;
        strcpy(ht->entries[i].value, "");
    }
}

int linearProbing(ClosedHashTable* ht, int key, int i) {
    return (hashFunction1(key) + i) % TABLE_SIZE;
}


int quadraticProbing(ClosedHashTable* ht, int key, int i) {
    return (hashFunction1(key) + i * i) % TABLE_SIZE;
}


int doubleHashing(ClosedHashTable* ht, int key, int i) {
    return (hashFunction1(key) + i * hashFunction2(key)) % TABLE_SIZE;
}


void insertClosedHash(ClosedHashTable* ht, int key, const char* value, int (*probingFunc)(ClosedHashTable*, int, int)) {
    if (ht->count >= ht->size) {
        printf("Hash table is full!\n");
        return;
    }
    
    int i = 0;
    int index;
    
    do {
        index = probingFunc(ht, key, i);
        
        if (!ht->entries[index].isOccupied || ht->entries[index].isDeleted) {
            ht->entries[index].key = key;
            strcpy(ht->entries[index].value, value);
            ht->entries[index].isOccupied = 1;
            ht->entries[index].isDeleted = 0;
            ht->count++;
            printf("Inserted key %d at index %d\n", key, index);
            return;
        }
        
        if (ht->entries[index].key == key) {
            strcpy(ht->entries[index].value, value);
            printf("Updated key %d at index %d\n", key, index);
            return;
        }
        
        i++;
    } while (i < TABLE_SIZE);
    
    printf("Failed to insert key %d (table full after probing)\n", key);
}


Entry* searchClosedHash(ClosedHashTable* ht, int key, int (*probingFunc)(ClosedHashTable*, int, int)) {
    int i = 0;
    int index;
    
    do {
        index = probingFunc(ht, key, i);
        
        
        if (!ht->entries[index].isOccupied && !ht->entries[index].isDeleted) {
            return NULL;
        }
        
        if (ht->entries[index].isOccupied && 
            !ht->entries[index].isDeleted && 
            ht->entries[index].key == key) {
            return &ht->entries[index];
        }
        
        i++;
    } while (i < TABLE_SIZE);
    
    return NULL;
}


int deleteClosedHash(ClosedHashTable* ht, int key, int (*probingFunc)(ClosedHashTable*, int, int)) {
    Entry* entry = searchClosedHash(ht, key, probingFunc);
    
    if (entry != NULL) {
        entry->isDeleted = 1;
        ht->count--;
        printf("Marked key %d as deleted\n", key);
        return 1;
    }
    
    printf("Key %d not found for deletion\n", key);
    return 0;
}


void displayClosedHashTable(ClosedHashTable* ht) {
    printf("\nClosed Hashing Table (Open Addressing):\n");
    printf("========================================\n");
    printf("Index\tKey\tValue\tOccupied\tDeleted\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d\t", i);
        if (ht->entries[i].isOccupied && !ht->entries[i].isDeleted) {
            printf("%d\t%s\t", ht->entries[i].key, ht->entries[i].value);
        } else if (ht->entries[i].isDeleted) {
            printf("%d\t%s\t", DELETED_KEY, "[DELETED]");
        } else {
            printf("-\t-\t");
        }
        printf("%s\t\t%s\n", 
               ht->entries[i].isOccupied ? "Yes" : "No",
               ht->entries[i].isDeleted ? "Yes" : "No");
    }
    printf("Total entries: %d/%d\n\n", ht->count, ht->size);
}


void freeClosedHashTable(ClosedHashTable* ht) {
    free(ht->entries);
    ht->entries = NULL;
}


void demoLinearProbing() {
    ClosedHashTable ht;
    initClosedHashTable(&ht);
    
    printf("\n=== Closed Hashing with Linear Probing Demo ===\n");
    
    insertClosedHash(&ht, 10, "Alice", linearProbing);
    insertClosedHash(&ht, 20, "Bob", linearProbing);
    insertClosedHash(&ht, 30, "Charlie", linearProbing);
    insertClosedHash(&ht, 40, "David", linearProbing);
    insertClosedHash(&ht, 11, "Eve", linearProbing);  // Potential collision
    
    displayClosedHashTable(&ht);
    
    
    Entry* found = searchClosedHash(&ht, 30, linearProbing);
    if (found != NULL) {
        printf("Found key 30: %s\n", found->value);
    }
    
    
    deleteClosedHash(&ht, 20, linearProbing);
    displayClosedHashTable(&ht);
    
    
    insertClosedHash(&ht, 21, "Frank", linearProbing);
    displayClosedHashTable(&ht);
    
    freeClosedHashTable(&ht);
}


void demoQuadraticProbing() {
    ClosedHashTable ht;
    initClosedHashTable(&ht);
    
    printf("\n=== Closed Hashing with Quadratic Probing Demo ===\n");
    
    insertClosedHash(&ht, 10, "Alice", quadraticProbing);
    insertClosedHash(&ht, 20, "Bob", quadraticProbing);
    insertClosedHash(&ht, 30, "Charlie", quadraticProbing);
    insertClosedHash(&ht, 40, "David", quadraticProbing);
    insertClosedHash(&ht, 11, "Eve", quadraticProbing);
    
    displayClosedHashTable(&ht);
    
    freeClosedHashTable(&ht);
}


void demoDoubleHashing() {
    ClosedHashTable ht;
    initClosedHashTable(&ht);
    
    printf("\n=== Closed Hashing with Double Hashing Demo ===\n");
    
    insertClosedHash(&ht, 10, "Alice", doubleHashing);
    insertClosedHash(&ht, 20, "Bob", doubleHashing);
    insertClosedHash(&ht, 30, "Charlie", doubleHashing);
    insertClosedHash(&ht, 40, "David", doubleHashing);
    insertClosedHash(&ht, 11, "Eve", doubleHashing);
    
    displayClosedHashTable(&ht);
    
    freeClosedHashTable(&ht);
}


int main() {
    printf("Hash Table Implementations in C\n");
    printf("===============================\n");
    
    demoOpenHashing();
    
    demoLinearProbing();
    demoQuadraticProbing();
    demoDoubleHashing();
    
    return 0;
}
