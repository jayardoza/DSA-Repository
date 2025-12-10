#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "functions.h"

void runTests(int test_choice) {
    VHeap test_heap;
    int test_L = -1;
    int test_id_counter = 1;

    Article createTestArticle(int id, const char* title, const char* content) {
        Article a;
        a.id = id;
        strcpy(a.title, title);
        strcpy(a.content, content);
        return a;
    }

    printf("\n--- Running Test Case %d ---\n", test_choice);
    initVHeap(&test_heap);

    switch(test_choice) {
        case 1:
            // Test Case 1: Insert at the beginning, end, and middle.
            printf("Test Case 1: Insertion Functionality\n");

            Article article1 = createTestArticle(test_id_counter++, "Article 1", "This is the first article.");
            insertArticle(&test_heap, &test_L, article1, 0);
            printf("Inserted article 1 at position 0.\n");
            viewArticles(test_heap, test_L);

            Article article2 = createTestArticle(test_id_counter++, "Article 2", "This is the second article.");
            insertArticle(&test_heap, &test_L, article2, -1);
            printf("Inserted article 2 at the end.\n");
            viewArticles(test_heap, test_L);

            Article article3 = createTestArticle(test_id_counter++, "Article 3", "This is the third article.");
            insertArticle(&test_heap, &test_L, article3, 1);
            printf("Inserted article 3 at position 1 (middle).\n");
            viewArticles(test_heap, test_L);

            printf("Insertion test complete.\n");
            break;

        case 2:
            // Test Case 2: Search for articles.
            printf("Test Case 2: Search Functionality\n");

            Article article4 = createTestArticle(test_id_counter++, "Search Test 1", "Content for search test 1.");
            insertArticle(&test_heap, &test_L, article4, -1);
            Article article5 = createTestArticle(test_id_counter++, "Search Test 2", "Content for search test 2.");
            insertArticle(&test_heap, &test_L, article5, -1);

            printf("Searching for existing article (ID %d)...\n", article4.id);
            searchArticle(test_heap, test_L, article4.id);

            int non_existent_id = 999;
            printf("Searching for non-existent article (ID %d)...\n", non_existent_id);
            searchArticle(test_heap, test_L, non_existent_id);

            printf("Search test complete.\n");
            break;

        case 3:
            // Test Case 3: Delete articles from the list.
            printf("Test Case 3: Deletion Functionality\n");
            Article article6 = createTestArticle(test_id_counter++, "First to Delete", "This is the first article.");
            insertArticle(&test_heap, &test_L, article6, -1);
            Article article7 = createTestArticle(test_id_counter++, "Middle to Delete", "This is the middle article.");
            insertArticle(&test_heap, &test_L, article7, -1);
            Article article8 = createTestArticle(test_id_counter++, "Last to Delete", "This is the last article.");
            insertArticle(&test_heap, &test_L, article8, -1);
            viewArticles(test_heap, test_L);

            printf("Deleting middle article (ID %d)...\n", article7.id);
            deleteArticle(&test_heap, &test_L, article7.id);
            viewArticles(test_heap, test_L);

            printf("Deleting first article (ID %d)...\n", article6.id);
            deleteArticle(&test_heap, &test_L, article6.id);
            viewArticles(test_heap, test_L);

            printf("Deleting last article (ID %d)...\n", article8.id);
            deleteArticle(&test_heap, &test_L, article8.id);
            viewArticles(test_heap, test_L);

            printf("Deletion test complete.\n");
            break;

        case 4:
            // Test Case 4: Test deletion of a non-existent article.
            printf("Test Case 4: Delete non-existent article\n");
            Article article9 = createTestArticle(test_id_counter++, "Test Article", "This is the article.");
            insertArticle(&test_heap, &test_L, article9, -1);
            viewArticles(test_heap, test_L);

            int non_existent_id_delete = 999;
            printf("Attempting to delete non-existent article (ID %d)...\n", non_existent_id_delete);
            deleteArticle(&test_heap, &test_L, non_existent_id_delete);
            viewArticles(test_heap, test_L);

            printf("Deletion of non-existent article test complete.\n");
            break;

        case 5:
            // Test Case 5: Full heap insertion.
            printf("Test Case 5: Heap Full Insertion\n");
            for(int i = 0; i < MAX_SIZE; i++) {
                Article temp_article = createTestArticle(test_id_counter++, "Filler", "This is a filler article.");
                insertArticle(&test_heap, &test_L, temp_article, -1);
            }
            printf("Heap should be full now.\n");
            viewArticles(test_heap, test_L);

            Article article_overflow = createTestArticle(test_id_counter++, "Overflow", "This should fail.");
            insertArticle(&test_heap, &test_L, article_overflow, -1);
            printf("Attempted to insert an article into a full heap.\n");

            printf("Heap full insertion test complete.\n");
            break;

        default:
            printf("Invalid test case number.\n");
            break;
    }
    printf("--- Test Case %d Finished ---\n\n", test_choice);
}

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    VHeap my_knowledge_base;
    int L = -1; // The head of the list, initially empty.
    int next_id = 1;
    int choice, sub_choice, id, position;
    Article new_article;

    initVHeap(&my_knowledge_base);

    do {
        printf("--- Knowledge Base Menu ---\n");
        printf("1. Insert new article\n");
        printf("2. View list of articles\n");
        printf("3. Search for an article\n");
        printf("4. Delete an article\n");
        printf("5. Run test cases\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            choice = 0; // Invalid input
        } else {
            clearInputBuffer();
        }

        switch (choice) {
            case 1:
                printf("\n--- Insert New Article ---\n");
                new_article.id = next_id++;
                printf("Enter article title (max 64 chars): ");
                fgets(new_article.title, sizeof(new_article.title), stdin);
                new_article.title[strcspn(new_article.title, "\n")] = 0; // Remove newline

                printf("Enter article content (max 255 chars): ");
                fgets(new_article.content, sizeof(new_article.content), stdin);
                new_article.content[strcspn(new_article.content, "\n")] = 0; // Remove newline

                printf("Enter position to insert (-1 for end): ");
                if (scanf("%d", &position) != 1) {
                    clearInputBuffer();
                    printf("Invalid position. Inserting at the end.\n");
                    position = -1;
                }
                clearInputBuffer();

                if (insertArticle(&my_knowledge_base, &L, new_article, position)) {
                    printf("Article successfully inserted with ID %d.\n\n", new_article.id);
                } else {
                    next_id--; // Revert ID if insertion failed.
                }
                break;

            case 2:
                viewArticles(my_knowledge_base, L);
                break;

            case 3:
                printf("Enter article ID to search: ");
                if (scanf("%d", &id) != 1) {
                    clearInputBuffer();
                    printf("Invalid ID.\n\n");
                } else {
                    clearInputBuffer();
                    searchArticle(my_knowledge_base, L, id);
                }
                break;

            case 4:
                printf("Enter article ID to delete: ");
                if (scanf("%d", &id) != 1) {
                    clearInputBuffer();
                    printf("Invalid ID.\n\n");
                } else {
                    clearInputBuffer();
                    deleteArticle(&my_knowledge_base, &L, id);
                }
                break;

            case 5:
                printf("\n--- Test Cases Menu ---\n");
                printf("1. Test Insertion Functionality\n");
                printf("2. Test Search Functionality\n");
                printf("3. Test Deletion Functionality\n");
                printf("4. Test Delete Non-Existent Article\n");
                printf("5. Test Heap Full Insertion\n");
                printf("Enter test case number: ");
                if (scanf("%d", &sub_choice) != 1) {
                    clearInputBuffer();
                    sub_choice = 0;
                } else {
                    clearInputBuffer();
                }
                runTests(sub_choice);
                break;

            case 6:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n\n");
                break;
        }

    } while (choice != 6);

    return 0;
}
