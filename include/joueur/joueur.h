/**
*	Entité joueur
**/

#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include "balle/balle.h"
#include "joueur/barre.h"
#define	  CAR_MAX 50

typedef struct Joueur{
	char nom [CAR_MAX];
	char prenom [CAR_MAX];
	int vie;
	Barre * barre;
	Balle * balle;
}Joueur;

Joueur initJoueur(char * nom, char * prenom, int vie, Barre * barre, Balle * balle);
Barre * getBarre(Joueur * joueur);
Balle * getBalle(Joueur * joueur);
void setBalle(Joueur * joueur, Balle * b);
void setBarre(Joueur * joueur, Barre * b);
void handleBarreIAJ2(Joueur *j1, Joueur * j2, float ordonneRepereMax);

#endif