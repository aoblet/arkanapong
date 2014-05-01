#include "utils/dessin_utils.h"
#include <GL/gl.h>
#include <math.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

void dessinCercleCanonique(){
	int i =0;
	double rayon_rotation = (double) (2*PI)/40;
	glBegin(GL_POLYGON);
	for(;i<40;i++){
		glVertex2f(0.5*cos(rayon_rotation*i),0.5*sin(rayon_rotation*i));
	}
	glEnd();
}

void dessinCarreCanonique(){
	glBegin(GL_POLYGON);
		glVertex2f(-0.5,-0.5);
		glVertex2f(0.5,-0.5);
		glVertex2f(0.5,0.5);
		glVertex2f(-0.5,0.5);
	glEnd();
}