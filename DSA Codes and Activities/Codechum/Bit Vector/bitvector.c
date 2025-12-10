#include <stdio.h>
#include <stdbool.h>
#include "bitvector.h"

// Set the answer to 1 or 0 for a given question index
void setAnswer(BitVect* profile, int index, int value) {
    // Validate index (0-9 for 10 questions)
    if (index < 0 || index > 9) {
        return;
    }
    
    // Set the value in the array
    profile->answers[index] = (value == 1) ? 1 : 0;
}

// Retrieve the answer for a given question index
int getAnswer(BitVect profile, int index) {
    // Validate index
    if (index < 0 || index > 9) {
        return 0;
    }
    
    return profile.answers[index];
}

// Count how many answers are 1
int countYesAnswers(BitVect profile) {
    int count = 0;
    
    // Count all '1' values in the array
    for (int i = 0; i < 10; i++) {
        if (profile.answers[i] == 1) {
            count++;
        }
    }
    
    return count;
}

// Print all answers as a binary string
void printAnswers(BitVect profile) {
    // Print from index 9 to 0 for left-to-right reading
    // (assuming index 0 is question 1, so we want to show most recent/question 10 first)
    for (int i = 9; i >= 0; i--) {
        printf("%d", profile.answers[i]);
    }
    printf("\n");
}

// Compares how many matching answers the two respondents have
int compareProfiles(BitVect a, BitVect b) {
    int matching = 0;
    
    // Count positions where both profiles have the same answer
    for (int i = 0; i < 10; i++) {
        if (a.answers[i] == b.answers[i]) {
            matching++;
        }
    }
    
    return matching;
}

// Returns a new set containing all of the yes answers from both profiles
BitVect unionProfiles(BitVect a, BitVect b) {
    BitVect result = {0};
    
    // For each position, set to 1 if either a or b has 1
    for (int i = 0; i < 10; i++) {
        if (a.answers[i] == 1 || b.answers[i] == 1) {
            result.answers[i] = 1;
        } else {
            result.answers[i] = 0;
        }
    }
    
    return result;
}

// Returns a new set containing all of the common yes answers from both profiles
BitVect intersectProfiles(BitVect a, BitVect b) {
    BitVect result = {0};
    
    // For each position, set to 1 only if both a and b have 1
    for (int i = 0; i < 10; i++) {
        if (a.answers[i] == 1 && b.answers[i] == 1) {
            result.answers[i] = 1;
        } else {
            result.answers[i] = 0;
        }
    }
    
    return result;
}

// Returns a new set containing the yes answers from a and the common answers they have with b
BitVect differenceProfiles(BitVect a, BitVect b) {
    BitVect result = {0};
    
    // Based on sample output, this seems to be: yes in a but no in b
    // In other words: a - b (set difference)
    for (int i = 0; i < 10; i++) {
        if (a.answers[i] == 1 && b.answers[i] == 0) {
            result.answers[i] = 1;
        } else {
            result.answers[i] = 0;
        }
    }
    
    return result;
}