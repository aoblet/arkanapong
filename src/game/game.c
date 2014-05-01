#include "game/game.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>


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
	setVecteurVitesse(ballej1,1.6,1);
	setVecteurVitesse(ballej2,-1,-1.3);
}

void initVitesseBarres(Barre * barrej1, Barre * barrej2){
	setVitesseBarre(barrej1,5);
	setVitesseBarre(barrej2,5);
}

void genereWallpaper(GLuint * id_text){
	char * nomImage = "../img/screen/wallpaper.jpg";
	SDL_Surface * img = IMG_Load(nomImage);

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
		    fprintf(stderr, "Format des pixels de l'image %s non pris en charge\n", nomImage);
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
