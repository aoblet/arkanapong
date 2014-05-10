#include "game/masterLauncher.h"
#include "game/menu.h"

//Item_menu createItem(float xPos, float yPos, float xSize, float ySize,int nb_elements){

void selectMenu(char ** theme, char ** level, char ** mode_jeu, float abcisse_repere_max, float ordonne_repere_max){
	float center_x = abcisse_repere_max /2; //3/4 de la fenetre en x

	float x_size = 274, y_size = 61, yEspace = 10, yPos =(y_size+yEspace)*5/2 + y_size; 
	
	Item_menu menu[5];

	menu[START_GAME]=createItem(center_x, (yPos=yPos-y_size) , x_size,y_size,1);

	
}