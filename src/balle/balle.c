#include "balle/balle.h"

Balle initBalle(double xPos, double yPos,double xVitesse,double yVitesse, double rayon){
	Balle b;
	b.xPos = xPos;
	b.yPos = yPos;
	b.xVitesse = xVitesse;
	b.yVitesse = yVitesse;
	b.rayon = rayon;

	return b;
}