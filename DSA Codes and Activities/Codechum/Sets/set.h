#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

typedef char String[30];
typedef struct Node {
    String spell;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
}Set;

// Create a new empty set
Set* createSet();

// Add a spell to the set (no duplicates)
bool addSpell(Set* set, String spell);

// Remove a spell from the set
bool removeSpell(Set** set, String spell);

// Check if a spell exists in the set
bool containsSpell(Set* set, String spell);

// Print all spells in the set
void printSet(Set* set);

// Free all memory associated with the set
void destroySet(Set* set);

Set* unionSets(Set* set1, Set* set2);
Set* intersectSets(Set* set1, Set* set2);

#endif // SET_H