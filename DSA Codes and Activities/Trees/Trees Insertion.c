#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a maximum length for the key
#define MAX_KEY_LEN 100

// 1. Structure Definition
typedef struct node {
   char *key;          // The string element used for comparison and storage
   struct node* LC;   // Left Child pointer
   struct node* RC;   // Right Child pointer
} Node, *BST;


void insert(BST *tree, const char *key_data) {
    // If we've reached an empty spot (leaf position), create new node
    if (*tree == NULL) {
        // Allocate memory for new node
        *tree = (BST)malloc(sizeof(Node));
        if (*tree == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }
        
        // Allocate memory for the key string and copy the data
        (*tree)->key = (char*)malloc(strlen(key_data) + 1);
        if ((*tree)->key == NULL) {
            printf("Memory allocation for key failed!\n");
            free(*tree);
            *tree = NULL;
            return;
        }
        strcpy((*tree)->key, key_data);
        
        // Initialize children to NULL
        (*tree)->LC = NULL;
        (*tree)->RC = NULL;
        
        printf("Inserted key: \"%s\"\n", key_data);
        return;
    }
    
    // Compare the new key with current node's key
    int cmp_result = strcmp(key_data, (*tree)->key);
    
    if (cmp_result < 0) {
        // New key is less than current node's key, go left
        insert(&((*tree)->LC), key_data);
    } else if (cmp_result > 0) {
        // New key is greater than current node's key, go right
        insert(&((*tree)->RC), key_data);
    } else {
        // Key already exists (duplicate)
        printf("Key \"%s\" already exists. Ignoring.\n", key_data);
    }
}

void inorderTraversal(BST tree) {
    if (tree != NULL) {
        inorderTraversal(tree->LC);
        printf("\"%s\" ", tree->key);
        inorderTraversal(tree->RC);
    }
}

void preorderTraversal(BST tree) {
    if (tree != NULL) {
        printf("\"%s\" ", tree->key);
        preorderTraversal(tree->LC);
        preorderTraversal(tree->RC);
    }
}

void postorderTraversal(BST tree) {
    if (tree != NULL) {
        postorderTraversal(tree->LC);
        postorderTraversal(tree->RC);
        printf("\"%s\" ", tree->key);
    }
}

/**
 * @brief Frees all memory allocated for the BST nodes, including the string keys.
 * * @param tree The root of the tree to destroy.
 */
void destroyTree(BST tree) {
    if (tree != NULL) {
        destroyTree(tree->LC);
        destroyTree(tree->RC);

        if (tree->key != NULL) {
            free(tree->key);
        }

        free(tree);
    }
}

int main() {
    // 1. Create and initialize the tree
    BST myTree = NULL;

    printf("--- Initializing and Inserting String Data into BST ---\n");

    // Root: 'Mango'
    // Left: 'Apple', 'Banana'
    // Right: 'Pineapple', 'Grape', 'Orange', 'Kiwi'
    insert(&myTree, "Mango");
    insert(&myTree, "Apple");
    insert(&myTree, "Pineapple");
    insert(&myTree, "Banana");
    insert(&myTree, "Grape");
    insert(&myTree, "Orange");
    insert(&myTree, "Kiwi");

    // Test duplicate handling
    insert(&myTree, "Mango");

    printf("\n\n--- BST Traversal Results ---\n");

    // In-Order: Sorted (A, B, G, K, M, O, P)
    printf("1. In-Order Traversal (Left-Root-Right, Sorted):\n");
    printf("   ");
    inorderTraversal(myTree);
    printf("\n\n");

    // Pre-Order: Root first (M, A, B, P, G, K, O)
    printf("2. Pre-Order Traversal (Root-Left-Right):\n");
    printf("   ");
    preorderTraversal(myTree);
    printf("\n\n");

    // Post-Order: Root last (B, A, K, O, G, P, M)
    printf("3. Post-Order Traversal (Left-Right-Root):\n");
    printf("   ");
    postorderTraversal(myTree);
    printf("\n\n");

    // 3. Clean up memory
    destroyTree(myTree);
    printf("Tree destroyed and memory freed.\n");

    return 0;
}