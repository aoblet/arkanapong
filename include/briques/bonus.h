#ifndef __BONUS_H__
#define __BONUS_H__
#define BONUS_REDUCTION_BARRE 1
#define BONUS_AGRANDISSEMENT_BARRE 2
#define BONUS_INVERSION_VITESSE_BARRE 3
#define BONUS_VITESSE_BALLE 4
#define BONUS_VITESSE_BARRE 5

typedef struct bonus{
	int compteur_frame;
	int nom_bonus;
	float value;
	struct bonus * next;
}Bonus;

void detruireBonus(Bonus ** bonus);
Bonus * createBonus(int compteur_frame, int nom_bonus, float value);

#endif
