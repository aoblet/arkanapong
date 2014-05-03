/**
*	Entité balle
**/

#ifndef __BALLE_H__
#define __BALLE_H__
#include "joueur/barre.h"
#include <GL/gl.h>

typedef struct Balle {
	float xPos;
	float yPos;
	float xVitesse;
	float yVitesse;
	float rayon;
	int rouge;
	int vert;
	int bleu;
	Barre * barre_joueur_1;
	Barre * barre_joueur_2;
	struct Joueur * joueur;
	GLuint texture;
}Balle;


Balle initBalle(float xPos, float yPos,float xVitesse,float yVitesse, float rayon, int rouge, int vert, int bleu, struct Joueur * joueur);
void setAcceleration(Balle * b, float vitesse);
void setVecteurVitesse(Balle * b, float xVitesse,float yVitesse);
void setSymetriqueVecteurVitesse(Balle * b);
void setPositionBalle(Balle * b, float xPos, float yPos);
void dessinBalle(Balle * balle,float abcisseRepereMax,float ordonneRepereMax);
int handleBalleBorder(Balle *b, float xMax, float yMax);
void setBarresToBalle(Balle * b, Barre * barrej1, Barre * barrej2);
int handleBalleBarre(Balle * b);
void stopBalle(Balle * b);
void setBalleJ1ToScreen(Balle * balle, Barre * barre);
void setBalleJ2ToScreen(Balle * balle, Barre * barre);
#endif