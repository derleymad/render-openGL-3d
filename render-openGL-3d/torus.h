#ifndef TORUS_H
#define TORUS_H

typedef struct {
   float x, y, z;
   float radiusInner, radiusOuter;
   float red, green, blue;
} Torus;

void drawTorus(Torus* torus);

#endif
