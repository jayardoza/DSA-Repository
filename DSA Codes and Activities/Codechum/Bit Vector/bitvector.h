#ifndef BITVECTOR_H
#define BITVECTOR_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char answers[10];
} BitVect;

void setAnswer(BitVect* profile, int index, int value);
int getAnswer(BitVect profile, int index);
int countYesAnswers(BitVect profile);
void printAnswers(BitVect profile);
int compareProfiles(BitVect a, BitVect b);

BitVect unionProfiles(BitVect a, BitVect b);
BitVect intersectProfiles(BitVect a, BitVect b);
BitVect differenceProfiles(BitVect a, BitVect b);

#endif // BITVECTOR_H