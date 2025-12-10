#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

int main() {
    String spell;
    Set* fireSpells = createSet();
    Set* waterSpells = createSet();

	strncpy(spell,"Flame Burst",12);
	spell[11]='\0';
	addSpell(fireSpells, spell);

	strncpy(spell,"Inferno",8);
	spell[7]='\0';
	addSpell(fireSpells, spell);

	strncpy(spell,"Aqua Jet",9);
	spell[8]='\0';
	addSpell(waterSpells, spell);

	strncpy(spell,"Inferno",8);
	spell[7]='\0';
	addSpell(waterSpells, spell);

	Set* commonSpells = intersectSets(fireSpells, waterSpells);
	Set* allSpells = unionSets(fireSpells, waterSpells);

	printf("Common Spells:\n");
	printSet(commonSpells);

	printf("\nAll Spells:\n");
	printSet(allSpells);

	strncpy(spell,"Aqua Jet",9);
	spell[8]='\0';
	removeSpell(&allSpells,spell);

	printf("\nAll Spells:\n");
	printSet(allSpells);

	destroySet(fireSpells);
	destroySet(waterSpells);
	destroySet(commonSpells);
	destroySet(allSpells);

return 0;
}