/**
*	Entité joueur
**/

#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include "balle/balle.h"
#include "joueur/barre.h"
#include "briques/bonus.h"
#ifndef CAR_MAX
#define CAR_MAX 100
#endif

typedef struct Joueur{
	char nom [CAR_MAX];
	char prenom [CAR_MAX];
	int vie;
	Barre * barre;
	Bonus * bonus;
	int nb_coups_barre;
	int nb_coups_briques;
}Joueur;

Joueur initJoueur(char * nom, char * prenom, int vie, Barre * barre);
Barre * getBarre(Joueur * joueur);
void setBarre(Joueur * joueur, Barre * b);
void handleBarreIAJ2(Balle * balle_j1, Balle * balle_j2, Joueur * j1, Joueur * j2, float ordonneRepereMax);
void addBonusJoueur(Joueur * joueur, int compteur_frame, int nom_bonus, float value);
void updateBonusJoueur(Joueur * joueur, float size_x_barre_default,  float size_y_barre_default, float x_vitesse_barre_default);
void detruireBonusJoueur(Joueur * joueur);

#endif