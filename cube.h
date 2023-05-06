#ifndef CUBE_H
#define CUBE_H

typedef struct {
   float x, y, z;
   float width, height, depth;
   float red, green, blue;
} Cube;


void drawCube(Cube* cube);

#endif
