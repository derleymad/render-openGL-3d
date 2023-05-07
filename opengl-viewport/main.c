#include <GL/glut.h>

// ----------- variaveis para controlar o angulo de cada bule --------------
float angle = 0.0f;
float angleXY = 0.0f;
float angleXZ = 0.0f;
float angleYZ = 0.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);

//------------ iluminação -------------------------------------------------

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

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

    //perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);

    // camera para viewport perspectiva
    glViewport(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT));
        glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0f, 5.0f, 5.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    //desenha bule na perspectiva
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);  // Cor vermelha
    glutSolidTeapot(1.0f);
    glPopMatrix();


    //projecao
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -10.0f, 10.0f);    //projecao ortogonal

    // outras viewports
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //viewport XY
    glViewport(0, glutGet(GLUT_WINDOW_HEIGHT) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    glPushMatrix();
    glRotatef(angleXY, 0.0f, 1.0f, 0.0f);  //eixo y
    glColor3f(0.0f, 1.0f, 0.0f);  // verde
    glutSolidTeapot(1.0f);
    glPopMatrix();

    // viewport XZ
    glViewport(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    glPushMatrix();
    glRotatef(angleXZ, 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);  // azul
    glutSolidTeapot(1.0f);
    glPopMatrix();

    //viewport YZ
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    glPushMatrix();
    glRotatef(angleYZ, 0.0f, 1.0f, 0.0f);  // eixo z
    glColor3f(1.0f, 1.0f, 0.0f);  //amarelo
    glutSolidTeapot(1.0f);
    glPopMatrix();

    // atualiza cada angulo para cada bule (ver funcao update)
    angle += 0.5f;  // viewport perspectiva
    angleXY += 1.0f;  //  viewport XY
    angleXZ += 1.5f;  // viewport XZ
    angleYZ += 2.0f;  //viewport YZ

    // Trocar os buffers para exibir a cena
    glutSwapBuffers();
}


// funcao para atualizar valores (para animação)
void update(int value) {

    angle += 0.5f;
    angleXY += 1.0f;
    angleXZ += 1.5f;
    angleYZ += 2.0f;

    glutPostRedisplay();

    //glutTimerFunc(16, timerFunc, 0);  // 16 ms -> 60 fps (se for usar diminuir a incrementacao do aungulo pq fica mt rapido)

    // (30 FPS)
    glutTimerFunc(1000 / 30, update, 0);
}

int main(int argc, char** argv) {
    // criacao da janela
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Renderização com Viewports");

    glutDisplayFunc(display);

    //glutDisplayFunc(drawViewportXZ);

    glutTimerFunc(0, update, 0);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 1;

    }
