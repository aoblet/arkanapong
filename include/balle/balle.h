/**
*	Entité balle
**/

#ifndef __BALLE_H__
#define

typedef struct {
	double xPos;
	double yPos;
	double xVitesse;
	double yVitesse;
	double rayon;
}Balle;


Balle initBalle(double xPos, double yPos,double xVitesse,double yVitesse, double rayon);
int setAcceleration(Balle * b, double vitesse);
int setVecteurVitesse(Balle * b, double vitesse);
int setSymetriqueVecteurVitesse(Balle * b);



#endif