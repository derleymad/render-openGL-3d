#include <GL/glut.h>

// ----------- variaveis para controlar o angulo de cada bule --------------
int width = 400;
int height = 400;
float angle = 0.0f;  // Ângulo de rotação do bule

void displayXY()
{
    glViewport(0, 200, 200, 200);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15.0, 15.0, -15.0, 15.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.65f, 0.0f); //red
    glutSolidTeapot(5.0f);
}

void displayYZ()
{
    glViewport(200, 200, 200, 200);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15.0, 15.0, -15.0, 15.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.65f, 0.0f); //segundo
    glutSolidTeapot(5.0f);
}

void displayXZ()
{
    glViewport(0, 0, 200, 200);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15.0, 15.0, -15.0, 15.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 15.0f, 0.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, -1.0f); //vetor "up" apontando para baixo para ver de cima
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.65f, 0.0f);//terceiro
    glutSolidTeapot(5.0f);
}


void displayPerspective()
{
    glViewport(200, 0, 200, 200);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15.0, 15.0, -15.0, 15.0, -20.0, 20.0);

    //gluPerspective(100.0f, 1.0f, 1.0f, 10.0f); //n muda isso
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 2.0f, 5.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.65f, 0.0f); //perspectiva
    glutSolidTeapot(5.0f);
}

void enableLight()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};    // Reflexão difusa
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};   // Reflexão especular
    GLfloat mat_shininess[] = {100.0f};                  // Brilho especular

    GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};   // Luz ambiente
    GLfloat light_diffuse[] = {1.f, 1.0f, 1.0f, 1.0f};   // Luz difusa
    GLfloat light_specular[] = {1.0f, 1.f, 1.0f, 1.0f};  // Luz especular
    GLfloat light_position[] = {1.0f, 1.0f, 1.0f, 0.0f};  // Posição da luz

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);


    // Habilitar a iluminação
    glEnable(GL_LIGHTING);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);

    enableLight(); // e se fez a luz

    //desenha os bules em cada perspectiva
    //drawViewportBorders();
    displayXY();
    displayXZ();
    displayYZ();

    displayPerspective(); //o capeta

    glutSwapBuffers();
}


void update(int value)
{
    angle += 1.0f;
    if (angle > 360.0f)
    {
        angle -= 360.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}


// funcao para atualizar valores (para animação)


int main(int argc, char** argv)
{
    // criacao da janela
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Renderização com Viewports");

    glutDisplayFunc(display);

    //glutDisplayFunc(drawViewportXZ);

    glutTimerFunc(0, update, 0);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 1;

}
