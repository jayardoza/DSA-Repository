#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// ==================== DICTIONARY NODE STRUCTURE ====================
typedef struct DictNode {
    char *key;              // Lookup key
    int value;              // Associated value
    struct DictNode *next;  // Next node in chain
} DictNode;

// ==================== DICTIONARY STRUCTURE ====================
typedef struct {
    DictNode **buckets;     // Array of linked list pointers
    int size;               // Number of key-value pairs
    int capacity;           // Number of buckets
} Dictionary;

// ==================== DICTIONARY CREATION ====================
/**
 * Creates empty dictionary
 * WHY? Same as set but stores key-value pairs
 */

Dictionary* create_dict() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->buckets = (DictNode**)calloc(TABLE_SIZE, sizeof(DictNode*));
    dict->size = 0;
    dict->capacity = TABLE_SIZE;
    
    printf("✅ Created new dictionary with %d buckets\n", TABLE_SIZE);
    return dict;
}

// ==================== PUT KEY-VALUE PAIR ====================
/**
 * Inserts or updates key-value pair
 * WHY? Dictionaries map keys to values (can update existing keys)
 */
void dict_put(Dictionary *dict, const char *key, int value) {
    unsigned int bucket_index = hash(key);
    
    printf("📝 Putting ['%s' → %d] at bucket %u: ", key, value, bucket_index);
    
    // Check if key already exists (for update)
    DictNode *current = dict->buckets[bucket_index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Key exists - update value
            printf("UPDATING existing value from %d to %d\n", current->value, value);
            current->value = value;
            return;
        }
        current = current->next;
    }
    
    // Key doesn't exist - insert new pair
    DictNode *new_node = (DictNode*)malloc(sizeof(DictNode));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = dict->buckets[bucket_index];  // Insert at front
    dict->buckets[bucket_index] = new_node;
    dict->size++;
    
    printf("ADDED new mapping ✅\n");
}

// ==================== GET VALUE BY KEY ====================
/**
 * Retrieves value for given key
 * WHY? Main dictionary operation - lookup values by key
 */
int dict_get(Dictionary *dict, const char *key, int *found) {
    unsigned int bucket_index = hash(key);
    DictNode *current = dict->buckets[bucket_index];
    
    printf("🔍 Getting value for '%s' from bucket %u: ", key, bucket_index);
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            *found = 1;
            printf("FOUND → %d ✅\n", current->value);
            return current->value;
        }
        current = current->next;
    }
    
    *found = 0;
    printf("KEY NOT FOUND ❌\n");
    return -1;  // Return value doesn't matter when not found
}

// ==================== REMOVE KEY-VALUE PAIR ====================
/**
 * Removes key-value pair from dictionary
 * WHY? Need to delete entries while maintaining structure
 */
int dict_remove(Dictionary *dict, const char *key) {
    unsigned int bucket_index = hash(key);
    DictNode *current = dict->buckets[bucket_index];
    DictNode *previous = NULL;
    
    printf("🗑️  Removing key '%s' from bucket %u: ", key, bucket_index);
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Found the key to remove
            
            if (previous == NULL) {
                // Remove first node in chain
                dict->buckets[bucket_index] = current->next;
            } else {
                // Remove middle/last node
                previous->next = current->next;
            }
            
            free(current->key);
            free(current);
            dict->size--;
            
            printf("SUCCESS ✅\n");
            return 1;
        }
        
        previous = current;
        current = current->next;
    }
    
    printf("KEY NOT FOUND ❌\n");
    return 0;
}

// ==================== CHECK IF KEY EXISTS ====================
/**
 * Returns 1 if key exists, 0 otherwise
 * WHY? Quick existence check without retrieving value
 */
int dict_contains(Dictionary *dict, const char *key) {
    int found;
    dict_get(dict, key, &found);  // Reuse get function
    return found;
}

// ==================== PRINT DICTIONARY ====================
/**
 * Visualizes entire dictionary structure
 * WHY? See how key-value pairs are distributed
 */
void print_dict(Dictionary *dict) {
    printf("\n📊 DICTIONARY VISUALIZATION (%d key-value pairs):\n", dict->size);
    printf("=================================================\n");
    
    for (int i = 0; i < dict->capacity; i++) {
        printf("Bucket [%d]: ", i);
        
        DictNode *current = dict->buckets[i];
        if (current == NULL) {
            printf("EMPTY");
        } else {
            while (current != NULL) {
                printf("('%s':%d)", current->key, current->value);
                if (current->next != NULL) {
                    printf(" → ");
                }
                current = current->next;
            }
        }
        printf("\n");
    }
    printf("=================================================\n\n");
}

// ==================== FREE DICTIONARY MEMORY ====================
/**
 * Cleans up all dictionary memory
 * WHY? Prevent memory leaks - ESSENTIAL!
 */
void free_dict(Dictionary *dict) {
    printf("🧹 Cleaning up dictionary memory...\n");
    
    for (int i = 0; i < dict->capacity; i++) {
        DictNode *current = dict->buckets[i];
        
        while (current != NULL) {
            DictNode *temp = current;
            current = current->next;
            
            free(temp->key);
            free(temp);
        }
    }
    
    free(dict->buckets);
    free(dict);
    
    printf("✅ All dictionary memory freed!\n");
}

// ==================== DICTIONARY DEMONSTRATION ====================
void demonstrate_dictionary() {
    printf("\n🎯 DICTIONARY DEMONSTRATION\n");
    printf("============================\n\n");
    
    // Create empty dictionary
    Dictionary *student_grades = create_dict();
    
    // Add grade entries
    printf("1. ADDING/UPDATEING GRADES:\n");
    printf("---------------------------\n");
    dict_put(student_grades, "Alice", 85);
    dict_put(student_grades, "Bob", 92);
    dict_put(student_grades, "Charlie", 78);
    dict_put(student_grades, "Alice", 90);  // Update Alice's grade
    
    // Show structure
    print_dict(student_grades);
    
    // Retrieve grades
    printf("2. RETRIEVING GRADES:\n");
    printf("----------------------\n");
    int found;
    int grade;
    
    grade = dict_get(student_grades, "Bob", &found);
    if (found) printf("Bob's grade: %d\n", grade);
    
    grade = dict_get(student_grades, "David", &found);
    if (!found) printf("David is not in the class.\n");
    
    // Check existence
    printf("\n3. EXISTENCE CHECKS:\n");
    printf("---------------------\n");
    printf("Contains 'Charlie': %s\n", 
           dict_contains(student_grades, "Charlie") ? "YES" : "NO");
    printf("Contains 'Eve': %s\n", 
           dict_contains(student_grades, "Eve") ? "YES" : "NO");
    
    // Remove entries
    printf("\n4. REMOVING ENTRIES:\n");
    printf("---------------------\n");
    dict_remove(student_grades, "Charlie");
    dict_remove(student_grades, "Eve");  // Not in dictionary
    
    // Show final structure
    print_dict(student_grades);
    
    // Real-world example: Word frequency counter
    printf("5. REAL-WORLD EXAMPLE - WORD FREQUENCIES:\n");
    printf("-----------------------------------------\n");
    
    Dictionary *word_freq = create_dict();
    const char *text[] = {"the", "cat", "in", "the", "hat", "the", "cat", NULL};
    
    printf("Text: ");
    for (int i = 0; text[i] != NULL; i++) {
        printf("%s ", text[i]);
        
        // Count frequency
        int count;
        int exists = dict_contains(word_freq, text[i]);
        if (exists) {
            count = dict_get(word_freq, text[i], &found);
            dict_put(word_freq, text[i], count + 1);
        } else {
            dict_put(word_freq, text[i], 1);
        }
    }
    printf("\n");
    
    print_dict(word_freq);
    
    // Clean up
    free_dict(student_grades);
    free_dict(word_freq);
}

// ==================== MAIN FUNCTION ====================
int main() {
    printf("🌈 COMPLETE SETS & DICTIONARIES IN C 🌈\n");
    printf("========================================\n");
    
    // Demonstrate both data structures
    demonstrate_set();
    demonstrate_dictionary();
    
    printf("\n🎉 ALL DEMONSTRATIONS COMPLETE! 🎉\n");
    printf("You now understand Sets & Dictionaries in C! 💪\n");
    
    return 0;
}