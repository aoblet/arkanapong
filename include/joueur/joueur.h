/**
*	Entité joueur
**/

#ifndef __JOUEUR_H__
#define

#include "balle/balle.h"
#include "joueur/barre.h"

typedef struct {
	char * nom;
	char * prenom;
	int vie;
	Barre * barre;
	Balle * balle;
}Joueur;

Joueur initJoueur(char * nom, char * prenom, int vie, Barre * barre, Balle * balle);
Barre * getBarre(Joueur * joueur);
Balle * getBalle(Joueur * joueur);



#endif