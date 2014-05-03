#ifndef __GAME_H__
#define __GAME_H__

#include "joueur/barre.h"
#include "joueur/joueur.h"
#include "balle/balle.h"
#include "briques/brique.h"

#include <GL/gl.h>

void initScreenGame(Barre * barrej1, Barre * barrej2, Balle * ballej1, Balle * ballej2, float abcisseRepereMax, float ordonneRepereMax);
void stopGame(Barre * barrej1, Barre * barrej2, Balle * ballej1, Balle * ballej2);
void initVitesseBalles(Balle * ballej1, Balle * ballej2);
void initVitesseBarres(Barre * barrej1, Barre * barrej2);
void genereWallpaper(GLuint * id_text, char * chemin_photo);
void dessinWallpaper(GLuint textureWallpaper, float abcisseRepereMax, float ordonneRepereMax );
void loadLevelBriques(char * nomlevel, Brique **** arrayBrique, Balle * balles, int * nbBriquesX, int *nbBriquesY, float abcisseRepereMax, float ordonneRepereMax);
void dessinBriques(Brique *** briques_array, int x, int y);
void handleGrilleBrique(Brique *** briques_array, Balle ** balles, int nbBriquesX, int nbBriquesY, int nbBalles);
#endif