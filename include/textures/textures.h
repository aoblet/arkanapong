#ifndef __TEXTURES_H__
#define __TEXTURES_H__ 
#define TEXTURE_CLASSIQUE_1 0
#define TEXTURE_INDESTRUCTIBLE_1 1
#define TEXTURE_AGRANDISSEMENT_BARRE_3 2
#define TEXTURE_AGRANDISSEMENT_BARRE_2 3
#define TEXTURE_AGRANDISSEMENT_BARRE_1 4
#define TEXTURE_REDUCTION_BARRE_1 5
#define TEXTURE_VITESSE_PLUS_BALLE_2 6
#define TEXTURE_VITESSE_PLUS_BALLE_1 7
#define TEXTURE_VITESSE_MOINS_BALLE_2 8
#define TEXTURE_VITESSE_MOINS_BALLE_1 9
#define TEXTURE_INVERSION_VITESSE_BARRE_1 10
#define TEXTURE_VITESSE_BARRE_3 11
#define TEXTURE_VITESSE_BARRE_2 12
#define TEXTURE_VITESSE_BARRE_1 13
#define NB_TEXTURES 14

#include <GL/gl.h>


typedef struct{
	GLuint identifiants[NB_TEXTURES];
	int nb_textures;
}Textures;

void loadTexturesBriques(Textures * textures, char * theme);
void loadTexture(GLuint * id, char * chemin_fichier);
void detruireTextures(Textures * textures);

#endif
