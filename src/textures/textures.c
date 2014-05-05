#include "textures/textures.h"
#include <string.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>



void loadTexture(GLuint * id, char * chemin_texture){
	SDL_Surface * img = IMG_Load(chemin_texture);

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
		    fprintf(stderr, "Format des pixels de l'image %s non pris en charge\n", chemin_texture);
		    exit(EXIT_FAILURE);
		}

	    glGenTextures(1,id);

	    if(id!= 0){
			glBindTexture(GL_TEXTURE_2D,*id);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

			// GL_UNSIGNED_BYTE -> composante de couleur géré sur SDL
			glTexImage2D( GL_TEXTURE_2D,0, GL_RGB, img->w, img->h, 0, format, GL_UNSIGNED_BYTE, img->pixels);
			SDL_FreeSurface(img);
	    }
	    else{
	    	fprintf(stderr,"probleme glGenTextures %s",chemin_texture);
			exit(EXIT_FAILURE);
	    }
	}
	else{
		fprintf(stderr,"echec ouverture texture: %s (img_load)",chemin_texture);
		exit(EXIT_FAILURE);
	}

	
}


void loadTexturesBriques(Textures * textures, char * theme){
	if(!strcmp(theme,"default")){
		loadTexture( &(textures->identifiants[CLASSIQUE_1]) , 				"../img/themes/default/briques/classique/1.png");
		loadTexture( &(textures->identifiants[INDESTRUCTIBLE_1]) , 			"../img/themes/default/briques/indestructible/1.png");
		loadTexture( &(textures->identifiants[AGRANDISSEMENT_BARRE_3]) , 	"../img/themes/default/briques/agrandissement_barre/3.png");
		loadTexture( &(textures->identifiants[AGRANDISSEMENT_BARRE_2]) ,	"../img/themes/default/briques/agrandissement_barre/2.png");
		loadTexture( &(textures->identifiants[AGRANDISSEMENT_BARRE_1]) , 	"../img/themes/default/briques/agrandissement_barre/1.png");
		//loadTexture( textures->identifiants[REDUCTION_BARRE_1] , 		"../img/themes/default/briques/reduction_barre/1.png");
		loadTexture( &(textures->identifiants[VITESSE_PLUS_BALLE_2]) , 		"../img/themes/default/briques/vitesse_plus_balle/2.png");
		loadTexture( &(textures->identifiants[VITESSE_PLUS_BALLE_1]) , 		"../img/themes/default/briques/vitesse_plus_balle/1.png");
		//loadTexture( textures->identifiants[VITESSE_MOINS_BALLE_2] , 	"../img/themes/default/briques/vitesse_moins_balle/2.png");
		//loadTexture( textures->identifiants[VITESSE_MOINS_BALLE_1] , 	"../img/themes/default/briques/vitesse_moins_balle/1.png");
	}		
	//else if(!strcmp(theme,""))	
}

