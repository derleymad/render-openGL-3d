#include <GL/glut.h>
#include "sphere.h"

void drawSphere(Sphere* sphere) {
   glColor3f(sphere->red, sphere->green, sphere->blue);
   glPushMatrix();
   glTranslatef(sphere->x, sphere->y, sphere->z);
   glutSolidSphere(sphere->radius, 20, 20);
   glPopMatrix();
}
