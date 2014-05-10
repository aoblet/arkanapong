#include "briques/bonus.h"
#include <stdlib.h>

void detruireBonus(Bonus ** bonus){
	if(bonus != NULL){
		free(*bonus);
		*bonus = NULL;
	}
}

Bonus * createBonus(int compteur_frame, int nom_bonus, float value){
	Bonus * bonus = (Bonus*)malloc(sizeof(Bonus));
	bonus->compteur_frame = compteur_frame;
	bonus->nom_bonus = nom_bonus;
	bonus->value = value;
	bonus->next = NULL;
	return bonus;
}
