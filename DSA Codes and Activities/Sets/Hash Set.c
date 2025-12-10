#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// ==================== SET NODE STRUCTURE ====================
typedef struct SetNode {
    char *key;              // The data stored in set
    struct SetNode *next;   // Pointer to next node in chain
} SetNode;

// ==================== HASH SET STRUCTURE ====================
typedef struct {
    SetNode **buckets;      // Array of linked list pointers
    int size;               // Total number of elements
    int capacity;           // Number of buckets (TABLE_SIZE)
} HashSet;

// ==================== HASH FUNCTION ====================
/**
 * Converts any string into array index (0 to TABLE_SIZE-1)
 * WHY? We need to distribute elements evenly across buckets
 */
unsigned int hash(const char *key) {
    unsigned long hash_value = 5381;  // Starting prime number
    int c;
    
    // Process each character in string
    while ((c = *key++)) {
        // Magic formula: hash * 33 + character
        hash_value = ((hash_value << 5) + hash_value) + c;
    }
    
    return hash_value % TABLE_SIZE;  // Ensure it fits in our array
}

// ==================== SET CREATION ====================
/**
 * Creates empty hash set
 * WHY? We need to initialize the array and counters
 */
HashSet* create_set() {
    HashSet *set = (HashSet*)malloc(sizeof(HashSet));
    
    // Allocate array of pointers, all initialized to NULL
    set->buckets = (SetNode**)calloc(TABLE_SIZE, sizeof(SetNode*));
    set->size = 0;
    set->capacity = TABLE_SIZE;
    
    printf("✅ Created new set with %d buckets\n", TABLE_SIZE);
    return set;
}

// ==================== ADD TO SET ====================
/**
 * Adds element to set if not already present
 * WHY? Sets only store unique elements
 */
void set_add(HashSet *set, const char *key) {
    // Step 1: Find which bucket this key belongs to
    unsigned int bucket_index = hash(key);
    printf("🔍 Adding '%s' → hash index: %u\n", key, bucket_index);
    
    // Step 2: Check if key already exists in this bucket's chain
    SetNode *current = set->buckets[bucket_index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            printf("   ⚠️  '%s' already exists! Sets don't allow duplicates.\n", key);
            return;  // Exit - no duplicates in sets!
        }
        current = current->next;
    }
    
    // Step 3: Create new node (key doesn't exist)
    SetNode *new_node = (SetNode*)malloc(sizeof(SetNode));
    new_node->key = strdup(key);  // Copy string (important!)
    new_node->next = set->buckets[bucket_index];  // Insert at front
    
    // Step 4: Update bucket to point to new node
    set->buckets[bucket_index] = new_node;
    set->size++;
    
    printf("   ✅ Added '%s' to bucket %u\n", key, bucket_index);
}

// ==================== CHECK MEMBERSHIP ====================
/**
 * Returns 1 if key exists in set, 0 otherwise
 * WHY? Basic set operation - "is this element in the set?"
 */
int set_contains(HashSet *set, const char *key) {
    unsigned int bucket_index = hash(key);
    SetNode *current = set->buckets[bucket_index];
    
    printf("🔎 Searching for '%s' in bucket %u: ", key, bucket_index);
    
    // Traverse the chain in this bucket
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            printf("FOUND! 🎉\n");
            return 1;
        }
        current = current->next;
    }
    
    printf("NOT FOUND 😞\n");
    return 0;
}

// ==================== REMOVE FROM SET ====================
/**
 * Removes element from set if it exists
 * WHY? We need to delete elements while maintaining structure
 */
int set_remove(HashSet *set, const char *key) {
    unsigned int bucket_index = hash(key);
    SetNode *current = set->buckets[bucket_index];
    SetNode *previous = NULL;
    
    printf("🗑️  Removing '%s' from bucket %u: ", key, bucket_index);
    
    // Search for the key in this bucket's chain
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Key found! Now remove it from chain
            
            if (previous == NULL) {
                // Removing first node in chain
                set->buckets[bucket_index] = current->next;
            } else {
                // Removing middle or last node
                previous->next = current->next;
            }
            
            // Free the memory
            free(current->key);  // Free the copied string
            free(current);       // Free the node itself
            set->size--;
            
            printf("SUCCESS! ✅\n");
            return 1;
        }
        
        // Move to next node in chain
        previous = current;
        current = current->next;
    }
    
    printf("Key not found! ❌\n");
    return 0;
}

// ==================== PRINT SET ====================
/**
 * Visualizes the entire set structure
 * WHY? Debugging and understanding how hash tables work
 */
void print_set(HashSet *set) {
    printf("\n📊 SET VISUALIZATION (%d elements):\n", set->size);
    printf("=========================================\n");
    
    for (int i = 0; i < set->capacity; i++) {
        printf("Bucket [%d]: ", i);
        
        SetNode *current = set->buckets[i];
        if (current == NULL) {
            printf("EMPTY");
        } else {
            while (current != NULL) {
                printf("'%s'", current->key);
                if (current->next != NULL) {
                    printf(" → ");  // Show chain links
                }
                current = current->next;
            }
        }
        printf("\n");
    }
    printf("=========================================\n\n");
}

// ==================== FREE MEMORY ====================
/**
 * Cleans up all allocated memory
 * WHY? Prevent memory leaks - CRITICAL in C!
 */
void free_set(HashSet *set) {
    printf("🧹 Cleaning up set memory...\n");
    
    for (int i = 0; i < set->capacity; i++) {
        SetNode *current = set->buckets[i];
        
        while (current != NULL) {
            SetNode *temp = current;
            current = current->next;
            
            free(temp->key);  // Free the string copy
            free(temp);       // Free the node
        }
    }
    
    free(set->buckets);  // Free the buckets array
    free(set);           // Free the set structure
    
    printf("✅ All memory freed!\n");
}

// ==================== SET DEMONSTRATION ====================
void demonstrate_set() {
    printf("\n🎯 HASH SET DEMONSTRATION\n");
    printf("==========================\n\n");
    
    // Create empty set
    HashSet *fruit_set = create_set();
    
    // Add elements
    printf("1. ADDING ELEMENTS:\n");
    printf("-------------------\n");
    set_add(fruit_set, "apple");
    set_add(fruit_set, "banana");
    set_add(fruit_set, "cherry");
    set_add(fruit_set, "apple");  // Duplicate - should be rejected!
    set_add(fruit_set, "date");
    set_add(fruit_set, "elderberry");
    
    // Show structure
    print_set(fruit_set);
    
    // Test membership
    printf("2. MEMBERSHIP TESTS:\n");
    printf("--------------------\n");
    set_contains(fruit_set, "apple");
    set_contains(fruit_set, "grape");
    set_contains(fruit_set, "banana");
    
    // Remove elements
    printf("\n3. REMOVAL TESTS:\n");
    printf("-----------------\n");
    set_remove(fruit_set, "cherry");
    set_remove(fruit_set, "watermelon");  // Not in set
    
    // Show final structure
    print_set(fruit_set);
    
    // Clean up
    free_set(fruit_set);
}