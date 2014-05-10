#ifndef __BRIQUE_H__
#define __BRIQUE_H__

#include <GL/gl.h>
#include "balle/balle.h"
#include "textures/textures.h"
#define  BRIQUE_CLASSIQUE 0
#define  BRIQUE_INDESTRUCTIBLE 1
#define  BRIQUE_AGRANDISSEMENT_BARRE 2
#define  BRIQUE_REDUCTION_BARRE 3
#define  BRIQUE_VITESSE_PLUS_BALLE 4
#define  BRIQUE_VITESSE_MOINS_BALLE 5
#define  BRIQUE_INVERSION_VITESSE_BARRE 6
#define  BRIQUE_VITESSE_BARRE 7

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
void detruireBriques(Brique ** briques, int nbBriques);
void configureBrique(Brique ** brique, int type, Textures textures);
// 0: classique, 1: indestrctible, 2:agrandissement barre, 3:reduction barre, 4:balle, 5:diminution vitesse
void handleBriqueBalles(Brique ** brique, int nbBalles,Textures textures);
void handleCollisionBrique(Brique ** brique, Balle ** balle,Textures textures);


#endif
