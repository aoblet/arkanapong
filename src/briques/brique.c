#include "briques/brique.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "joueur/joueur.h"
#include "joueur/barre.h"


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
	if(brique !=NULL && *brique!= NULL)
		*brique = NULL;
}

void setPositionBrique(Brique ** brique, float xPos, float yPos){
	if(brique != NULL && *brique != NULL){
		(*brique)->xPos = xPos;
		(*brique)->yPos = yPos;
	}
}

void setTextureBrique(Brique ** brique, char * chemin_texture){
	if(brique != NULL && *brique != NULL){
		SDL_Surface * img = IMG_Load(chemin_texture);

		if(img != NULL){
		    GLenum format;
		    switch(img->format->BytesPerPixel) {
		    	case 1:
		      		format = GL_RED;
		      	break;
		      	case 3:
		      		/* Ne gere pas les machines big-endian (a confirmer...) */
		      		format = GL_RGB;
		      	break;
		      	case 4:
		      		/* Ne gere pas les machines big-endian (a confirmer...) */
		     		 format = GL_RGBA;
		      	break;
		      	default:
			    /* On ne traite pas les autres cas */
			    fprintf(stderr, "Format des pixels de l'image %s non pris en charge\n", chemin_texture);
			    exit(EXIT_FAILURE);
			}

		    glGenTextures(1,&((*brique)->texture));

		    if((*brique)->texture != 0){
				glBindTexture(GL_TEXTURE_2D,(*brique)->texture);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

				// GL_UNSIGNED_BYTE -> composante de couleur géré sur SDL
				glTexImage2D( GL_TEXTURE_2D,0, GL_RGB, img->w, img->h, 0, format, GL_UNSIGNED_BYTE, img->pixels);
				SDL_FreeSurface(img);
		    }
		    else{
		    	fprintf(stderr,"probleme glGenTextures brique");
				exit(EXIT_FAILURE);
		    }
		}
		else{
			fprintf(stderr,"echec ouverture texture brique");
			exit(EXIT_FAILURE);
		}

	}
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
void configureBrique(Brique ** brique, int type){
	if(brique != NULL){
		(*brique)->type_brique = type;
		if(type == 0){ 
			setTextureBrique(brique,"../img/briques/classique/1.png");
		}
		else if(type == 1){
			setTextureBrique(brique,"../img/briques/indestructible/1.png");
		}
		else if(type == 2){
			(*brique)->vie = 3;
			setTextureBrique(brique,"../img/briques/agrandissement_barre/3.png");
		}
		else if(type == 3){
			setTextureBrique(brique,"../img/briques/reduction_barre/1.png");
		}
		else if(type == 4){
			(*brique)->vie = 2;
			setTextureBrique(brique,"../img/briques/vitesse_plus_balle/2.png");
		}
		else if(type == 5){
			(*brique)->vie = 2;
			setTextureBrique(brique,"../img/briques/vitesse_moins_balle/2.png");
		}
	}
}

void handleCollisionBrique(Brique ** brique, Balle ** balle){
	if(brique != NULL && *brique!=NULL){
		if((*brique)->type_brique == 0){
			if( ((*brique)->vie-=1) <= 0)
				detruireBrique(brique);
		}
		else if((*brique)->type_brique == 1){
			// rien à faire:indestructible
		}
		else if((*brique)->type_brique == 2){
			(*brique)->vie -=1;

			if( (*brique)->vie == 2){
				setTextureBrique(brique,"../img/briques/agrandissement_barre/2.png");
			}
			else if( (*brique)->vie == 1){
				setTextureBrique(brique,"../img/briques/agrandissement_barre/1.png");
			}
			else{
				//success
				Barre ** barre_joueur =  &(((*balle)->joueur)->barre);
				(*barre_joueur)->xSize*=2;
				detruireBrique(brique);
			}
		}
		else if((*brique)->type_brique == 3){
			if( ((*brique)->vie-=1) <= 0){
				Barre ** barre_joueur = &((*balle)->joueur->barre);
				(*barre_joueur)->xSize /=2;
				detruireBrique(brique);
			}
		}
		else if((*brique)->type_brique == 4){
			if( ((*brique)->vie-=1) == 1){
				setTextureBrique(brique,"../img/briques/vitesse_plus_balle/1.png");
			}
			else{
				(*balle)->xVitesse *= 2;
				(*balle)->yVitesse *= 2;
				detruireBrique(brique);
			}
		}
		else if((*brique)->type_brique == 5){
			if( ((*brique)->vie-=1) == 1){
				setTextureBrique(brique,"../img/briques/vitesse_moins_balle/1.png");
			}
			else{
				(*balle)->xVitesse /= 2;
				(*balle)->yVitesse /= 2;
				detruireBrique(brique);
			}
		}
	}
}

void handleBriqueBalles(Brique ** brique, int nbBalles){

	int i;
	for(i=0;i<nbBalles;i++){
		if(brique != NULL && *brique != NULL){
			Balle * balle = (*brique)->balles[i];
			float extremiteBalleDroit 	= balle->xPos + balle->rayon;
			float extremiteBalleGauche 	= balle->xPos - balle->rayon;
			float extremiteBalleHaut 	= balle->yPos + balle->rayon;
			float extremiteBalleBas 	= balle->yPos - balle->rayon;

			float extremiteBriqueHaut 	= (*brique)->yPos+(*brique)->ySize/2;
			float extremiteBriqueBas 	= (*brique)->yPos-(*brique)->ySize/2;
			float extremiteBriqueDroit	= (*brique)->xPos+(*brique)->xSize/2;
			float extremiteBriqueGauche	= (*brique)->xPos-(*brique)->xSize/2;


			if(balle->yVitesse>0){

				if(extremiteBalleHaut > extremiteBriqueBas && extremiteBalleBas < extremiteBriqueHaut){
					// tappe extremite gauche
					if(extremiteBalleGauche < extremiteBriqueGauche && extremiteBalleDroit > extremiteBriqueGauche){
						balle->xVitesse *=-1;
						setPositionBalle(balle, extremiteBriqueGauche-balle->rayon, balle->yPos);
						handleCollisionBrique(brique,&((*brique)->balles[i]));

					}
					// tappe extremite droit
					else if(extremiteBalleDroit > extremiteBriqueDroit && extremiteBalleGauche < extremiteBriqueDroit){
						balle->xVitesse *=-1;
						setPositionBalle(balle, extremiteBriqueDroit+balle->rayon, balle->yPos);
						handleCollisionBrique(brique,&((*brique)->balles[i]));
						
					}
					else if(extremiteBalleGauche < extremiteBriqueDroit && extremiteBalleDroit > extremiteBriqueGauche ){
						setPositionBalle(balle,balle->xPos, extremiteBriqueBas-balle->rayon);
						balle->yVitesse *=-1;
						handleCollisionBrique(brique,&((*brique)->balles[i]));
						
					}
				}
			}
			else{
				if(extremiteBalleBas < extremiteBriqueHaut && extremiteBalleHaut > extremiteBriqueBas){
					if(extremiteBalleGauche < extremiteBriqueGauche && extremiteBalleDroit > extremiteBriqueGauche){
						balle->xVitesse *=-1;
						setPositionBalle(balle, extremiteBriqueGauche-balle->rayon, balle->yPos);
						handleCollisionBrique(brique,&((*brique)->balles[i]));
						
						printf("tappe gauche\n");
					}

					else if(extremiteBalleDroit > extremiteBriqueDroit && extremiteBalleGauche < extremiteBriqueDroit){
						balle->xVitesse *=-1;
						setPositionBalle(balle, extremiteBriqueDroit+balle->rayon, balle->yPos);
						handleCollisionBrique(brique,&((*brique)->balles[i]));
						
						printf("tappe droit\n");


					}
					else if(extremiteBalleGauche < extremiteBriqueDroit && extremiteBalleDroit > extremiteBriqueGauche ){
						balle->yVitesse *=-1;
						setPositionBalle(balle, balle->xPos, extremiteBriqueHaut+balle->rayon);
						handleCollisionBrique(brique,&((*brique)->balles[i]));
						
					}
				}
			}
		}
	}
}

