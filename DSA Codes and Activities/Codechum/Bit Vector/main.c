#include <stdio.h>
#include "bitvector.h"

int main() {
    BitVect inie = {0};
    BitVect jobo = {0};

    setAnswer(&inie, 0, 1); // Q1: Yes
    setAnswer(&inie, 1, 1); // Q2: Yes
    setAnswer(&inie, 3, 1); // Q4: Yes
    setAnswer(&inie, 5, 1); // Q6: Yes
    setAnswer(&inie, 8, 1); // Q9: Yes
    setAnswer(&jobo, 0, 1); // Q1: Yes
    setAnswer(&jobo, 2, 1); // Q3: Yes
    setAnswer(&jobo, 4, 1); // Q5: Yes
    setAnswer(&jobo, 5, 1); // Q6: Yes
    setAnswer(&jobo, 6, 1); // Q7: Yes
    setAnswer(&jobo, 7, 1); // Q8: Yes

    printf("Inie's answers: ");
    printAnswers(inie);

    printf("Jobo's answers: ");
    printAnswers(jobo);

    printf("\nMatching answers: %d\n", compareProfiles(inie, jobo));

    printf("Jobo answered %s to question %d\n",(getAnswer(jobo,0))?"yes":"no",1);
    printf("Jobo answered %s to question %d\n",(getAnswer(jobo,1))?"yes":"no",2);
    printf("Inie said yes to %d questions\n\n", countYesAnswers(inie));

	BitVect unionSet = unionProfiles(inie, jobo);
	BitVect intersectSet = intersectProfiles(inie, jobo);
	BitVect diffSet = differenceProfiles(inie, jobo);

	printf("Union:        "); printAnswers(unionSet);
	printf("Intersection: "); printAnswers(intersectSet);
	printf("Difference:   "); printAnswers(diffSet);

	return 0;
}