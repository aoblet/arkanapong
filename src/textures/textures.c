#include "textures/textures.h"
#include <string.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>



void loadTexture(GLuint * id, char * chemin_texture){
	
	glGenTextures(1,id);
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

	    if(id!= 0){
			glBindTexture(GL_TEXTURE_2D,*id);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

			// GL_UNSIGNED_BYTE -> composante de couleur géré sur SDL
			glTexImage2D( GL_TEXTURE_2D,0, GL_RGBA, img->w, img->h, 0, format, GL_UNSIGNED_BYTE, img->pixels);
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
	textures->nb_textures = NB_TEXTURES_BRIQUES;
	char theme_string_safe[50];
	strcpy(theme_string_safe,theme);

	if(!(!strcmp(theme_string_safe,"espace") || !strcmp(theme_string_safe,"mario") || !strcmp(theme_string_safe,"flat") ))
		exit(EXIT_FAILURE);
	
	char chemin_theme[50], chemin_theme_copy[5000];
	sprintf(chemin_theme,"../img/themes/%s/briques/",theme_string_safe);
	strcpy(chemin_theme_copy,chemin_theme);
	loadTexture( &(textures->identifiants[TEXTURE_CLASSIQUE_1]) , 				strcat(strcpy(chemin_theme_copy,chemin_theme),"classique/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_INDESTRUCTIBLE_1]) , 			strcat(strcpy(chemin_theme_copy,chemin_theme),"indestructible/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_AGRANDISSEMENT_BARRE_3]) , 	strcat(strcpy(chemin_theme_copy,chemin_theme),"agrandissement_barre/3.png"));
	loadTexture( &(textures->identifiants[TEXTURE_AGRANDISSEMENT_BARRE_2]) ,	strcat(strcpy(chemin_theme_copy,chemin_theme),"agrandissement_barre/2.png"));
	loadTexture( &(textures->identifiants[TEXTURE_AGRANDISSEMENT_BARRE_1]) , 	strcat(strcpy(chemin_theme_copy,chemin_theme),"agrandissement_barre/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_REDUCTION_BARRE_1]) , 		strcat(strcpy(chemin_theme_copy,chemin_theme),"reduction_barre/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_VITESSE_PLUS_BALLE_2]) , 		strcat(strcpy(chemin_theme_copy,chemin_theme),"vitesse_plus_balle/2.png"));
	loadTexture( &(textures->identifiants[TEXTURE_VITESSE_PLUS_BALLE_1]) , 		strcat(strcpy(chemin_theme_copy,chemin_theme),"vitesse_plus_balle/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_VITESSE_MOINS_BALLE_2]) , 	strcat(strcpy(chemin_theme_copy,chemin_theme),"vitesse_moins_balle/2.png"));
	loadTexture( &(textures->identifiants[TEXTURE_VITESSE_MOINS_BALLE_1]) , 	strcat(strcpy(chemin_theme_copy,chemin_theme),"vitesse_moins_balle/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_INVERSION_VITESSE_BARRE_1]) , strcat(strcpy(chemin_theme_copy,chemin_theme),"inversion_vitesse_barre/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_VITESSE_BARRE_3]) , 		strcat(strcpy(chemin_theme_copy,chemin_theme),"vitesse_barre/3.png"));
	loadTexture( &(textures->identifiants[TEXTURE_VITESSE_BARRE_2]) , 		strcat(strcpy(chemin_theme_copy,chemin_theme),"vitesse_barre/2.png"));
	loadTexture( &(textures->identifiants[TEXTURE_VITESSE_BARRE_1]) , 		strcat(strcpy(chemin_theme_copy,chemin_theme),"vitesse_barre/1.png"));
}

void loadTexturesMenu(Textures * textures){
	char * chemin_menu = "../img/menu/";
	char chemin_menu_copy[1000];
	textures->nb_textures = NB_TEXTURES_MENU;

	loadTexture( &(textures->identifiants[TEXTURE_START_GAME_ON]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/start/on/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_START_GAME_OFF]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/start/off/1.png"));
	
	loadTexture( &(textures->identifiants[TEXTURE_MODE_JEU_SOLO_ON]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/mode/solo/on/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_MODE_JEU_SOLO_OFF]) ,			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/mode/solo/off/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_MODE_JEU_MULTI_ON]) , 		strcat(strcpy(chemin_menu_copy,chemin_menu),"item/mode/multi/on/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_MODE_JEU_MULTI_OFF]) , 		strcat(strcpy(chemin_menu_copy,chemin_menu),"item/mode/multi/off/1.png"));
	
	loadTexture( &(textures->identifiants[TEXTURE_THEME_MARIO_ON]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/theme/mario/on/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_THEME_MARIO_OFF]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/theme/mario/off/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_THEME_ESPACE_ON]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/theme/espace/on/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_THEME_ESPACE_OFF]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/theme/espace/off/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_THEME_FLAT_ON]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/theme/flat/on/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_THEME_FLAT_OFF]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/theme/flat/off/1.png"));
	
	loadTexture( &(textures->identifiants[TEXTURE_LEVEL_CLASSIQUE_ON]) , 		strcat(strcpy(chemin_menu_copy,chemin_menu),"item/level/classique/on/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_LEVEL_CLASSIQUE_OFF]) , 		strcat(strcpy(chemin_menu_copy,chemin_menu),"item/level/classique/off/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_LEVEL_FULL_BONUS_ON]) , 		strcat(strcpy(chemin_menu_copy,chemin_menu),"item/level/full_bonus/on/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_LEVEL_FULL_BONUS_OFF]) , 		strcat(strcpy(chemin_menu_copy,chemin_menu),"item/level/full_bonus/off/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_LEVEL_ARKANO_ON]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/level/arkana/on/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_LEVEL_ARKANO_OFF]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/level/arkana/off/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_LEVEL_NO_BONUS_ON]) , 		strcat(strcpy(chemin_menu_copy,chemin_menu),"item/level/no_bonus/on/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_LEVEL_NO_BONUS_OFF]) , 		strcat(strcpy(chemin_menu_copy,chemin_menu),"item/level/no_bonus/off/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_LEVEL_PONG_ON]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/level/pong/on/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_LEVEL_PONG_OFF]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"item/level/pong/off/1.png"));
	
	loadTexture( &(textures->identifiants[TEXTURE_QUIT_ON]) , 					strcat(strcpy(chemin_menu_copy,chemin_menu),"item/quit/on/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_QUIT_OFF]) , 					strcat(strcpy(chemin_menu_copy,chemin_menu),"item/quit/off/1.png"));
	
	loadTexture( &(textures->identifiants[TEXTURE_WALLPAPER_MARIO]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"wallpaper/mario.png"));
	loadTexture( &(textures->identifiants[TEXTURE_WALLPAPER_ESPACE]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"wallpaper/espace.png"));
	loadTexture( &(textures->identifiants[TEXTURE_WALLPAPER_FLAT]) , 			strcat(strcpy(chemin_menu_copy,chemin_menu),"wallpaper/flat.png"));

}

void loadTexturesBarresCoeur(Textures * textures, char * theme){
	textures->nb_textures = NB_TEXTURES_BARRES_COEUR;

	char theme_string_safe[50];
	strcpy(theme_string_safe,theme);
	char chemin_barres[50], chemin_barres_copy[5000];

	sprintf(chemin_barres,"../img/themes/%s/barre/",theme_string_safe);

	if(!(!strcmp(theme_string_safe,"espace") || !strcmp(theme_string_safe,"mario") || !strcmp(theme_string_safe,"flat") ))
		exit(EXIT_FAILURE);

	loadTexture( &(textures->identifiants[TEXTURE_BARRE_BAS]) , 	strcat(strcpy(chemin_barres_copy,chemin_barres),"bas/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_BARRE_HAUT]) ,	strcat(strcpy(chemin_barres_copy,chemin_barres),"haut/1.png"));
	loadTexture( &(textures->identifiants[TEXTURE_COEUR]) ,			"../img/utils/heart.png");
}

void detruireTextures(Textures * textures){
	glDeleteTextures(textures->nb_textures,textures->identifiants);
}

void dessinSurfaceInfos(SDL_Surface * surface, float xPos,float yPos){
	GLuint texture=0;
	glEnable(GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glColor3ub(255,255,255);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex2f(xPos,yPos-surface->h);

		glTexCoord2f(1,1);
		glVertex2f(xPos+surface->w,yPos-surface->h);

		glTexCoord2f(1,0);
		glVertex2f(xPos+surface->w,yPos);

		glTexCoord2f(0,0);
		glVertex2f(xPos,yPos);
	glEnd();
	glDeleteTextures(1,&texture);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}
void dessinTexture(GLuint texture,float xPos, float yPos, float xSize, float ySize){
	glEnable(GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex2f(xPos-xSize/2,yPos-(ySize/2));

	glTexCoord2f(1,1);
	glVertex2f(xPos+(xSize/2),yPos-(ySize/2));

	glTexCoord2f(1,0);
	glVertex2f(xPos+(xSize/2),yPos+(ySize/2));

	glTexCoord2f(0,0);
	glVertex2f(xPos-(xSize/2),yPos+(ySize/2));
	glEnd();
	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}
