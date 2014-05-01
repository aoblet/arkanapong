#ifndef __GAME_H__
#define __GAME_H__

#include "joueur/barre.h"
#include "joueur/joueur.h"
#include "balle/balle.h"
#include <GL/gl.h>

void initScreenGame(Barre * barrej1, Barre * barrej2, Balle * ballej1, Balle * ballej2, float abcisseRepereMax, float ordonneRepereMax);
void stopGame(Barre * barrej1, Barre * barrej2, Balle * ballej1, Balle * ballej2);
void initVitesseBalles(Balle * ballej1, Balle * ballej2);
void initVitesseBarres(Barre * barrej1, Barre * barrej2);
void genereWallpaper(GLuint * id_text);
void dessinWallpaper(GLuint textureWallpaper, float abcisseRepereMax, float ordonneRepereMax );

#endif