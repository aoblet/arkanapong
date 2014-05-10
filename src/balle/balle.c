#include "balle/balle.h"
#include <GL/gl.h>
#include <math.h>
#include <stdlib.h> //NULL
#include <stdio.h> //NULL
#include "utils/dessin_utils.h"
#include "joueur/joueur.h"
#include "briques/bonus.h"


Balle initBalle(float xPos, float yPos,float normeVitesse,float angleVitesse, float rayon,int rouge, int vert, int bleu, struct Joueur * joueur){
	Balle balle;
	balle.xPos = xPos;
	balle.yPos = yPos;

	balle.normeVitesse = normeVitesse;
	balle.angleVitesse = angleVitesse;

	balle.rayon = rayon;
	balle.rouge = rouge; balle.vert = vert; balle.bleu=bleu;
	balle.texture=0;
	balle.joueur = joueur;
	balle.bonus = NULL;
	return balle;
}

void setPositionBalle(Balle * b, float xPos, float yPos){
	b->xPos = xPos;
	b->yPos = yPos;
}

void setAngleVitesseBalle(Balle * balle, float angleVitesse){
	balle->angleVitesse = fmod(angleVitesse,2.0*M_PI);
	if(balle->angleVitesse<0)
		balle->angleVitesse = 2.0*M_PI + balle->angleVitesse; //toujours positif
}
void setNormeVitesseBalle(Balle * balle, float normeVitesse){
	balle->normeVitesse = normeVitesse;
}

int handleBalleBorder(Balle *b, float xMax, float yMax){
	int touch = 0;

	if(b!=NULL){
		if(b->xPos+b->rayon >= xMax){
	 		setAngleVitesseBalle(b,M_PI - b->angleVitesse);
	 		setPositionBalle(b,xMax-b->rayon,b->yPos);
	 		touch = 1;
	 	}
	 	else if( b->xPos-b->rayon <= xMax*-1){
	 		setAngleVitesseBalle(b,M_PI - b->angleVitesse);
	 		setPositionBalle(b,-xMax + b->rayon,b->yPos);
	 		touch = 1;
	 	}

	 	if( (b->yPos+b->rayon) >= yMax){
	 		setAngleVitesseBalle(b,- b->angleVitesse);
	 		setPositionBalle(b,b->xPos,yMax-b->rayon);
	 		//perdu
	 		touch = -2; // perte j2
	 	}
	 	else if((b->yPos-b->rayon) <= yMax*-1){
	 		setAngleVitesseBalle(b, 2*M_PI - b->angleVitesse);
	 		setPositionBalle(b,b->xPos,-yMax + b->rayon);
	 		touch = -1;	//perte j1
	 	}		
	}
 	return touch;
}



void setAcceleration(Balle * b, float vitesse){
	if(b!=NULL){
		b->normeVitesse*=vitesse;
	}
}

int handleBalleBarres(Balle * b, struct Joueur * joueur1, struct Joueur * joueur2){
	if(b!=NULL){
		float 	extremiteBalleDroit 	= b->xPos + b->rayon,
				extremiteBalleGauche 	= b->xPos - b->rayon,
				extremiteBalleHaut 		= b->yPos + b->rayon,
				extremiteBalleBas 		= b->yPos - b->rayon;

		//barre joueur 1
		if(joueur1 != NULL && joueur1->barre != NULL){
			float extremiteBarreHaut_j1 	= joueur1->barre->yPos + (joueur1->barre->ySize/2);
			float extremiteBarreDroit_j1 	= joueur1->barre->xPos + (joueur1->barre->xSize/2);
			float extremiteBarreGauche_j1 	= joueur1->barre->xPos - (joueur1->barre->xSize/2);

			// si rentre dans la barre
			if(extremiteBalleBas < extremiteBarreHaut_j1 && extremiteBalleGauche <= extremiteBarreDroit_j1 && extremiteBalleDroit >= extremiteBarreGauche_j1 ){
				b->joueur = joueur1;

				float angle_after_rebond;
				if(b->xPos >= joueur1->barre->xPos)
					 angle_after_rebond = M_PI/2-((b->xPos - joueur1->barre->xPos)*(M_PI/3)/(joueur1->barre->xSize/2));
				else
					 angle_after_rebond = M_PI -(( M_PI/2-(joueur1->barre->xPos-b->xPos)*(M_PI/3)/(joueur1->barre->xSize/2)));

				setPositionBalle(b,b->xPos,extremiteBarreHaut_j1+b->rayon);
				setAngleVitesseBalle(b,angle_after_rebond);
				joueur1->nb_coups ++;
				return 1;
			}
		}
		
		//barre joueur 2
		if(joueur2 != NULL && joueur2->barre != NULL){
			float extremiteBarreBas_j2 		= joueur2->barre->yPos - (joueur2->barre->ySize/2);
			float extremiteBarreDroit_j2 	= joueur2->barre->xPos + (joueur2->barre->xSize/2);
			float extremiteBarreGauche_j2 	= joueur2->barre->xPos - (joueur2->barre->xSize/2);

			//si rentre dans la barre
			if(extremiteBalleHaut > extremiteBarreBas_j2 && extremiteBalleGauche <= extremiteBarreDroit_j2 && extremiteBalleDroit >= extremiteBarreGauche_j2 ){
				b->joueur = joueur2;

				float angle_after_rebond;
				if(b->xPos >= joueur2->barre->xPos)
					 angle_after_rebond = -(M_PI/2-((b->xPos - joueur2->barre->xPos)*(M_PI/3)/(joueur2->barre->xSize/2)));
				else
					 angle_after_rebond = -(M_PI -(( M_PI/2-(joueur2->barre->xPos-b->xPos)*(M_PI/3)/(joueur2->barre->xSize/2))));

				setPositionBalle(b,b->xPos,extremiteBarreBas_j2-b->rayon);
				setAngleVitesseBalle(b,angle_after_rebond);
				joueur2->nb_coups ++;
				return 1;
			}
		}

	}
	return 0;
}

void dessinBalle(Balle * balle, float abcisseRepereMax,float ordonneRepereMax){
	if(balle!=NULL){

		glPushMatrix();
			glTranslatef(balle->xPos,balle->yPos,0);
			glScalef(balle->rayon*2,balle->rayon*2,0);
			glColor3ub(balle->rouge,balle->vert,balle->bleu);
			dessinCercleCanonique();
		glPopMatrix();

		float xTranslate = balle->normeVitesse*cos(balle->angleVitesse);
		float yTranslate = balle->normeVitesse*sin(balle->angleVitesse);
		setPositionBalle(balle,balle->xPos + xTranslate,balle->yPos + yTranslate);
		//printf("Angle : %f\n",balle->angleVitesse * (180/M_PI) );
	}
}


void stopBalle(Balle * b){
	if(b!=NULL)
		b->normeVitesse=0;
}

void setBalleJ1ToScreen(Balle * balle, Barre * barre){
	balle->xPos =0;
	balle->yPos = barre->yPos + barre->ySize/2 +5;
}
void setBalleJ2ToScreen(Balle * balle, Barre * barre){
	balle->xPos =0;
	balle->yPos = barre->yPos - (barre->ySize/2 +5);
}

void addBonusBalle(Balle * balle, int compteur_frame, int nom_bonus, float value){
 	if(balle!=NULL){
 		if(balle->bonus != NULL){
 			free(balle->bonus);
 			balle->bonus=NULL;
 		}
 		balle->bonus = createBonus(compteur_frame,nom_bonus,value);
 	}
}
void updateBonusBalle(Balle * balle, float norme_vitesse_default){
	balle->normeVitesse = norme_vitesse_default;

	if(balle != NULL && balle->bonus != NULL){
		balle->normeVitesse *= balle->bonus->value;

		if( (balle->bonus->compteur_frame-=1) <= 0 ){
			free(balle->bonus);
			balle->bonus=NULL;
		}
	}
}
