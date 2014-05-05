#include "game/game.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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

void genereWallpaper(GLuint * id_text, char * chemin_photo){
	SDL_Surface * img = IMG_Load(chemin_photo);

	if(img != NULL){
	    GLenum format;
	    switch(img->format->BytesPerPixel) {
	    	case 1:
	      		format = GL_RED;
	      	break;
	      	case 3:
	      		/* Ne gere pas les machines big-endian (a confirmer...) */
	      		format = GL_RGB;
	      	break;
	      	case 4:
	      		/* Ne gere pas les machines big-endian (a confirmer...) */
	     		 format = GL_RGBA;
	      	break;
	      	default:
		    /* On ne traite pas les autres cas */
		    fprintf(stderr, "Format des pixels de l'image %s non pris en charge\n", chemin_photo);
		    exit(EXIT_FAILURE);
		}

	    glGenTextures(1,id_text);

	    if(*id_text != 0){
			glBindTexture(GL_TEXTURE_2D,*id_text);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

			// GL_UNSIGNED_BYTE -> composante de couleur géré sur SDL
			glTexImage2D( GL_TEXTURE_2D,0, GL_RGB, img->w, img->h, 0, format, GL_UNSIGNED_BYTE, img->pixels);
			SDL_FreeSurface(img);
	    }
	    else{
	    	fprintf(stderr,"probleme glGenTextures wallpaper");
			exit(EXIT_FAILURE);
	    }
	}
	else{
		fprintf(stderr,"echec ouverture screen wallpaper");
		exit(EXIT_FAILURE);
	}
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


void loadLevelBriques(char * nomlevel, Brique *** arrayBrique, Balle ** balles, int * nbBriques, float abcisseRepereMax, float ordonneRepereMax){
	
	GLuint texture_load;
	genereWallpaper(&texture_load,"../img/screen/loading.jpg");
	dessinWallpaper(texture_load,abcisseRepereMax,ordonneRepereMax);
	SDL_GL_SwapBuffers(); 

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
			
			configureBrique(&brique,type_brique);
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
}

void dessinBriques(Brique ** briques_array, int nbBriques){
	int i;
	for(i=0;i<nbBriques;i++){
		dessinBrique(briques_array[i]);
	}
}


void handleGrilleBrique(Brique ** briques_array, int nbBriques, int nbBalles){
	int i;
	for(i=0;i<nbBriques;i++){
		handleBriqueBalles(&(briques_array[i]), nbBalles);
	}
	
}		
