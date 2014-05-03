#include "joueur/joueur.h"
#include <string.h>
#include <stdlib.h>

Joueur initJoueur(char * nom, char * prenom, int vie, Barre * barre){
	Joueur j;
	strncpy(j.nom,nom,CAR_MAX);
	strncpy(j.prenom,prenom,CAR_MAX);
	j.vie = vie;
	j.barre = barre;

	return j;
}

Barre * getBarre(Joueur * joueur){
	if(joueur != NULL)
		return joueur->barre;
	return NULL;
}



void setBarre(Joueur * joueur, Barre * b){
	if(joueur != NULL)
		joueur->barre = b;
}

void handleBarreIAJ2( Balle * balle_j1, Balle * balle_j2, Joueur * j1, Joueur *j2, float ordonneRepereMax){
	// en priorité sur balle j1
	if(balle_j1->yPos > balle_j2->yPos){
		if(balle_j1->xPos > (j2->barre->xPos+(j2->barre->xSize/2))){
			deplacerBarreX(j2->barre,1,ordonneRepereMax);
		}
		else if(balle_j1->xPos < (j2->barre->xPos-(j2->barre->xSize/2))){
			deplacerBarreX(j2->barre,-1,ordonneRepereMax);
		}
	}
	else{
		if(balle_j2->xPos > (j2->barre->xPos+(j2->barre->xSize/2))){
			deplacerBarreX(j2->barre,1,ordonneRepereMax);
		}
		else if(balle_j2->xPos < (j2->barre->xPos-(j2->barre->xSize/2))){
			deplacerBarreX(j2->barre,-1,ordonneRepereMax);
		}
	}
}