#ifndef __BRIQUE_H__
#define __BRIQUE_H__

#include <GL/gl.h>
#include "balle/balle.h"
#include "textures/textures.h"

typedef struct{
	float xPos;
	float yPos;
	float xSize;
	float ySize;
	GLuint texture;
	Balle ** balles;
	int vie;
	int type_brique;
} Brique;

Brique * initBrique(float xPos, float yPos, float xSize, float ySize, Balle ** balles);
void setTextureBrique(Brique ** brique, GLuint id_texture);
void setPositionBrique(Brique ** brique, float xPos, float yPos);
void dessinBrique(Brique * brique);
void detruireBrique(Brique ** brique);
void configureBrique(Brique ** brique, int type, Textures textures);
// 0: classique, 1: indestrctible, 2:agrandissement barre, 3:reduction barre, 4:balle, 5:diminution vitesse
void handleBriqueBalles(Brique ** brique, int nbBalles,Textures textures);
void handleCollisionBrique(Brique ** brique, Balle ** balle,Textures textures);


#endif
