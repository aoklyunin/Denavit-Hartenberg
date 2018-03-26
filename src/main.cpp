#include <GL/gl.h>
#include <GL/glut.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/ClaseOpenGL.h"


ClaseOpenGL *Miclase = NULL;

void glutTimer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, glutTimer, 100);
}

GLenum doubleBuffer;

GLubyte ubImage[65536];

static void Init(void)
{
    Miclase = new ClaseOpenGL;
    Miclase->inicializar();
    int j;
    GLubyte *img;
    GLsizei imgWidth = 128;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DITHER);

}

/* ARGSUSED1 */
static void Key(unsigned char key, int x, int y)
{
    float dtheta(3);

    switch (key) {
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


        case 97:

            Miclase->SSRMS.theta1 = Miclase->SSRMS.theta1 + dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta1, {0, 0, 2.5});     //b1
            Miclase->SSRMS.THList[2] = Miclase->SSRMS.THz;

            break;
        case 99:

            Miclase->SSRMS.theta1 = Miclase->SSRMS.theta1 - dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta1, {0, 0, 2.5});     //b1
            Miclase->SSRMS.THList[2] = Miclase->SSRMS.THz;


            break;

        case 100:

            Miclase->SSRMS.theta2 = Miclase->SSRMS.theta2 + dtheta;
            Miclase->SSRMS.AplicarTHz(Miclase->SSRMS.theta2, {0, 0, 6});  //b2
            Miclase->SSRMS.THList[4] = Miclase->SSRMS.THz;

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


        case 'A':Miclase->thetaCamera = Miclase->thetaCamera + 0.05;

            break;
        case 'D':Miclase->thetaCamera = Miclase->thetaCamera - 0.05;

            break;

        case 'W':Miclase->phiCamera = Miclase->phiCamera + 0.05;

            break;
        case 'S':Miclase->phiCamera = Miclase->phiCamera - 0.05;

            break;

    }
}


static void Draw(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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
    glutTimerFunc(100, glutTimer, 100);
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}



