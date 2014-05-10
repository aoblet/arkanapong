/**
*	Entité barre/racket
**/

#ifndef __BARRE_H__
#define __BARRE_H__
#include <GL/gl.h>

typedef struct Barre {
	float xPos;
	float yPos;
	float xSize;
	float ySize;
	float xVitesse;
	//float yVitesse;
	int rouge;
	int vert;
	int bleu;
	GLuint texture;
}Barre;

Barre initBarre(float xPos, float yPos, float xSize, float ySize, float xVitesse, int rouge, int vert, int bleu);
void setPositionBarre(Barre * barre, float xPos, float yPos);
void setSizeBarre(Barre * barre, float xSize,float ySize);
void setVitesseBarre(Barre * barre, float xVitesse);
void dessinBarre(Barre * barre);
void deplacerBarreX(Barre * barre, int direction, float abcisseRepereMax); // -1 gauche, 1 droite
int handleBarreBord(Barre * barre, float abcisseRepereMax);
void setBarreJ1ToScreen(Barre *barre, float ordonneRepereMax);
void setBarreJ2ToScreen(Barre *barre, float ordonneRepereMax);
void stopBarre(Barre * barre);
#endif