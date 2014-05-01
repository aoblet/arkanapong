#include "balle/balle.h"
#include <GL/gl.h>
#include <math.h>
#include <stdlib.h> //NULL
#include <stdio.h> //NULL
#include "utils/dessin_utils.h"


Balle initBalle(float xPos, float yPos,float xVitesse,float yVitesse, float rayon,int rouge, int vert, int bleu){
	Balle balle;
	balle.xPos = xPos;
	balle.yPos = yPos;
	balle.xVitesse = xVitesse;
	balle.yVitesse = yVitesse;
	balle.rayon = rayon;
	balle.rouge = rouge; balle.vert = vert; balle.bleu=bleu;
	balle.texture=0;
	return balle;
}

void setPositionBalle(Balle * b, float xPos, float yPos){
	b->xPos = xPos;
	b->yPos = yPos;
}

int handleBalleBorder(Balle *b, float xMax, float yMax){
	int touch = 0;

	if(b!=NULL){
		if( (b->xPos+b->rayon) >= xMax || (b->xPos-b->rayon) <= xMax*-1){
	 		b->xVitesse *=-1;
	 		setAcceleration(b,1.2);
	 		touch = 1;
	 	}
	 	if( (b->yPos+b->rayon) >= yMax){
	 		//perdu
	 		b->yVitesse *=0;
	 		b->xVitesse *=0;
	 		touch = -2; // perte j2
	 	}
	 	else if((b->yPos-b->rayon) <= yMax*-1){
	 		b->yVitesse *=0;
	 		b->xVitesse *=0;
	 		touch = -1;	//perte j1
	 	}		
	}
 	return touch;
}

void setVecteurVitesse(Balle * b, float xVitesse,float yVitesse){
	if (b!=NULL){
		b->xVitesse = xVitesse;
		b->yVitesse = yVitesse;
	}
}
void setSymetriqueVecteurVitesse(Balle * b){
	if (b!=NULL){
		/* code */
	}
}

void setAcceleration(Balle * b, float vitesse){
	if(b!=NULL){
		b->xVitesse*=vitesse;
		b->yVitesse*=vitesse;
	}
}

int handleBalleBarres(Balle * b){
	if(b!=NULL){
		float extremiteBalleDroit 	= b->xPos + b->rayon;
		float extremiteBalleGauche 	= b->xPos - b->rayon;
		float extremiteBalleHaut 	= b->yPos + b->rayon;
		float extremiteBalleBas 	= b->yPos - b->rayon;

		//barre joueur 1
		if(b->barre_joueur_1 != NULL){
			float extremiteBarreHaut_j1 = b->barre_joueur_1->yPos + (b->barre_joueur_1->ySize/2);
			if(extremiteBalleBas <= extremiteBarreHaut_j1){
				float extremiteBarreDroit_j1 	= b->barre_joueur_1->xPos + (b->barre_joueur_1->xSize/2);
				float extremiteBarreGauche_j1 	= b->barre_joueur_1->xPos - (b->barre_joueur_1->xSize/2);

				if( (extremiteBalleGauche <= extremiteBarreDroit_j1) &&  (extremiteBalleDroit >= extremiteBarreGauche_j1) ){


					b->yVitesse *=-1;
					return 1;
				}
			}
		}
		
		//barre joueur 2
		if(b->barre_joueur_2 != NULL){
			float extremiteBarreBas_j2 = b->barre_joueur_2->yPos - (b->barre_joueur_2->ySize/2);
			if(extremiteBalleHaut >= extremiteBarreBas_j2  ){
				float extremiteBarreDroit_j2 	= b->barre_joueur_2->xPos + (b->barre_joueur_2->xSize/2);
				float extremiteBarreGauche_j2 	= b->barre_joueur_2->xPos - (b->barre_joueur_2->xSize/2);

				if( (extremiteBalleGauche <= extremiteBarreDroit_j2) &&  (extremiteBalleDroit >= extremiteBarreGauche_j2) ){
					b->yVitesse *=-1;
					return 1;
				}
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

		setPositionBalle(balle,balle->xPos + balle->xVitesse,balle->yPos + balle->yVitesse);
		handleBalleBarres(balle);
	}
}

void setBarresToBalle(Balle * b, Barre * barrej1, Barre * barrej2){
	if(b != NULL){
		b->barre_joueur_1 = barrej1; 
		b->barre_joueur_2 = barrej2; 
	}
}

void stopBalle(Balle * b){
	b->xVitesse = 0;
	b->yVitesse = 0;
}

void setBalleJ1ToScreen(Balle * balle, Barre * barre){
	balle->xPos =0;
	balle->yPos = barre->yPos + barre->ySize/2 +5;
}
void setBalleJ2ToScreen(Balle * balle, Barre * barre){
	balle->xPos =0;
	balle->yPos = barre->yPos - (barre->ySize/2 +5);
}

