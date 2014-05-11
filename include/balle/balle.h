/**
*	Entité balle
**/

#ifndef __BALLE_H__
#define __BALLE_H__
#include "joueur/barre.h"
#include <GL/gl.h>
#include "briques/bonus.h"

typedef struct Balle {
	float xPos;
	float yPos;

	float normeVitesse;
	float angleVitesse;

	float xVitesse;
	float yVitesse;
	float rayon;
	int rouge;
	int vert;
	int bleu;
	Bonus * bonus; // 1 seul bonus pour la balle max
	struct Joueur * joueur;
	GLuint texture;
}Balle;


Balle initBalle(float xPos, float yPos,float normeVitesse,float angleVitesse, float rayon, int rouge, int vert, int bleu, struct Joueur * joueur);

void setAngleVitesseBalle(Balle * balle, float angleVitesse);
void setNormeVitesseBalle(Balle * balle, float normeVitesse);

void setAcceleration(Balle * b, float vitesse);
void setPositionBalle(Balle * b, float xPos, float yPos);
void dessinBalle(Balle * balle,float abcisseRepereMax,float ordonneRepereMax);
int handleBalleBorder(Balle *b, float xMax, float yMax);
void setBarresToBalle(Balle * b, Barre * barrej1, Barre * barrej2);
int handleBalleBarres(Balle * b,struct Joueur * joueur1, struct Joueur * joueur2);
void stopBalle(Balle * b);
void setBalleJ1ToScreen(Balle * balle, Barre * barre);
void setBalleJ2ToScreen(Balle * balle, Barre * barre);
void addBonusBalle(Balle * balle, int compteur_frame, int nom_bonus, float value);
void updateBonusBalle(Balle * Balle, float norme_vitesse_default);
void initBonusBalle(Balle * balle);
#endif