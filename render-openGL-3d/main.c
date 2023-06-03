#include <GL/glut.h>
#include "cube.h"
#include "sphere.h"
#include "teapot.h"
#include "torus.h"

float cameraX = 3.0;
float cameraY = 4.0;
float cameraZ = 6.0;

float windowWidth = 800.0;
float windowHeight = 600.0;

// Variáveis para armazenar a posição anterior do mouse
int lastMouseX = 0;
int lastMouseY = 0;

//Armazena a posição da câmera
float cameraPointX = 0.0;
float cameraPointY = 0.0;

float lookAtX = 0.0;
float lookAtY = 0.0;
float lookAtZ = 0.0;

int mouseX = 0;
int mouseY = 0;

//Cria objetos
Cube *ground; //chao
Cube *wall1; //parede esquerda
Cube *wall3; //parede direita
Teapot *teapot; //bule
Torus *torus; //toro
Sphere *sphere; //esfera

void createGround(Cube *ground)
{
    ground->x = 0.0f;
    ground->y = -1.0f;
    ground->z = 0.0f;
    ground->width = 10.0f;
    ground->height = 0.1f;
    ground->depth = 10.0f;
    ground->red = 1.0f;
    ground->green = 0.0f;
    ground->blue = 0.0f;
    drawCube(ground);
}

void createWalls(Cube *wall1,Cube *wall3)
{
    wall1->x = -5.0f;
    wall1->y = 0.0f;
    wall1->z = 0.0f;
    wall1->width = 0.1f;
    wall1->height = 2.0f;
    wall1->depth = 10.0f;
    wall1->red = 1.0f; //vermelho
    wall1->green = 0.0f;
    wall1->blue = 0.0f;
    drawCube(wall1);

    wall3->x = 0.0f;
    wall3->y = 0.0f;
    wall3->z = -5.0f;
    wall3->width = 10.0f;
    wall3->height = 2.0f;
    wall3->depth = 0.1f;
    wall3->red = 1.0f; //vermelho
    wall3->green = 0.0f;
    wall3->blue = 0.0f;
    drawCube(wall3);
}

void createTeaPot(Teapot *teapot)
{
    teapot->x = -4.0f;
    teapot->y = 0.0f;
    teapot->z = 2.0f;
    teapot->scale = 1.0f;
    teapot->rotation = 60.0f;
    teapot->red = 0.0f;
    teapot->green = 0.0f;
    teapot->blue = 1.0f; //azul
    drawTeapot(teapot);
}

void createTorus(Torus *torus)
{
    torus->x = 2.0f;
    torus->y = 0.0f;
    torus->z = 0.0f;
    torus->radiusInner = 0.2f;
    torus->radiusOuter = 1.0f;
    torus->red = 0.0f;
    torus->green = 1.0f;
    torus->blue = 0.0f; //azul
    drawTorus(torus);
}

void createSphere(Sphere *sphere)
{
    sphere->x = -3.0f;
    sphere->y = 0.0f;
    sphere->z = -3.0f;
    sphere->radius = 1.0f;
    sphere->red = 1.0f; //laranja
    sphere->green = 0.5f;
    sphere->blue = 0.0f;
    drawSphere(sphere);
}

void mouseMotion(int x, int y)
{
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

void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        lastMouseX = x;
        lastMouseY = y;
        glutMotionFunc(mouseMotion);
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        glutMotionFunc(NULL);
    }

    if (button == 3)
    {
        cameraZ -= 0.1;  // Zoom in
    }
    else if (button == 4)
    {
        cameraZ += 0.1;  // Zoom out
    }

    glutPostRedisplay();

}

void mouseWheel(int wheel, int direction, int x, int y)
{
    if (direction > 0)
    {
        cameraZ -= 0.1;  // Zoom in
    }
    else
    {
        cameraZ += 0.1;  // Zoom out
    }
    mouseX = x;
    mouseY = y;

    glutPostRedisplay();
}

//Iluminação
void lighting(){
    //posicao da lus (tipo um ponto de iluminacao com a vela)
    GLfloat lightPosition[] = { 0.0, 1.0, 0.0, 0.0 };
    //luz global (tipo o brilho da tela)
    GLfloat ambientLight[] = { 0.1, 0.1, 0.1, 1.0 };
    //reflexao dos objetos (difusa)
    GLfloat diffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
    //para deixar liso e polido
    GLfloat specularLight[] = { 0.0, 1.0, 0.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

    //Iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0); // define a cor de fundo
    glEnable(GL_DEPTH_TEST); // habilita teste de profundidade
    glEnable(GL_COLOR_MATERIAL); // habilita a cor nos objetos
    glMatrixMode(GL_PROJECTION); // define quea matriz é de projeção
    glLoadIdentity(); // carrega a matriz identidade
    /*4 primeiros parâmetros são as coordenadas da janela de recorte
    e os 2 últimos as distâncias para os planos de recorte near/far*/
    // Não consigo definir o glOrtho
    //glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Perspectiva
    gluPerspective(45.0, windowWidth/windowHeight, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW); // define que a matriz é a model view
    glLoadIdentity();

    //Posicionamento da câmera
    gluLookAt(cameraX,cameraY,cameraZ,   // posição da câmera
              lookAtX, lookAtY, lookAtZ,   // onde a camera esta apontando
              0.0, 1.0, 0.0);  // vetor view-up

    //Adiciona a iluminação
    lighting();

    //Desenha os objetos
    createGround(&ground);
    createTorus(&torus);
    createWalls(&wall1, &wall3);
    createSphere(&sphere);
    createTeaPot(&teapot);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); //Inicializa o glut
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); //Configura o modo de display
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Cena bule, bola e toro");

    glutMouseFunc(mouse);

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

