#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

void insert(BST *tree, const char *key_data);
void inorderTraversal(BST tree);
void destroyTree(BST tree);

// Find the minimum node in a subtree
BST findMin(BST node) {
    BST current = node;
    while (current && current->LC != NULL) {
        current = current->LC;
    }
    return current;
}

// Find the maximum node in a subtree
BST findMax(BST node) {
    BST current = node;
    while (current && current->RC != NULL) {
        current = current->RC;
    }
    return current;
}


/**
 * @brief Deletes a node with the given key from the BST.
 * @param root The current root of the BST.
 * @param key_data The string key to delete.
 * @return BST The new root of the BST after deletion.
 */
BST deleteNode(BST root, const char *key_data) {
    // If tree is empty, return NULL
    if (root == NULL) {
        printf("Key \"%s\" not found for deletion.\n", key_data);
        return root;
    }
    
    // Find the node to delete
    int cmp = strcmp(key_data, root->key);
    
    if (cmp < 0) {
        // Key is smaller, go to left subtree
        root->LC = deleteNode(root->LC, key_data);
    } else if (cmp > 0) {
        // Key is larger, go to right subtree
        root->RC = deleteNode(root->RC, key_data);
    } else {
        // Found the node to delete
        // Case 1: Node with no children (leaf node)
        if (root->LC == NULL && root->RC == NULL) {
            free(root->key);
            free(root);
            return NULL;
        }
        // Case 2: Node with one child
        else if (root->LC == NULL) {
            BST temp = root->RC;
            free(root->key);
            free(root);
            return temp;
        } else if (root->RC == NULL) {
            BST temp = root->LC;
            free(root->key);
            free(root);
            return temp;
        }
        // Case 3: Node with two children
        else {
            // Find the in-order successor (minimum node in right subtree)
            BST successor = findMin(root->RC);
            
            // Create a copy of the successor's key
            char *successor_key = (char *)malloc(strlen(successor->key) + 1);
            strcpy(successor_key, successor->key);
            
            // Delete the successor node (which has at most one right child)
            root->RC = deleteNode(root->RC, successor_key);
            
            // Replace current node's key with successor's key
            free(root->key);
            root->key = successor_key;
            
            return root;
        }
    }
    
    return root;
}

int main() {
    // 1. Create and initialize the tree
    BST myTree = NULL;

    printf("--- Building BST for Deletion Test ---\n");
    // Keys: Apple, Banana, Grape, Kiwi, Mango(ROOT), Orange, Pineapple
    insert(&myTree, "Mango");      // Root
    insert(&myTree, "Apple");      // Left of Mango
    insert(&myTree, "Pineapple");  // Right of Mango
    insert(&myTree, "Banana");     // Right of Apple
    insert(&myTree, "Grape");      // Left of Pineapple
    insert(&myTree, "Orange");     // Right of Grape
    insert(&myTree, "Kiwi");       // Left of Orange

    printf("\nInitial In-Order Traversal:\n   ");
    inorderTraversal(myTree);
    printf("\n");

    // --- Deletion Tests ---

    printf("\n--- Test 1: Delete Leaf Node (Kiwi) ---\n");
    // Kiwi is a leaf node (0 children)
    myTree = deleteNode(myTree, "Kiwi");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 2: Delete Node with 1 Child (Apple) ---\n");
    // Apple has 1 child (Banana)
    myTree = deleteNode(myTree, "Apple");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 3: Delete Node with 2 Children (Mango - the Root) ---\n");
    // Mango is replaced by its successor (Orange)
    myTree = deleteNode(myTree, "Mango");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 4: Delete Non-Existent Key (Zebra) ---\n");
    myTree = deleteNode(myTree, "Zebra");
    printf("No change expected: ");
    inorderTraversal(myTree);
    printf("\n");

    // 2. Clean up memory
    destroyTree(myTree);
    printf("\nTree destroyed and memory freed.\n");

    return 0;
}