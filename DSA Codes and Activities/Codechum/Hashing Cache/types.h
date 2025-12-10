#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

#define HASH_BUCKETS 100

// Structure for a single entry in the cache (a Node in the linked list)
typedef struct CacheEntry {
    char *url;                   // The URL string (dynamically allocated key)
    char *content;               // The web page content (dynamically allocated value)
    struct CacheEntry *next;     // Pointer for separate chaining (Open Hashing)
} CacheEntry;

// Structure for the entire Hash Table
typedef struct {
    CacheEntry *buckets[HASH_BUCKETS];
} HashTable;

// --- Function Prototypes ---
void init_cache(HashTable *table);
char *lookup_cache(HashTable *table, const char *key);
bool insert_cache(HashTable *table, const char *key);

unsigned int hash(const char *str);
void free_cache(HashTable *table);
char *simulate_web_request(const char *url);
void cleanup_fetched_results(char **results);
void print_content(const char *url, const char *content);
void run_test_case(HashTable *cache, int test_id);

#endif