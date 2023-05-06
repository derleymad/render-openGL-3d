#ifndef SPHERE_H
#define SPHERE_H

typedef struct {
   float x, y, z;
   float radius;
   float red, green, blue;
} Sphere;

void drawSphere(Sphere* sphere);

#endif
