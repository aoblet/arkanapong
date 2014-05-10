#ifndef __MASTER_LAUNCHER_H__
#define __MASTER_LAUNCHER_H__
#define START_GAME 0
#define MODE_JEU 1
#define THEME 2
#define LEVEL 3
#define QUIT 4
#define WALLPAPER 5
#include "game/menu.h"
#include "textures/textures.h"

void genereMenu(Item_menu * menu, Textures * textures_menu, float abcisse_repere_max, float ordonne_repere_max); // abcisse et ordonnées pour orga des positions
void handleItem(int * indice_item_inside, int indice_menu, Item_menu * item,Item_menu * menu);
void handleMenu(int * indice_menu, int * indice_item,  Item_menu * menu, int nb_items_menu);
void drawItem(Item_menu * item, float abcisse_repere_max, float ordonne_repere_max );

#endif