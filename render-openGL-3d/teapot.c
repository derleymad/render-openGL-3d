#include <GL/glut.h>
#include "teapot.h"

void drawTeapot(Teapot* teapot) {
    glColor3f(teapot->red, teapot->green, teapot->blue);
    glPushMatrix();
    glTranslatef(teapot->x, teapot->y, teapot->z);
    glRotatef(teapot->rotation, 0.0f, 1.0f, 0.0f);
    glutSolidTeapot(1.0f);
    glPopMatrix();
}
