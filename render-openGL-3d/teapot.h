#ifndef TEAPOT_H
#define TEAPOT_H

typedef struct {
    float x,y,z;
    float scale;
    float rotation;
    float red,green,blue;
} Teapot;

void drawTeapot(Teapot* teapot);

#endif
