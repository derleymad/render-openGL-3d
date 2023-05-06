#include <GL/glut.h>
#include "objetos.c"

int windowWidth = 800;
int windowHeight = 600;
// Variáveis para armazenar a posição anterior do mouse
int lastMouseX = 0;
int lastMouseY = 0;

// Variáveis para armazenar a posição da câmera
float cameraX = 3.0;
float cameraY = 4.0;
float cameraZ = 6.0;

float cameraPointX=0.0;
float cameraPointY=0.0;

  float lookAtX = 0.0;
    float lookAtY =0.0;
    float lookAtZ = 0.0;

int mouseX = 0;
int mouseY = 0;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glEnable(GL_COLOR_MATERIAL);

    // perspectiva
   gluPerspective(45.0, 800.0/600.0, 0.1, 100.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();


     //lookAtX = cameraX - ((mouseX / windowWidth) - 0.5);
     //lookAtY = cameraY + ((mouseY / windowHeight) - 0.5);
    // lookAtZ = cameraZ - 1.0;  // Distância do ponto de visualização à câmera

    //posicionamento
   gluLookAt(cameraX,cameraY,cameraZ,   // camera pos. //horizont, vertical  //zoom (3,4,6)
             lookAtX, lookAtY, lookAtZ,   // ponto de foco (onde a camera esta olhando eu acho)
             0.0, 1.0, 0.0);  // vetor orientacao n sei (up)
    //iluminação
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   //posicao da lus (tipo um ponto de iluminacao com a vela)
   GLfloat lightPosition[] = { 0.0, 1.0, 0.0, 0.0 };

   //luz global (tipo o brilho da tela)
   GLfloat ambientLight[] = { 0.0, 1.0, 0.0, 1.0 };

   //reflexao dos objetos (difusa)
   GLfloat diffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };

   //para deixar liso e polido
   GLfloat specularLight[] = { 0.0, 1.0, 0.0, 1.0 };

   glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);


   //BULE
   glColor3f(0.0f, 0.0f, 1.0f);  //azul
   glTranslatef(-1.0f, 1.0f, 0.0f);
   glutSolidTeapot(1);


   //BOLA
   glColor3f(1.0, 0.5, 0.0);  //laranja
   glTranslatef(0.0f, 0.0f, -2.0f);
   glutSolidSphere(1, 20, 20);

   //TORO
   glColor3f(0.0, 0.5, 0.0);  //verde
   glTranslatef(2.0f, 0.0f, 0.0f);
   //glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
                //(espessura, tamanho , nsei, nsei)
   glutSolidTorus(0.15, 0.5, 50, 50);

    //chao
    glColor3f(1.0f, 0.0f, 0.0f); //vermelho
    glPushMatrix();
    glTranslatef(-1.0f, -1.0f, 0.0f); //abaixo da origem
    glScalef(6.0f, 0.1f, 6.0f); //dimensoes
    glutSolidCube(1.0f);
    glPopMatrix();

    //paredes esquerda
    //glColor3f(GLUT_RED);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-4.0f, 0.0f, 0.0f); //joga para esquerda
    glScalef(0.1f, 2.0f, 6.0f); // dimensoes
    glutSolidCube(1.0f);
    glPopMatrix();

    //glPushMatrix();
    //glTranslatef(5.0f, 0.0f, 0.0f); // joga a direita
    //glScalef(0.1f, 2.0f, 10.0f); // dimensoes
    //glutSolidCube(1.0f);
    //glPopMatrix();

    //parede trazeira
    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, -3.0f); // trazeira
    glScalef(6.0f, 2.0f, 0.1f); //dimensoes
    glutSolidCube(1.0f);
    glPopMatrix();


   glFlush();
   glutSwapBuffers();
}

void mouseMotion(int x, int y) {
    // Calcula a diferença entre a posição atual do mouse e a posição anterior
    int deltaX = x - lastMouseX;
    int deltaY = y - lastMouseY;

    // Atualiza a posição da câmera com base nos movimentos do mouse
    cameraX += deltaX * 0.01;
    cameraY -= deltaY * 0.01;  // Inverte o sinal para mover na direção desejada

    // Atualiza a posição anterior do mouse para a próxima chamada da função
    lastMouseX = x;
    lastMouseY = y;

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
        glutMotionFunc(mouseMotion);
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        glutMotionFunc(NULL);
    }

    if (button == 3) {
        cameraZ -= 0.1;  // Zoom in
    } else if (button == 4) {
        cameraZ += 0.1;  // Zoom out
    }



    glutPostRedisplay();

}

void mouseWheel(int wheel, int direction, int x, int y) {
    if (direction > 0) {
        cameraZ -= 0.1;  // Zoom in
    } else {
        cameraZ += 0.1;  // Zoom out
    }
    mouseX = x;
    mouseY = y;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(windowWidth, windowHeight);
   glutCreateWindow("Cena bule,bola e toro");

   glEnable(GL_DEPTH_TEST);  //teste de profundidade

   glutDisplayFunc(display);


   glutMouseFunc(mouse);
   glutMainLoop();

   return 0;
}
