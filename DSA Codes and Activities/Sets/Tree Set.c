#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// BST Node for ordered set
typedef struct TreeNode {
    char *key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Tree Set Structure
typedef struct {
    TreeNode *root;
    int size;
} TreeSet;

TreeSet* create_treeset() {
    TreeSet *set = malloc(sizeof(TreeSet));
    set->root = NULL;
    set->size = 0;
    return set;
}

// Insert into BST (automatically ordered)
TreeNode* treeset_insert(TreeNode *node, const char *key) {
    if (node == NULL) {
        TreeNode *new_node = malloc(sizeof(TreeNode));
        new_node->key = strdup(key);
        new_node->left = new_node->right = NULL;
        return new_node;
    }
    
    int cmp = strcmp(key, node->key);
    if (cmp < 0) {
        node->left = treeset_insert(node->left, key);
    } else if (cmp > 0) {
        node->right = treeset_insert(node->right, key);
    }
    // If equal, do nothing (set property)
    
    return node;
}

void treeset_add(TreeSet *set, const char *key) {
    set->root = treeset_insert(set->root, key);
    set->size++;
}

// Search in BST
int treeset_contains(TreeNode *node, const char *key) {
    if (node == NULL) return 0;
    
    int cmp = strcmp(key, node->key);
    if (cmp == 0) return 1;
    if (cmp < 0) return treeset_contains(node->left, key);
    return treeset_contains(node->right, key);
}