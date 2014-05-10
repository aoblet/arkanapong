#include "game/menu.h"

Item_menu createItem(float xPos, float yPos, float xSize, float ySize,int nb_elements){
	Item_menu item;
	item.xPos = xPos;
	item.yPos = yPos;
	item.xSize = xSize;
	item.ySize = ySize;
	item.nb_elements = nb_elements;
	item.indice_courant = 0;
	item.on_off = 0;
	return item;
}