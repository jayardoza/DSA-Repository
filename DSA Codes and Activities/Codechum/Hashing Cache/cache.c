#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"

// write your functions here
void init_cache(HashTable *table) {
    for (int i = 0; i < HASH_BUCKETS; i++) {
        table->buckets[i] = NULL;
    }
}

char *lookup_cache(HashTable *table, const char *key) {
    unsigned int index = hash(key);
    
    // Traverse the linked list at the bucket
    CacheEntry *current = table->buckets[index];
    
    while (current != NULL) {
        if (strcmp(current->url, key) == 0) {
            return current->content;
        }
        current = current->next;
    }
    
    return NULL;
}

bool insert_cache(HashTable *table, const char *key) {
    // First check if key already exists
    char *existing_content = lookup_cache(table, key);
    if (existing_content != NULL) {
        // Key already exists, skip insertion
        return true;
    }
    
    // Key doesn't exist, simulate web request
    char *content = simulate_web_request(key);
    
    // Check if web request was successful
    if (content == NULL) {
        return false;  // Web request failed
    }
    
    // Create new cache entry
    CacheEntry *new_entry = (CacheEntry *)malloc(sizeof(CacheEntry));
    if (new_entry == NULL) {
        free(content);
        return false;  // Memory allocation failed
    }
    
    // Allocate and copy URL
    new_entry->url = (char *)malloc(strlen(key) + 1);
    if (new_entry->url == NULL) {
        free(content);
        free(new_entry);
        return false;
    }
    strcpy(new_entry->url, key);
    
    // Store the content
    new_entry->content = content;
    
    // Calculate hash index
    unsigned int index = hash(key);
    
    // Insert at the beginning of the linked list (separate chaining)
    new_entry->next = table->buckets[index];
    table->buckets[index] = new_entry;
    
    return true;
}

void cleanup_fetched_results(char **results) {
    if (results != NULL) {
        free(results);
    }
}