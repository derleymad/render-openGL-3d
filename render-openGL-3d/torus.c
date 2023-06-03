#include <GL/glut.h>
#include "torus.h"

void drawTorus(Torus* torus) {

   glColor3f(torus->red, torus->green, torus->blue);
   glPushMatrix();
   glRotatef(90.0f,torus->x,torus->y,torus->z);
   glTranslatef(torus->x, torus->y, torus->z);
   glutSolidTorus(torus->radiusInner, torus->radiusOuter, 50, 50);

   glPopMatrix();
}
