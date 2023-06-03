#include <GL/glut.h>

// ----------- variaveis para controlar o angulo de cada bule --------------
int width = 400;
int height = 400;
float angle = 0.0f;  // Ângulo de rotação do bule

void displayXY()
{
    glLoadIdentity();
    glViewport(0, 200, 200, 200);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.65f, 0.0f); //red
    glutSolidTeapot(5.0f);
}

void displayYZ()
{
    glLoadIdentity();
    glViewport(200, 200, 200, 200);
    gluLookAt(15.0f, 0.0f, -1.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.65f, 0.0f); //segundo
    glutSolidTeapot(5.0f);
}

void displayXZ()
{
    glLoadIdentity();
    glViewport(0, 0, 200, 200);
    gluLookAt(0.0f, 15.0f, 0.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, -1.0f); //vetor "up" apontando para baixo para ver de cima
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.65f, 0.0f);//terceiro
    glutSolidTeapot(5.0f);
}


void displayPerspective()
{
    glLoadIdentity();
    glViewport(200, 0, 200, 200);
    gluPerspective(10.0f, 1.0f, -20.0f, 20.0f);
    gluLookAt(9.0f, 10.0f, 1.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.65f, 0.0f);
    glutSolidTeapot(5.0f);
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

void lighting()
{
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

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // define a cor de fundo
    glEnable(GL_DEPTH_TEST); // habilita teste de profundidade
    glEnable(GL_COLOR_MATERIAL); // habilita a cor nos objetos
    glMatrixMode(GL_PROJECTION); // define quea matriz é de projeção
    glLoadIdentity(); // carrega a matriz identidade
    glOrtho(-15.0, 15.0, -15.0, 15.0, -20.0, 20.0);

    lighting();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); // define que a matriz é a model view

    displayXY();
    displayXZ();
    displayYZ();
    displayPerspective();

    glutSwapBuffers();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv); //Inicializa o glut
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Configura o modo de display
    glutInitWindowSize(400, 400);
    glutCreateWindow("Renderização com Viewports");

    glutTimerFunc(0, update, 0);

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 1;
}
