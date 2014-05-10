#ifndef __MENU_H__
#define __MENU_H__
#include <GL/gl.h>

typedef struct Item_menu{
	float xPos;
	float yPos;
	float xSize;
	float ySize;
	GLuint textures[10][2]; //2d -> on_off
	int nb_elements;
	int indice_courant;
	int on_off;
	char values[10][50];
}Item_menu;

Item_menu createItem(float xPos, float yPos, float xSize, float ySize,int nb_elements);


#endif