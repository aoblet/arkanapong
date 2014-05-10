#include <math.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "joueur/joueur.h"
#include "joueur/barre.h"
#include "briques/bonus.h"
#include "briques/brique.h"

Brique * initBrique(float xPos, float yPos, float xSize, float ySize, Balle ** balles){
	Brique * b = (Brique*)malloc(sizeof(Brique));
	b->xPos = xPos;
	b->yPos = yPos;
	b->ySize = ySize;
	b->xSize = xSize;
	b->balles = balles;
	b->vie = 1;
	b->texture = 0;
	b->type_brique = 0;
	return b;
}

void detruireBrique(Brique ** brique){
	if(brique !=NULL && *brique!= NULL){
		free(*brique);
		*brique = NULL;
	}
}

void detruireBriques(Brique ** briques, int nbBriques){
	int i;
	for(i=0 ; i<nbBriques; i++)
		detruireBrique(&(briques[i]));
}

void setPositionBrique(Brique ** brique, float xPos, float yPos){
	if(brique != NULL && *brique != NULL){
		(*brique)->xPos = xPos;
		(*brique)->yPos = yPos;
	}
}

void setTextureBrique(Brique ** brique, GLuint id_texture){
	(*brique)->texture = id_texture;
}

void dessinBrique(Brique * brique){
	if(brique != NULL){

		glColor3ub(255,255,255);
		float xGauche 	= brique->xPos-(brique->xSize/2);
		float xDroit 	= brique->xPos+(brique->xSize/2);
		float yBas		= brique->yPos-(brique->ySize/2);
		float yHaut		= brique->yPos+(brique->ySize/2);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, brique->texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex2f(xGauche,yBas);

		glTexCoord2f(1,1);
		glVertex2f(xDroit,yBas);

		glTexCoord2f(1,0);
		glVertex2f(xDroit,yHaut);

		glTexCoord2f(0,0);
		glVertex2f(xGauche,yHaut);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}
}

// 0: classique, 1: indestructible, 2:agrandissement_barre, 3:reduction_barre, 4:vitesse_plus_balle, 5:vitesse_moins_balle
void configureBrique(Brique ** brique, int type,Textures textures){
	if(brique != NULL){
		(*brique)->type_brique = type;
		if(type == BRIQUE_CLASSIQUE){ 
			setTextureBrique(brique,textures.identifiants[TEXTURE_CLASSIQUE_1]);
		}
		else if(type == BRIQUE_INDESTRUCTIBLE){
			setTextureBrique(brique,textures.identifiants[TEXTURE_INDESTRUCTIBLE_1]);
		}
		else if(type == BRIQUE_AGRANDISSEMENT_BARRE){
			(*brique)->vie = 3;
			setTextureBrique(brique,textures.identifiants[TEXTURE_AGRANDISSEMENT_BARRE_3]);
		}
		else if(type == BRIQUE_REDUCTION_BARRE){
			setTextureBrique(brique,textures.identifiants[TEXTURE_REDUCTION_BARRE_1]);
		}
		else if(type == BRIQUE_VITESSE_PLUS_BALLE){
			(*brique)->vie = 2;
			setTextureBrique(brique,textures.identifiants[TEXTURE_VITESSE_PLUS_BALLE_2]);
		}
		else if(type == BRIQUE_VITESSE_MOINS_BALLE){
			(*brique)->vie = 2;
			setTextureBrique(brique,textures.identifiants[TEXTURE_VITESSE_MOINS_BALLE_2]);
		}
		else if(type == BRIQUE_INVERSION_VITESSE_BARRE){
			(*brique)->vie = 1;
			setTextureBrique(brique,textures.identifiants[TEXTURE_INVERSION_VITESSE_BARRE_1]);
		}
		else if(type == BRIQUE_VITESSE_BARRE){
			(*brique)->vie = 3;
			setTextureBrique(brique,textures.identifiants[TEXTURE_VITESSE_BARRE_3]);
		}
	}
}

void handleCollisionBrique(Brique ** brique, Balle ** balle,Textures textures){
	//base de frame rate 1000/60
	if(brique != NULL && *brique!=NULL){
		if((*brique)->type_brique == BRIQUE_CLASSIQUE){
			if( ((*brique)->vie-=1) <= 0)
				detruireBrique(brique);
		}
		else if((*brique)->type_brique == BRIQUE_INDESTRUCTIBLE){
			// rien à faire:indestructible
		}
		else if((*brique)->type_brique == BRIQUE_AGRANDISSEMENT_BARRE){
			(*brique)->vie -=1;

			if( (*brique)->vie == 2){
				setTextureBrique(brique,textures.identifiants[TEXTURE_AGRANDISSEMENT_BARRE_2]);
			}
			else if( (*brique)->vie == 1){
				setTextureBrique(brique,textures.identifiants[TEXTURE_AGRANDISSEMENT_BARRE_1]);
			}
			else{
				//success
				addBonusJoueur((*balle)->joueur,60*5,BONUS_AGRANDISSEMENT_BARRE,2); // 5 secondes
				detruireBrique(brique);
			}
		}
		else if((*brique)->type_brique == BRIQUE_REDUCTION_BARRE){
			if( ((*brique)->vie-=1) <= 0){
				addBonusJoueur((*balle)->joueur,60*7,BONUS_REDUCTION_BARRE,0.5); // 7secondes
				detruireBrique(brique);
			}
		}
		else if((*brique)->type_brique == BRIQUE_VITESSE_PLUS_BALLE){
			if( ((*brique)->vie-=1) == 1){
				setTextureBrique(brique,textures.identifiants[TEXTURE_VITESSE_PLUS_BALLE_1]);
			}
			else{
				addBonusBalle((*balle),60*5,BONUS_VITESSE_BALLE,1.3);
				detruireBrique(brique);
			}
		}
		else if((*brique)->type_brique == BRIQUE_VITESSE_MOINS_BALLE){
			if( ((*brique)->vie-=1) == 1){
				setTextureBrique(brique,textures.identifiants[TEXTURE_VITESSE_MOINS_BALLE_1]);
			}
			else{
				addBonusBalle((*balle),60*5,BONUS_VITESSE_BALLE,0.5);
				detruireBrique(brique);
			}
		}
		else if((*brique)->type_brique == BRIQUE_INVERSION_VITESSE_BARRE){
			if( ((*brique)->vie-=1) <= 0){
				addBonusJoueur((*balle)->joueur,60*3,BONUS_INVERSION_VITESSE_BARRE,0); // 3secondes
				detruireBrique(brique);
			}
		}
		else if((*brique)->type_brique == BRIQUE_VITESSE_BARRE){
			(*brique)->vie -=1;
			if( (*brique)->vie == 2){
				setTextureBrique(brique,textures.identifiants[TEXTURE_VITESSE_BARRE_2]);
			}
			else if( (*brique)->vie == 1){
				setTextureBrique(brique,textures.identifiants[TEXTURE_VITESSE_BARRE_1]);
			}
			else{
				//success
				addBonusJoueur((*balle)->joueur,60*5,BONUS_VITESSE_BARRE,2); // 5 secondes
				detruireBrique(brique);
			}
		}
	}
}

void handleBriqueBalles(Brique ** brique, int nbBalles, Textures textures){

	int i;
	for(i=0;i<nbBalles;i++){
		if(brique != NULL && *brique != NULL){
			Balle * balle = (*brique)->balles[i];
				  //extremites balles
			float extremiteBalleDroit 	= balle->xPos + balle->rayon, extremiteBalleGauche = balle->xPos - balle->rayon,
				  extremiteBalleHaut 	= balle->yPos + balle->rayon, extremiteBalleBas    = balle->yPos - balle->rayon,
				  //extremites briques
				  extremiteBriqueHaut 	= (*brique)->yPos+(*brique)->ySize/2, extremiteBriqueBas 	= (*brique)->yPos-(*brique)->ySize/2,
				  extremiteBriqueDroit	= (*brique)->xPos+(*brique)->xSize/2, extremiteBriqueGauche	= (*brique)->xPos-(*brique)->xSize/2;

			// tappe dans la brique
			if(	extremiteBalleGauche < extremiteBriqueDroit && extremiteBalleDroit > extremiteBriqueGauche && extremiteBalleHaut > extremiteBriqueBas && extremiteBalleBas<extremiteBriqueHaut){
				
				float 	coeff_directeur_balle_brique = fabs((balle->yPos - (*brique)->yPos)/(balle->xPos - (*brique)->xPos)),
						coeff_directeur_diagonale_brique = (*brique)->ySize/(*brique)->xSize;

				//haut ou bas
				if(coeff_directeur_balle_brique>coeff_directeur_diagonale_brique){
					if(balle->angleVitesse <= M_PI && balle->angleVitesse >=0)
						setPositionBalle(balle, balle->xPos, extremiteBriqueBas-balle->rayon);
					else
						setPositionBalle(balle, balle->xPos, extremiteBriqueHaut+balle->rayon);

					setAngleVitesseBalle(balle,-balle->angleVitesse);
				}
				else{
					//les cotes
					if((balle->angleVitesse < M_PI/2 && balle->angleVitesse > 0) || (balle->angleVitesse < 2.0*M_PI && balle->angleVitesse > 3*M_PI/2)) // gauche
						setPositionBalle(balle, extremiteBriqueGauche-balle->rayon,balle->yPos);
					else
						setPositionBalle(balle, extremiteBriqueDroit+balle->rayon,balle->yPos);
					
					setAngleVitesseBalle(balle,M_PI-balle->angleVitesse);
				}

				balle->joueur->nb_coups_briques++;
				handleCollisionBrique(brique,&((*brique)->balles[i]),textures);
			}
		}
	}
}



