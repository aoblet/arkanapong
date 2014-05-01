#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "balle/balle.h"
#include "joueur/joueur.h"
#include "joueur/barre.h"
#include "game/game.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;

static float ABCISSE_REPERE_MAX = 200;
static float ORDONNE_REPERE_MAX = 200;

static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape() {
	float ratio = (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT;
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(ratio*-ABCISSE_REPERE_MAX, ratio*ABCISSE_REPERE_MAX, -ORDONNE_REPERE_MAX, ORDONNE_REPERE_MAX);
}

void setVideoMode() {
	if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		exit(EXIT_FAILURE);
	}
	reshape();

	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapBuffers();
}


int main(int argc, char * argv []){

	if(SDL_Init(SDL_INIT_VIDEO)==-1) {
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return EXIT_FAILURE;
	}

 	setVideoMode();
  	SDL_WM_SetCaption("Arkana", NULL);

  	GLuint textureScreen;
  	genereWallpaper(&textureScreen);

  	Balle balle_joueur1 = initBalle(0,-170,0,0,5,151,187,205);
  	Barre barre_joueur1 = initBarre(0,0,60,5,2,151,187,205);
  	Joueur j1 = initJoueur("Alexis","Oblet",20,&barre_joueur1,&balle_joueur1);

  	Balle balle_joueur2 = initBalle(0,170,0,0,5,255,204,0);
  	Barre barre_joueur2 = initBarre(0,0,60,5,2,255,204,0);
  	Joueur j2 = initJoueur("Machine","Invincible",20,&barre_joueur2,&balle_joueur2);

  	setBarresToBalle(&balle_joueur1, &barre_joueur1,&barre_joueur2);
  	setBarresToBalle(&balle_joueur2, &barre_joueur1,&barre_joueur2);
	
	initScreenGame(&barre_joueur1, &barre_joueur2, &balle_joueur1, &balle_joueur2, ABCISSE_REPERE_MAX, ORDONNE_REPERE_MAX);

  	int loop=1;
  	int partie_stopped=1;
  	while(loop) {
    	Uint32 startTime = SDL_GetTicks();

	    /* dessin */
	    glClear(GL_COLOR_BUFFER_BIT);
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();

	    glColor3ub(255,255,255); // init
	    dessinWallpaper(textureScreen,ABCISSE_REPERE_MAX,ORDONNE_REPERE_MAX);

	    dessinBalle(&balle_joueur1,ABCISSE_REPERE_MAX,ORDONNE_REPERE_MAX);
	    dessinBalle(&balle_joueur2,ABCISSE_REPERE_MAX,ORDONNE_REPERE_MAX);
	    dessinBarre(&barre_joueur1);
	    dessinBarre(&barre_joueur2);
	    SDL_GL_SwapBuffers(); 
	    /* fin dessin */

	    if(!partie_stopped){
		    //gestion touche enfoncée
		    Uint8 *keystates = SDL_GetKeyState(NULL);
		    //joueur 1
		    if(keystates[ SDLK_RIGHT])
		    	deplacerBarreX(&barre_joueur1,1,ABCISSE_REPERE_MAX);
		    else if(keystates[ SDLK_LEFT])
		    	deplacerBarreX(&barre_joueur1,-1,ABCISSE_REPERE_MAX);

		    //joueur 2
		    if(keystates[ SDLK_r])
		    	deplacerBarreX(&barre_joueur2,1,ABCISSE_REPERE_MAX);
		    else if(keystates[ SDLK_e])
		    	deplacerBarreX(&barre_joueur2,-1,ABCISSE_REPERE_MAX);


		    /*****  IA  ******/
		    handleBarreIAJ2( &j1, &j2, ORDONNE_REPERE_MAX);


		    /****** GESTION PERTE ******/
			int perte_potentiel_balle1 = handleBalleBorder(&balle_joueur1, ABCISSE_REPERE_MAX, ORDONNE_REPERE_MAX);
			if(perte_potentiel_balle1 == -1){
				j1.vie -=1;
				partie_stopped = 1;
			}
			else if(perte_potentiel_balle1 == -2){
				j2.vie =-1;
				partie_stopped -= 1;
			}
			
			int perte_potentiel_balle2 = handleBalleBorder(&balle_joueur2, ABCISSE_REPERE_MAX, ORDONNE_REPERE_MAX);
			if(perte_potentiel_balle2 == -1){
				j1.vie -=1;
				partie_stopped = 1;
			}
			else if(perte_potentiel_balle2 == -2){
				j2.vie -=1;
				partie_stopped = 1;
			}
			
			if(partie_stopped){
				stopGame(&barre_joueur1, &barre_joueur2, &balle_joueur1, &balle_joueur2);
			}
		}


	    SDL_Event e;
	    while(SDL_PollEvent(&e)) {
	    	if(e.type == SDL_QUIT) {
	    		loop = 0;
	        	break;
	      	}
	      
	      	switch(e.type) {
	        	case SDL_MOUSEBUTTONUP:
	          
	        	break;
	          
		        case SDL_VIDEORESIZE:
		          WINDOW_WIDTH = e.resize.w;
		          WINDOW_HEIGHT = e.resize.h;
		          setVideoMode();
		        break;

	        	case SDL_KEYDOWN:
	      	  		switch(e.key.keysym.sym){
	      	    		case 'q' : 
	      	    		case SDLK_ESCAPE : 
	        		  		loop = 0;
	        			break;

	            		case SDLK_UP:
	            		break;

	            		case SDLK_DOWN:
	           			break;
	      	    		
	      	    		case SDLK_RETURN :
		      	    		if(partie_stopped){
								initScreenGame(&barre_joueur1, &barre_joueur2, &balle_joueur1, &balle_joueur2, ABCISSE_REPERE_MAX, ORDONNE_REPERE_MAX);
								//vitesse default balles
								initVitesseBalles(&balle_joueur1,&balle_joueur2);
								initVitesseBarres(&barre_joueur1,&barre_joueur2);
								partie_stopped = 0;
								printf("Vie joueur 1: %d\n", j1.vie );
								printf("Vie joueur 2: %d\n", j2.vie );
								printf("\n" );
		      	    		}
	      	    		break;
	      	    		default : break;
	      	  	}

	          	break;
	          
	         	case SDL_KEYUP:
	          		switch(e.key.keysym.sym){
	          			case SDLK_UP:
	          				setAcceleration(&balle_joueur1,1.2);
	          				setAcceleration(&balle_joueur2,1.2);
	            		break;

			            case SDLK_DOWN:
	          				setAcceleration(&balle_joueur1,0.5);
	          				setAcceleration(&balle_joueur1,0.5);

			            break;

	            		default:break;
	         	} 
	        	default:break;

	      	}
    	}
    
		Uint32 elapsedTime = SDL_GetTicks() - startTime;
	    if(elapsedTime < FRAMERATE_MILLISECONDS) {
	      	SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
	    }
	}

 	glBindTexture(GL_TEXTURE_2D,0);
    glDeleteTextures(1,&textureScreen);
  	SDL_Quit(); 
	return EXIT_SUCCESS;

}