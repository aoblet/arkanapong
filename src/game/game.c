#include "game/game.h"
#include "textures/textures.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void initScreenGame(Barre * barrej1, Barre * barrej2, Balle * ballej1, Balle * ballej2, float abcisseRepereMax, float ordonneRepereMax, char * theme){
	setBarreJ1ToScreen(barrej1,ordonneRepereMax,theme);
  	setBarreJ2ToScreen(barrej2,ordonneRepereMax,theme);

  	setBalleJ1ToScreen(ballej1,barrej1);
  	setBalleJ2ToScreen(ballej2,barrej2);
}

void stopGame(Barre * barrej1, Barre * barrej2, Balle * ballej1, Balle * ballej2){
	stopBarre(barrej1);
	stopBarre(barrej2);
	stopBalle(ballej1);
	stopBalle(ballej2);
}

void initVitesseBalles(Balle * ballej1, Balle * ballej2){
	setNormeVitesseBalle(ballej1,1);
	setNormeVitesseBalle(ballej2,1);
	srand(time(NULL));

	setAngleVitesseBalle(ballej1,fmod(rand(),M_PI));
	rand();
	setAngleVitesseBalle(ballej2,-fmod(rand(),M_PI));
}

void initVitesseBarres(Barre * barrej1, Barre * barrej2){
	setVitesseBarre(barrej1,5);
	setVitesseBarre(barrej2,5);
}


void dessinWallpaper(GLuint textureWallpaper, float abcisseRepereMax, float ordonneRepereMax ){
 	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureWallpaper);
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex2f(-abcisseRepereMax,-ordonneRepereMax);

	glTexCoord2f(1,1);
	glVertex2f(abcisseRepereMax,-ordonneRepereMax);

	glTexCoord2f(1,0);
	glVertex2f(abcisseRepereMax,ordonneRepereMax);

	glTexCoord2f(0,0);
	glVertex2f(-abcisseRepereMax,ordonneRepereMax);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}


void loadGame(	char * theme, GLuint * texture_wallpaper, char * nomlevel, Brique *** arrayBrique, Balle ** balles, 
				int * nbBriques, float abcisseRepereMax, float ordonneRepereMax,Textures * textures_briques){
	
	/*GLuint texture_load;
	loadTexture(&texture_load,"../img/utils/loading.jpg");
	dessinWallpaper(texture_load,abcisseRepereMax,ordonneRepereMax);
	SDL_GL_SwapBuffers(); */

	/***** CHARGEMENT LEVEL *******/
	FILE * file = NULL;
	char chemin_level[100];

	if(!strcmp(nomlevel,"classique")){
		strcpy(chemin_level,"../level/classique.txt");
	}
	else if(!strcmp(nomlevel,"arkano")){
		strcpy(chemin_level,"../level/arkano.txt");
	}
	else if(!strcmp(nomlevel,"full_bonus")){
		strcpy(chemin_level,"../level/a.txt");
	}
	else if(!strcmp(nomlevel,"no_bonus")){
		strcpy(chemin_level,"../level/a.txt");
	}
	else{
		fprintf(stderr, "niveau inconnu");
		exit(EXIT_FAILURE);
	}

	file = fopen(chemin_level,"r");

	if(file == NULL){
		fprintf(stderr, "erreur chargment %s",nomlevel );
	    exit(EXIT_FAILURE);
	}

	char chemin_wallpaper [50] = "../img/themes/";
	strcat(chemin_wallpaper,theme);
	strcat(chemin_wallpaper,"/screen/wallpaper.png");

	loadTexture(texture_wallpaper,chemin_wallpaper);
	loadTexturesBriques(textures_briques,theme);

	int nbBriquesYFile, nbBriquesXFile, type_brique;
	
	fscanf(file,"%d %d", &nbBriquesXFile, &nbBriquesYFile);

	*nbBriques = nbBriquesXFile*nbBriquesYFile;

	float 	ySize = 20, 
			xSize = abcisseRepereMax*2/(float)nbBriquesXFile, 
			xPos=-abcisseRepereMax+(xSize/2),
			yPos=ySize*nbBriquesYFile/2 - ySize/2;

	//printf("ysize %f, xSize : %f, xPos: %f, yPos, %f\n",ySize,xSize,xPos,yPos );

	Brique ** grille_brique = (Brique **)malloc(sizeof(Brique*)*nbBriquesYFile*nbBriquesXFile);
	
	int i,j,cpt=0;
	for(j=0; j<nbBriquesYFile; j++){

		xPos=-abcisseRepereMax+(xSize/2);

		for(i=0;i<nbBriquesXFile;i++){
			fscanf(file,"%d",&type_brique);
			if(type_brique != -1){
				Brique * brique = initBrique(xPos,yPos,xSize,ySize,balles);
				configureBrique(&brique,type_brique,*textures_briques);
				grille_brique[cpt] = brique;
			}
			else
				grille_brique[cpt] = NULL;
			
			xPos += xSize;
			cpt++;
		}
		yPos -= ySize;
	}

	*arrayBrique = grille_brique;
	fclose(file);
	//glDeleteTextures(1,&texture_load);
}

void dessinBriques(Brique ** briques_array, int nbBriques){
	int i;
	for(i=0;i<nbBriques;i++){
		dessinBrique(briques_array[i]);
	}
}


void handleGrilleBrique(Brique ** briques_array, int nbBriques, int nbBalles, Textures textures_briques){
	int i;
	for(i=0;i<nbBriques;i++){
		handleBriqueBalles(&(briques_array[i]), nbBalles,textures_briques);
	}
	
}

void initBonusJoueurs(Joueur * j1,Joueur * j2){
	if(j1 != NULL)
		detruireBonusJoueur(j1);
	if(j2 != NULL)
		detruireBonusJoueur(j2);
}

void iniBonusBalles(Balle * balle_j1, Balle * balle_j2){
	if(balle_j1 != NULL)
		initBonusBalle(balle_j1);
	if(balle_j2 != NULL)
		initBonusBalle(balle_j2);
}

void dessinMessageWin(char * content){
	GLuint texture=0;
	glGenTextures(1,&texture);

	SDL_Color color = {255,255,255,0};
	TTF_Font *police_infos_game = TTF_OpenFont("../font/Harabara.ttf",40);
	SDL_Surface * infos_sdl = TTF_RenderText_Blended(police_infos_game,content,color);
	float x = -infos_sdl->w/2, y = infos_sdl->h/2;
	dessinSurfaceInfos(infos_sdl,x,y);
	TTF_CloseFont(police_infos_game);

	SDL_FreeSurface(infos_sdl);
}