#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICT_SIZE 100

// Dictionary Node (Key-Value Pair)
typedef struct DictNode {
    char *key;
    int value;
    struct DictNode *next;
} DictNode;

// Dictionary Structure
typedef struct {
    DictNode **buckets;
    int size;
} Dictionary;

// Hash function (same as before)
unsigned int dict_hash(const char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;
    return hash % DICT_SIZE;
}

// Create dictionary
Dictionary* create_dict() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->buckets = calloc(DICT_SIZE, sizeof(DictNode*));
    dict->size = 0;
    return dict;
}

// Insert or update key-value pair
void dict_put(Dictionary *dict, const char *key, int value) {
    unsigned int index = dict_hash(key);
    
    // Check if key exists
    DictNode *current = dict->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value; // Update existing
            return;
        }
        current = current->next;
    }
    
    // Insert new key-value pair
    DictNode *new_node = malloc(sizeof(DictNode));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = dict->buckets[index];
    dict->buckets[index] = new_node;
    dict->size++;
}

// Get value by key
int dict_get(Dictionary *dict, const char *key, int *found) {
    unsigned int index = dict_hash(key);
    DictNode *current = dict->buckets[index];
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            *found = 1;
            return current->value;
        }
        current = current->next;
    }
    
    *found = 0;
    return -1; // Not found
}

// Check if key exists
int dict_contains(Dictionary *dict, const char *key) {
    int found;
    dict_get(dict, key, &found);
    return found;
}

// Usage example
int main() {
    Dictionary *grades = create_dict();
    
    dict_put(grades, "Alice", 85);
    dict_put(grades, "Bob", 92);
    dict_put(grades, "Alice", 90); // Update Alice's grade
    
    int found;
    int alice_grade = dict_get(grades, "Alice", &found);
    if (found) {
        printf("Alice's grade: %d\n", alice_grade); // 90
    }
    
    printf("Contains Bob: %d\n", dict_contains(grades, "Bob")); // 1
    
    return 0;
}