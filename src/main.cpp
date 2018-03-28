#include <GL/gl.h>
#include <GL/glut.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/ClaseOpenGL.h"
#include "../include/Camera.h"
#include "../include/traces.h"


ClaseOpenGL *Miclase = NULL;

Camera camera = Camera();

double prevX = 10000;

double prevY = 10000;

void glutTimer(int value)
{
    // glutPostRedisplay();
    glutTimerFunc(100, glutTimer, 100);
}

void motionFunc(int x, int y)
{
    if (prevX == 10000) {
        prevX = x;
    }
    if (prevY == 10000) {
        prevY = y;
    }
    double dX = x - prevX;
    double dY = y - prevY;
    prevX = x;
    prevY = y;

    camera.rotateX(-dX / 50);

    camera.rotateY(-dY / 50);
    glutPostRedisplay();

}

GLenum doubleBuffer;

double positions[10][3];

static void Init(void)
{
    /* initialize random seed: */
    srand(time(NULL));

    Miclase = new ClaseOpenGL;
    Miclase->inicializar();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DITHER);

    for (int i = 0; i < 10; i++) {
        positions[i][0] = (rand() % 1000 - 500) / 20;
        positions[i][1] = (rand() % 1000 - 500) / 20;
        positions[i][2] = (rand() % 1000 - 500) / 20;
    }

}

/* ARGSUSED1 */
static void Key(unsigned char key, int x, int y)
{
    float dtheta(3);
   // std::cout << (int) key << std::endl;

    double delta = 0.1;

    switch (key) {
        case 27:

            break;

        case 97 :camera.moveLeft(delta); glutPostRedisplay();
            break;
        case 100 :camera.moveRight(delta); glutPostRedisplay();
            break;

        case 119:camera.moveForward(delta); glutPostRedisplay();

            break;
        case 115:camera.moveBack(delta); glutPostRedisplay();
            break;

        case 'R':

            Miclase->SSRMS.theta4 = Miclase->SSRMS.theta4 + dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta4, {0, 0, 1});   //b4
            Miclase->SSRMS.THList[8] = Miclase->SSRMS.THz;


            break;

        case 'Y':

            Miclase->SSRMS.theta4 = Miclase->SSRMS.theta4 - dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta4, {0, 0, 1});   //b4
            Miclase->SSRMS.THList[8] = Miclase->SSRMS.THz;


            break;


        case 'F':Miclase->SSRMS.theta5 = Miclase->SSRMS.theta5 + dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta5, {0, 0, 6});    //b5
            Miclase->SSRMS.THList[10] = Miclase->SSRMS.THz;
            break;

        case 'H':

            Miclase->SSRMS.theta5 = Miclase->SSRMS.theta5 - dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta5, {0, 0, 6});     //b5
            Miclase->SSRMS.THList[10] = Miclase->SSRMS.THz;


            break;

        case 'V':Miclase->SSRMS.theta6 = Miclase->SSRMS.theta6 + dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta6, {0, 0, 6});     //b6
            Miclase->SSRMS.THList[12] = Miclase->SSRMS.THz;
            break;

        case 'N':

            Miclase->SSRMS.theta6 = Miclase->SSRMS.theta6 - dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta6, {0, 0, 6});      //b6
            Miclase->SSRMS.THList[12] = Miclase->SSRMS.THz;
            break;

        case 'G':Miclase->SSRMS.theta7 = Miclase->SSRMS.theta7 - dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta7, {0, 0, 0});     //b7, efector final
            Miclase->SSRMS.THList[14] = Miclase->SSRMS.THz;
            break;


        case 99:

            Miclase->SSRMS.theta1 = Miclase->SSRMS.theta1 - dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta1, {0, 0, 2.5});     //b1
            Miclase->SSRMS.THList[2] = Miclase->SSRMS.THz;


            break;


        case 102:

            Miclase->SSRMS.theta2 = Miclase->SSRMS.theta2 - dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta2, {0, 0, 6});     //b2
            Miclase->SSRMS.THList[4] = Miclase->SSRMS.THz;


            break;

        case 103:

            Miclase->SSRMS.theta3 = Miclase->SSRMS.theta3 + dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta3, {0, 0, 6});     //b3
            Miclase->SSRMS.THList[6] = Miclase->SSRMS.THz;

            break;
        case 105:

            Miclase->SSRMS.theta3 = Miclase->SSRMS.theta3 - dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta3, {0, 0, 6});       //b3
            Miclase->SSRMS.THList[6] = Miclase->SSRMS.THz;

            break;

    }
}

static void Draw(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    Vector3d center = camera.getCenter();
    Vector3d eye = camera.getEye();
    Vector3d up = camera.getUp();

    //std::cout << eye(0) << " " << eye(1) << " " << eye(2) << std::endl;

    gluLookAt(eye(0), eye(1), eye(2),
              center(0), center(1), center(2),
              up(0), up(1), up(2));

    info_msg(center);
    info_msg(eye);

    for (auto &position : positions) {
        glPushMatrix();
        glTranslated(position[0], position[1], position[2]);
        glutSolidSphere(1.0, 50, 50);
        glPopMatrix();
    }

    if (doubleBuffer) {
        glutSwapBuffers();
    }
    else {
        glFlush();
    }
}

static void Args(int argc, char **argv)
{
    GLint i;

    doubleBuffer = GL_TRUE;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-sb") == 0) {
            doubleBuffer = GL_FALSE;
        }
        else if (strcmp(argv[i], "-db") == 0) {
            doubleBuffer = GL_TRUE;
        }
    }
}

int main(int argc, char **argv)
{
    GLenum type;

    glutInit(&argc, argv);
    Args(argc, argv);

    type = GLUT_RGB;
    type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
    glutInitDisplayMode(type);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1600, 800);
    glutCreateWindow("ABGR extension");
    if (!glutExtensionSupported("GL_EXT_abgr")) {
        printf("Couldn't find abgr extension.\n");
        exit(0);
    }
#if !GL_EXT_abgr
    printf("WARNING: client-side OpenGL has no ABGR extension support!\n");
    printf("         Drawing only RGBA (and not ABGR) images and textures.\n");
#endif
    Init();
    glutKeyboardFunc(Key);
    glutDisplayFunc(Draw);
    glutPassiveMotionFunc(motionFunc);
    glutTimerFunc(100, glutTimer, 100);
    glutMainLoop();
    return 0;
    /* ANSI C requires main to return int. */
}



