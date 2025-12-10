#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

// Create a new empty set
Set* createSet() {
    Set* newSet = (Set*)malloc(sizeof(Set));
    if (newSet == NULL) {
        return NULL;
    }
    newSet->head = NULL;
    newSet->size = 0;
    return newSet;
}

// Add a spell to the set (no duplicates)
bool addSpell(Set* set, String spell) {
    // Check if spell already exists
    if (containsSpell(set, spell)) {
        return false;
    }
    
    // Create new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return false;
    }
    
    // Copy spell string to node
    strcpy(newNode->spell, spell);
    newNode->next = NULL;
    
    // Add to beginning of list for O(1) insertion
    newNode->next = set->head;
    set->head = newNode;
    set->size++;
    
    return true;
}

// Remove a spell from the set
bool removeSpell(Set** set, String spell) {
    if (*set == NULL || (*set)->head == NULL) {
        return false;
    }
    
    Node* current = (*set)->head;
    Node* prev = NULL;
    
    // Check if head node contains the spell
    if (strcmp(current->spell, spell) == 0) {
        (*set)->head = current->next;
        free(current);
        (*set)->size--;
        return true;
    }
    
    // Search for the node to remove
    while (current != NULL && strcmp(current->spell, spell) != 0) {
        prev = current;
        current = current->next;
    }
    
    // If spell not found
    if (current == NULL) {
        return false;
    }
    
    // Remove the node
    prev->next = current->next;
    free(current);
    (*set)->size--;
    
    return true;
}

// Check if a spell exists in the set
bool containsSpell(Set* set, String spell) {
    if (set == NULL) {
        return false;
    }
    
    Node* current = set->head;
    while (current != NULL) {
        if (strcmp(current->spell, spell) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Print all spells in the set
void printSet(Set* set) {
    if (set == NULL || set->head == NULL) {
        return;
    }
    
    Node* current = set->head;
    int count = 1;
    
    while (current != NULL) {
        printf("  %d. %s\n", count, current->spell);
        current = current->next;
        count++;
    }
}

// Free all memory associated with the set
void destroySet(Set* set) {
    if (set == NULL) {
        return;
    }
    
    Node* current = set->head;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    free(set);
}

// Returns a new set containing all spells from both sets
Set* unionSets(Set* set1, Set* set2) {
    Set* result = createSet();
    if (result == NULL) {
        return NULL;
    }
    
    // Add all spells from set1
    Node* current = set1->head;
    while (current != NULL) {
        addSpell(result, current->spell);
        current = current->next;
    }
    
    // Add all spells from set2 (addSpell handles duplicates)
    current = set2->head;
    while (current != NULL) {
        addSpell(result, current->spell);
        current = current->next;
    }
    
    return result;
}

// Returns a new set containing only common spells
Set* intersectSets(Set* set1, Set* set2) {
    Set* result = createSet();
    if (result == NULL) {
        return NULL;
    }
    
    Node* current = set1->head;
    while (current != NULL) {
        // If spell exists in both sets, add to result
        if (containsSpell(set2, current->spell)) {
            addSpell(result, current->spell);
        }
        current = current->next;
    }
    
    return result;
}