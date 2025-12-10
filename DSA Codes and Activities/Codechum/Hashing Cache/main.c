#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"

/**
 * @brief Simple hash function (DJB2) to generate an index for the key (URL).
 * @param str The input URL string.
 * @return The hash index [0, HASH_BUCKETS - 1].
 */
unsigned int hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % HASH_BUCKETS;
}

/**
 * @brief Runs a specific test case from the original sequential tests.
 * @param cache Pointer to the HashTable instance.
 * @param test_id The ID of the test to run (1 to 5).
 */
void run_test_case(HashTable *cache, int test_id) {
    char *fetched_content = NULL;
    const char *url_to_test = NULL;
    bool insertion_success = false;

    // Note: Tests 2 and 3 depend on test 1 being run first.
    // Tests 4 and 5 depend on tests 1-3 having run.

    switch (test_id) {
        case 1:
            // --- Test 1: New URL (Cache MISS -> Insert calls Web Request -> Cache INSERT) ---
            printf("\n--- Test 1: New URL Insertion (https://www.google.com/cse_blog) ---\n");
            url_to_test = "https://www.google.com/cse_blog";

            fetched_content = lookup_cache(cache, url_to_test);

            if (fetched_content == NULL) {
                printf("  [Lookup Status] URL '%s' MISS. Attempting to fetch and insert (WEB REQUEST in progress)...\n", url_to_test);

                insertion_success = insert_cache(cache, url_to_test);

                if (insertion_success) {
                    printf("  [Insert Status] Insertion successful (Content fetched and cached).\n");
                } else {
                    printf("  [Insert Status] Insertion failed (Web request returned no content).\n");
                }

                fetched_content = lookup_cache(cache, url_to_test);
            } else {
                printf("  [Lookup Status] URL '%s' HIT. Returning cached results (ERROR: Should have been a MISS).\n", url_to_test);
            }
            print_content(url_to_test, fetched_content);
            break;

        case 2:
            // --- Test 2: Existing URL (Expected Cache HIT) ---
            printf("\n--- Test 2: Existing URL Lookup (https://www.google.com/cse_blog) ---\n");
            url_to_test = "https://www.google.com/cse_blog";

            // Lookup (Should be a HIT now, if Test 1 was run)
            fetched_content = lookup_cache(cache, url_to_test);

            if (fetched_content != NULL) {
                printf("  [Lookup Status] URL '%s' HIT. Returning cached content.\n", url_to_test);
            } else {
                 printf("  [Lookup Status] URL '%s' MISS (ERROR: Test 1 must be run first).\n", url_to_test);
            }
            print_content(url_to_test, fetched_content);
            break;

        case 3:
            // --- Test 3: Redundant Insertion Test (Expected Skip) ---
            printf("\n--- Test 3: Redundant Insertion Test (https://www.google.com/cse_blog) ---\n");
            url_to_test = "https://www.google.com/cse_blog";

            insertion_success = insert_cache(cache, url_to_test);

            if (insertion_success) {
                printf("  [Insert Status] Insertion was logically skipped because URL '%s' already exists.\n", url_to_test);
            } else {
                printf("  [Insert Status] Error: Insertion failed for existing URL.\n");
            }

            printf("  Note: No web request occurred. Cache content is unchanged.\n");

            fetched_content = lookup_cache(cache, url_to_test);
            print_content(url_to_test, fetched_content);
            break;

        case 4:
            // --- Test 4: Another New URL (Cache MISS -> Insert calls Web Request -> Cache INSERT) ---
            printf("\n--- Test 4: Second New URL Insertion (https://api.google.com/api/v1/earnings) ---\n");
            url_to_test = "https://api.google.com/api/v1/earnings";

            fetched_content = lookup_cache(cache, url_to_test);

            if (fetched_content == NULL) {
                printf("  [Lookup Status] URL '%s' MISS. Attempting to fetch and insert (WEB REQUEST in progress)...\n", url_to_test);

                insertion_success = insert_cache(cache, url_to_test);

                if (insertion_success) {
                    printf("  [Insert Status] Insertion successful (Content fetched and cached).\n");
                } else {
                    printf("  [Insert Status] Insertion failed (Web request returned no content).\n");
                }

                fetched_content = lookup_cache(cache, url_to_test);
            } else {
                printf("  [Lookup Status] URL '%s' HIT. Returning cached content (ERROR: Should have been a MISS).\n", url_to_test);
            }
            print_content(url_to_test, fetched_content);
            break;

        case 5:
            // --- Test 5: Failing URL (Cache MISS -> Web Request Fails) ---
            printf("\n--- Test 5: Failing URL (http://404.example.com) ---\n");
            url_to_test = "http://404.example.com/notfound";

            fetched_content = lookup_cache(cache, url_to_test);

            if (fetched_content == NULL) {
                printf("  [Lookup Status] URL '%s' MISS. Attempting to fetch and insert (WEB REQUEST in progress)...\n", url_to_test);

                insertion_success = insert_cache(cache, url_to_test);

                if (insertion_success) {
                    printf("  [Insert Status] Error: This should not happen. Insertion successful.\n");
                } else {
                    printf("  [Insert Status] Insertion aborted because web request returned no valid content (simulated 404).\n");
                }

                fetched_content = lookup_cache(cache, url_to_test);
            } else {
                printf("  [Lookup Status] URL '%s' HIT. Returning cached results (ERROR: URL should not exist).\n", url_to_test);
            }
            print_content(url_to_test, fetched_content);
            break;

        default:
            printf("\nInvalid choice. Please enter a number between 1 and 5 (or 0 to exit).\n");
            break;
    }
}


// --- Main Program Logic ---

int main() {
    HashTable search_cache;
    init_cache(&search_cache);
    int choice = -1;

    printf("Google Web Content Cache Simulation (Open Hashing)\n");
    printf("----------------------------------------------------\n");
    printf("Cache Key: URL | Cache Value: Page Content String\n");
    printf("Note: Test Cases 2 and 3 require Test 1 to be run first.\n");

    while (choice != 0) {
        printf("\nSelect a test case to run:\n");
        printf("1. Run Test 1: New URL Insertion (https://www.google.com/cse_blog)\n");
        printf("2. Run Test 2: Existing URL Lookup (Expected HIT)\n");
        printf("3. Run Test 3: Redundant Insertion (Expected SKIP)\n");
        printf("4. Run Test 4: Second New URL Insertion (https://api.google.com/api/v1/earnings)\n");
        printf("5. Run Test 5: Failing URL (Web Request Fails)\n");
        printf("0. Exit and Free Memory\n");
        printf("Enter choice: ");

        // Ensure only one integer is read
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            // Clear the input buffer to prevent infinite loop
            while (getchar() != '\n');
            choice = -1; // Reset choice
            continue;
        }

        if (choice == 0) {
            break;
        }

        run_test_case(&search_cache, choice);
    }

    // Clean up memory before exiting
    free_cache(&search_cache);

    return 0;
}