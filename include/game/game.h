#ifndef __GAME_H__
#define __GAME_H__

#include "joueur/barre.h"
#include "joueur/joueur.h"
#include "balle/balle.h"
#include "briques/brique.h"

#include <GL/gl.h>

void initScreenGame(Barre * barrej1, Barre * barrej2, Balle * ballej1, Balle * ballej2, float abcisseRepereMax, float ordonneRepereMax, char * theme);
void stopGame(Barre * barrej1, Barre * barrej2, Balle * ballej1, Balle * ballej2);
void initVitesseBalles(Balle * ballej1, Balle * ballej2);
void initVitesseBarres(Barre * barrej1, Barre * barrej2);
void initBonusJoueurs(Joueur * j1,Joueur * j2);

//void genereWallpaper(GLuint * id_text, char * chemin_photo);
void dessinWallpaper(GLuint textureWallpaper, float abcisseRepereMax, float ordonneRepereMax );

void loadGame(	char * theme, GLuint * texture_wallpaper, char * nomlevel, Brique *** arrayBrique, Balle ** balles, int * nbBriques, 
				float abcisseRepereMax, float ordonneRepereMax,Textures * textures_briques);

void dessinBriques(Brique ** briques_array, int nbBriques);
void handleGrilleBrique(Brique ** briques_array, int nbBriques, int nbBalles, Textures textures_briques);
void dessinMessageWin(Joueur * joueur);
#endif