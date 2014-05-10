#include "joueur/joueur.h"
#include <string.h>
#include <stdlib.h>

Joueur initJoueur(char * nom, char * prenom, int vie, Barre * barre){
	Joueur j;
	strncpy(j.nom,nom,CAR_MAX);
	strncpy(j.prenom,prenom,CAR_MAX);
	j.vie = vie;
	j.barre = barre;
	j.bonus = NULL;
	j.nb_coups = 0;
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
		if(balle_j1->xPos > (j2->barre->xPos+(j2->barre->xSize/4))){
			deplacerBarreX(j2->barre,1,ordonneRepereMax);
		}
		else if(balle_j1->xPos < (j2->barre->xPos-(j2->barre->xSize/4))){
			deplacerBarreX(j2->barre,-1,ordonneRepereMax);
		}
	}
	else{
		if(balle_j2->xPos > (j2->barre->xPos+(j2->barre->xSize/4))){
			deplacerBarreX(j2->barre,1,ordonneRepereMax);
		}
		else if(balle_j2->xPos < (j2->barre->xPos-(j2->barre->xSize/4))){
			deplacerBarreX(j2->barre,-1,ordonneRepereMax);
		}
	}
}

void addBonusJoueur(Joueur * joueur, int compteur_frame, int nom_bonus, float value){
	if(joueur != NULL){
		Bonus * bonus_temp = createBonus(compteur_frame, nom_bonus, value);
		bonus_temp->next = joueur->bonus;
		joueur->bonus = bonus_temp;
	}
}

void updateBonusJoueur(Joueur * joueur, float size_x_barre_default,  float size_y_barre_default, float x_vitesse_barre_default){
	if(joueur != NULL){
		joueur->barre->xSize = size_x_barre_default;
		joueur->barre->ySize = size_y_barre_default;
		joueur->barre->xVitesse = x_vitesse_barre_default;

		Bonus * bonus_temp = joueur->bonus;
		Bonus * bonus_temp_prec = NULL;
		while(bonus_temp != NULL){
			if( (bonus_temp->compteur_frame-=1)<0 ){
				if(bonus_temp_prec != NULL){
					bonus_temp_prec->next = bonus_temp->next;
					free(bonus_temp);
					bonus_temp = bonus_temp_prec->next;
				}
				else{
					joueur->bonus =  bonus_temp->next;
					free(bonus_temp);
					bonus_temp = joueur->bonus;
				}
			}
			else{
				if(bonus_temp->nom_bonus == BONUS_AGRANDISSEMENT_BARRE || bonus_temp->nom_bonus == BONUS_REDUCTION_BARRE)
					joueur->barre->xSize *= bonus_temp->value;
				else if(bonus_temp->nom_bonus == BONUS_INVERSION_VITESSE_BARRE)
					joueur->barre->xVitesse *= -1;
				else if(bonus_temp->nom_bonus == BONUS_VITESSE_BARRE)
					joueur->barre->xVitesse *= bonus_temp->value;

				bonus_temp_prec = bonus_temp;
				bonus_temp = bonus_temp->next;
			}
		}
	}
}
void detruireBonusJoueur(Joueur * joueur){
	if(joueur != NULL){
		Bonus * bonus_temp_next = joueur->bonus;
		Bonus * bonus_temp = NULL;
		while(bonus_temp_next != NULL){
			bonus_temp = bonus_temp_next;
			bonus_temp_next = bonus_temp->next;
			free(bonus_temp);
		}
		joueur->bonus = NULL;
	}
}
