#include "game/masterLauncher.h"
#include "game/menu.h"
#include "textures/textures.h"
#include <string.h>
#include <SDL/SDL.h>


void handleItem(int * indice_item_inside, int indice_menu, Item_menu * item,Item_menu * menu){
	if(*indice_item_inside < 0)
		*indice_item_inside +=1;
	else if(*indice_item_inside >= item->nb_elements)
		*indice_item_inside-=1;
	else{
		item->indice_courant = *indice_item_inside;

		if(indice_menu == THEME){
			if(!strcmp(menu[THEME].values[menu[THEME].indice_courant],"mario"))
				menu[WALLPAPER].indice_courant=0;
			else if(!strcmp(menu[THEME].values[menu[THEME].indice_courant],"espace"))
				menu[WALLPAPER].indice_courant=1;
			else
				menu[WALLPAPER].indice_courant=2;	
		}
	}	
}

void handleMenu(int * indice_menu, int * indice_item Item_menu, * menu, int nb_items_menu){
	if(*indice_menu < 0)
		*indice_menu+=1;
	else if(*indice_menu > nb_items_menu)
		*indice_menu-=1;
	else{
		int i;
		for(i=0;i<nb_items_menu;i++){
			menu[i].on_off = 0; //desactive les items
		}
		menu[*indice_menu].on_off = 1; //active l'item en question
		*indice_item = menu[*indice_menu].indice_courant;
	}
}

void drawItem(Item_menu * item, float abcisse_repere_max, float ordonne_repere_max ){
	

	glEnable(GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, item->textures[item->indice_courant][item->on_off]);

	glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex2f(item->xPos-(item->xSize/2),item->yPos-(item->ySize/2));

	glTexCoord2f(1,1);
	glVertex2f(item->xPos+(item->xSize/2),item->yPos-(item->ySize/2));

	glTexCoord2f(1,0);
	glVertex2f(item->xPos+(item->xSize/2),item->yPos+(item->ySize/2));

	glTexCoord2f(0,0);
	glVertex2f(item->xPos-(item->xSize/2),item->yPos+(item->ySize/2));
	glEnd();
	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

}

void genereMenu(Item_menu * menu, float abcisse_repere_max, float ordonne_repere_max){
	float center_x = abcisse_repere_max /2; //3/4 de la fenetre en x

	float x_size = 150, y_size = 33, yEspace = 2, yPos =(y_size+yEspace)*5/2 + y_size;
	Textures textures_menu;
	loadTexturesMenu(&textures_menu);

	menu[START_GAME]=createItem(center_x,(yPos=yPos-y_size - yEspace), x_size,y_size,1);
	menu[START_GAME].textures[0][1] = textures_menu.identifiants[TEXTURE_START_GAME_ON];
	menu[START_GAME].textures[0][0] = textures_menu.identifiants[TEXTURE_START_GAME_OFF];
	menu[START_GAME].on_off = 1;

	menu[MODE_JEU]=createItem(center_x, (yPos=yPos-y_size- yEspace) , x_size,y_size,2);
	menu[MODE_JEU].textures[0][1] = textures_menu.identifiants[TEXTURE_MODE_JEU_SOLO_ON];
	menu[MODE_JEU].textures[0][0] = textures_menu.identifiants[TEXTURE_MODE_JEU_SOLO_OFF];
	strcpy(menu[MODE_JEU].values[0], "solo");


	menu[MODE_JEU].textures[1][1] = textures_menu.identifiants[TEXTURE_MODE_JEU_MULTI_ON];
	menu[MODE_JEU].textures[1][0] = textures_menu.identifiants[TEXTURE_MODE_JEU_MULTI_OFF];
	strcpy(menu[MODE_JEU].values[1], "multi");


	menu[THEME]=createItem(center_x, (yPos=yPos-y_size- yEspace) , x_size,y_size,3);
	menu[THEME].textures[0][1] = textures_menu.identifiants[TEXTURE_THEME_MARIO_ON];
	menu[THEME].textures[0][0] = textures_menu.identifiants[TEXTURE_THEME_MARIO_OFF];
	strcpy(menu[THEME].values[0], "mario");

	menu[THEME].textures[1][1] = textures_menu.identifiants[TEXTURE_THEME_ESPACE_ON];
	menu[THEME].textures[1][0] = textures_menu.identifiants[TEXTURE_THEME_ESPACE_OFF];
	strcpy(menu[THEME].values[1], "espace");

	menu[THEME].textures[2][1] = textures_menu.identifiants[TEXTURE_THEME_FLAT_ON];
	menu[THEME].textures[2][0] = textures_menu.identifiants[TEXTURE_THEME_FLAT_OFF];
	strcpy(menu[THEME].values[2], "flat");


	menu[LEVEL]=createItem(center_x, (yPos=yPos-y_size- yEspace) , x_size,y_size,5);
	menu[LEVEL].textures[0][1] = textures_menu.identifiants[TEXTURE_LEVEL_CLASSIQUE_ON];
	menu[LEVEL].textures[0][0] = textures_menu.identifiants[TEXTURE_LEVEL_CLASSIQUE_OFF];
	strcpy(menu[LEVEL].values[0], "classique");

	menu[LEVEL].textures[1][1] = textures_menu.identifiants[TEXTURE_LEVEL_FULL_BONUS_ON];
	menu[LEVEL].textures[1][0] = textures_menu.identifiants[TEXTURE_LEVEL_FULL_BONUS_OFF];
	strcpy(menu[LEVEL].values[1], "full_bonus");

	menu[LEVEL].textures[2][1] = textures_menu.identifiants[TEXTURE_LEVEL_ARKANA_ON];
	menu[LEVEL].textures[2][0] = textures_menu.identifiants[TEXTURE_LEVEL_ARKANA_OFF];
	strcpy(menu[LEVEL].values[2], "arkana");

	menu[LEVEL].textures[3][1] = textures_menu.identifiants[TEXTURE_LEVEL_NO_BONUS_ON];
	menu[LEVEL].textures[3][0] = textures_menu.identifiants[TEXTURE_LEVEL_NO_BONUS_OFF];
	strcpy(menu[LEVEL].values[3], "no_bonus");


	menu[LEVEL].textures[4][1] = textures_menu.identifiants[TEXTURE_LEVEL_PONG_ON];
	menu[LEVEL].textures[4][0] = textures_menu.identifiants[TEXTURE_LEVEL_PONG_OFF];
	strcpy(menu[LEVEL].values[4], "pong");


	menu[QUIT]=createItem(center_x, (yPos=yPos-y_size- yEspace) , x_size,y_size,1);
	menu[QUIT].textures[0][1] = textures_menu.identifiants[TEXTURE_QUIT_ON];
	menu[QUIT].textures[0][0] = textures_menu.identifiants[TEXTURE_QUIT_OFF];

	menu[WALLPAPER]=createItem(0, 0 , abcisse_repere_max*2,ordonne_repere_max*2,3);
	menu[WALLPAPER].textures[0][1] = textures_menu.identifiants[TEXTURE_WALLPAPER_MARIO];
	menu[WALLPAPER].textures[1][1] = textures_menu.identifiants[TEXTURE_WALLPAPER_ESPACE];
	menu[WALLPAPER].textures[2][1] = textures_menu.identifiants[TEXTURE_WALLPAPER_FLAT];
	menu[WALLPAPER].on_off = 1;
}