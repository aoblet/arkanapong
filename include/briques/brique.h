#ifndef __BRIQUE_H__
#define __BRIQUE_H__

#include <GL/gl.h>
#include "balle/balle.h"

typedef struct{
	float xPos;
	float yPos;
	float xSize;
	float ySize;
	GLuint texture;
	Balle * balles;
	int vie;
	int type_brique;
} Brique;

Brique * initBrique(float xPos, float yPos, float xSize, float ySize, Balle * balles);
void setTextureBrique(Brique ** brique, char * chemin_texture);
void setPositionBrique(Brique ** brique, float xPos, float yPos);
void dessinBrique(Brique * brique);
void detruireBrique(Brique ** brique);
void configureBrique(Brique ** brique, int type);
// 0: classique, 1: indestrctible, 2:agrandissement barre, 3:reduction barre, 4:balle, 5:diminution vitesse
void handleBriqueBalles(Brique ** brique, Balle ** balles, int nbBalles);


#endif
