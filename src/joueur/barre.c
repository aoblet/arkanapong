#include "joueur/barre.h"
#include "joueur/joueur.h"
#include <utils/dessin_utils.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <string.h>

Barre initBarre(float xPos, float yPos, float xSize, float ySize, float xVitesse,int rouge, int vert, int bleu){
	Barre b;
	b.xPos = xPos;
	b.yPos = yPos;
	b.xSize = xSize;
	b.ySize = ySize;
	b.xVitesse = xVitesse;
	b.rouge = rouge;
	b.vert = vert;
	b.bleu = bleu;
	b.texture = 0;
	return b;
}

void setPositionBarre(Barre * barre, float xPos, float yPos){
	if(barre != NULL){
		barre->xPos = xPos;
		barre->yPos = yPos;
	}
}
void setSizeBarre(Barre * barre, float xSize,float ySize){
	if(barre != NULL){
		barre->xSize = xSize;
		barre->ySize = ySize;
	}
}
void setVitesseBarre(Barre * barre, float xVitesse){
	if(barre != NULL){
		barre->xVitesse = xVitesse;
	}
}

void dessinBarre(Barre * barre){

	if(barre != NULL){
		glPushMatrix();
			glEnable(GL_TEXTURE_2D );
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, barre->texture);

			glBegin(GL_QUADS);
			glTexCoord2f(0,1);
			glVertex2f(barre->xPos-barre->xSize/2,barre->yPos-(barre->ySize/2));

			glTexCoord2f(1,1);
			glVertex2f(barre->xPos+(barre->xSize/2),barre->yPos-(barre->ySize/2));

			glTexCoord2f(1,0);
			glVertex2f(barre->xPos+(barre->xSize/2),barre->yPos+(barre->ySize/2));

			glTexCoord2f(0,0);
			glVertex2f(barre->xPos-(barre->xSize/2),barre->yPos+(barre->ySize/2));
			glEnd();
			glDisable(GL_BLEND);

			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
}

int handleBarreBord(Barre * barre, float abcisseRepereMax){
	if(barre != NULL){
		if(barre->xPos + barre->xSize/2  > abcisseRepereMax){
			barre->xPos = abcisseRepereMax-(barre->xSize/2);
		}

		if(barre->xPos - barre->xSize/2  < -abcisseRepereMax){
			barre->xPos = -abcisseRepereMax+(barre->xSize/2);
		}
	}
	return 0;
}


void setBarreJ1ToScreen(Barre * barre, float ordonneRepereMax, char * theme){
	if(barre != NULL){
		if(!strcmp(theme,"mario"))
			barre->yPos = -ordonneRepereMax + (barre->ySize/2);
		else
			barre->yPos = -ordonneRepereMax + (barre->ySize/2 +10); // petite marge hardcoded
		barre->xPos = 0;
		
	}
}

void setBarreJ2ToScreen(Barre * barre, float ordonneRepereMax,char * theme){
	if(barre != NULL){
		if(!strcmp(theme,"mario"))
			barre->yPos = ordonneRepereMax - (barre->ySize/2);
		else
			barre->yPos = ordonneRepereMax - (barre->ySize/2); // petite marge hardcoded
		barre->xPos = 0;
	}
}

// -1 gauche, 1 droite
void deplacerBarreX(Barre * barre, int direction,float abcisseRepereMax){
	if(barre != NULL){
		setPositionBarre(barre, barre->xPos + direction*(barre->xVitesse), barre->yPos);
		handleBarreBord(barre,abcisseRepereMax);
	}
}

void stopBarre(Barre * barre){
	barre->xVitesse = 0;
}

