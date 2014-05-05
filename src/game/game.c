#include "game/game.h"
#include "textures/textures.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void initScreenGame(Barre * barrej1, Barre * barrej2, Balle * ballej1, Balle * ballej2, float abcisseRepereMax, float ordonneRepereMax){
	setBarreJ1ToScreen(barrej1,ordonneRepereMax);
  	setBarreJ2ToScreen(barrej2,ordonneRepereMax);

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
	setVecteurVitesse(ballej1,2,2);
	setVecteurVitesse(ballej2,-2,-2);
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
	
	GLuint texture_load;
	loadTexture(&texture_load,"../img/utils/loading.jpg");
	dessinWallpaper(texture_load,abcisseRepereMax,ordonneRepereMax);
	SDL_GL_SwapBuffers(); 

	/***** CHARGEMENT LEVEL *******/
	FILE * file = NULL;

	if(!strcmp(nomlevel,"classique")){
		file = fopen("../level/classique.txt","r");

	}
	else{
		fprintf(stderr, "niveau inconnu");
		exit(EXIT_FAILURE);
	}

	if(file == NULL){
		fprintf(stderr, "erreur chargment %s",nomlevel );
	    exit(EXIT_FAILURE);
	}

	char chemin_wallpaper [50] = "../img/themes/";
	strcat(chemin_wallpaper,theme);
	strcat(chemin_wallpaper,"/screen/wallpaper.jpg");

	loadTexture(texture_wallpaper,chemin_wallpaper);
	loadTexturesBriques(textures_briques,theme);

	int nbBriquesYFile, nbBriquesXFile, type_brique;
	
	fscanf(file,"%d %d", &nbBriquesXFile, &nbBriquesYFile);

	*nbBriques = nbBriquesXFile*nbBriquesYFile;

	float 	ySize = 10, 
			xSize = abcisseRepereMax*2/(float)nbBriquesXFile, 
			xPos=-abcisseRepereMax+(xSize/2),
			yPos=ySize*nbBriquesYFile/2;

	printf("ysize %f, xSize : %f, xPos: %f, yPos, %f\n",ySize,xSize,xPos,yPos );

	Brique ** grille_brique = (Brique **)malloc(sizeof(Brique*)*nbBriquesYFile*nbBriquesXFile);
	
	int i,j,cpt=0;
	for(j=0; j<nbBriquesYFile; j++){

		xPos=-abcisseRepereMax+(xSize/2);

		for(i=0;i<nbBriquesXFile;i++){
			fscanf(file,"%d",&type_brique);
			Brique * brique = initBrique(xPos,yPos,xSize,ySize,balles);
			
			configureBrique(&brique,type_brique,*textures_briques);
			/*printf("Brique :\n");
			printf("xPos : %f\n",brique->xPos);
			printf("yPos : %f\n",brique->yPos);
			printf("xSize : %f\n",brique->xSize);
			printf("ySize : %f\n",brique->ySize);
			printf("texture : %d\n\n\n",brique->texture);*/
			grille_brique[cpt] = brique;
			xPos += xSize;
			cpt++;
		}
		yPos -= ySize;
	}

	*arrayBrique = grille_brique;
	fclose(file);
	glDeleteTextures(1,&texture_load);
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
