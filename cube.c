#include <GL/glut.h>
#include "cube.h"

void drawCube(Cube* cube) {
   glColor3f(cube->red, cube->green, cube->blue);
   glPushMatrix();
   glTranslatef(cube->x, cube->y, cube->z);
   glScalef(cube->width, cube->height, cube->depth);
   glutSolidCube(1.0f);
   glPopMatrix();
}
