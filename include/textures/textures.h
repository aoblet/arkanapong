#ifndef __TEXTURES_H__
#define __TEXTURES_H__ 
#define CLASSIQUE_1 0
#define INDESTRUCTIBLE_1 1
#define AGRANDISSEMENT_BARRE_3 2
#define AGRANDISSEMENT_BARRE_2 3
#define AGRANDISSEMENT_BARRE_1 4
#define REDUCTION_BARRE_1 5
#define VITESSE_PLUS_BALLE_2 6
#define VITESSE_PLUS_BALLE_1 7
#define VITESSE_MOINS_BALLE_2 8
#define VITESSE_MOINS_BALLE_1 9
#define NB_TEXTURES 10

#include <GL/gl.h>



typedef struct{
	GLuint identifiants[NB_TEXTURES];	
}Textures;

void loadTexturesBriques(Textures * textures, char * theme);
void loadTexture(GLuint * id, char * chemin_fichier);


#endif
