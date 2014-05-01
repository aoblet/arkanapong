#include "joueur/joueur.h"
#include <string.h>
#include <stdlib.h>

Joueur initJoueur(char * nom, char * prenom, int vie, Barre * barre, Balle * balle){
	Joueur j;
	strncpy(j.nom,nom,CAR_MAX);
	strncpy(j.prenom,prenom,CAR_MAX);
	j.vie = vie;
	j.barre = barre;
	j.balle = balle;

	return j;
}

Barre * getBarre(Joueur * joueur){
	if(joueur != NULL)
		return joueur->barre;
	return NULL;
}

Balle * getBalle(Joueur * joueur){
	if(joueur != NULL)
		return joueur->balle;
	return NULL;
}

void setBalle(Joueur * joueur, Balle * b){
	if(joueur!=NULL)
		joueur->balle = b;
}

void setBarre(Joueur * joueur, Barre * b){
	if(joueur != NULL)
		joueur->barre = b;
}

void handleBarreIAJ2( Joueur *j1, Joueur * j2, float ordonneRepereMax){
	// en priorité sur balle j1
	if(j1->balle->yPos > j2->balle->yPos){
		if(j1->balle->xPos > j2->barre->xPos+j2->barre->xVitesse){
			deplacerBarreX(j2->barre,1,ordonneRepereMax);
		}
		else{
			deplacerBarreX(j2->barre,-1,ordonneRepereMax);
		}
	}
	else{
		if(j2->balle->xPos > j2->barre->xPos+j2->barre->xVitesse){
			deplacerBarreX(j2->barre,1,ordonneRepereMax);
		}
		else{
			deplacerBarreX(j2->barre,-1,ordonneRepereMax);
		}
	}
}