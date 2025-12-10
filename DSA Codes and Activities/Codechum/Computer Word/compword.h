#ifndef COMPWORD_H
#define COMPWORD_H

#include <stdio.h>
#include <stdbool.h>

typedef short int CompWord;

void setAnswer(CompWord* profile, int index, int value);
int getAnswer(CompWord profile, int index);
int countYesAnswers(CompWord profile);
void printAnswers(CompWord profile);
int compareProfiles(CompWord a, CompWord b);

CompWord unionProfiles(CompWord a, CompWord b);
CompWord intersectProfiles(CompWord a, CompWord b);
CompWord differenceProfiles(CompWord a, CompWord b);


#endif // COMPWORD_H