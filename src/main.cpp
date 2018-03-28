#include <GL/gl.h>
#include <GL/glut.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/Robot.h"
#include "../include/Camera.h"
#include "../include/traces.h"
#include "../include/OpenGLWrapper.h"


Camera camera;

Robot SSRMS;

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

static void Init(void)
{
    /* initialize random seed: */
    srand(time(NULL));

    glClearColor(1, 1, 1, 1);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);                    // hidden surface removal
    glShadeModel(GL_SMOOTH);                    // use smooth shading
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_COLOR_MATERIAL);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DITHER);

    camera = Camera(Vector3d(-7.6, -51.0, 12.0),
                    Vector3d(-0.25, -0.950767, 0).normalized(),
                    Vector3d(0, 0, 1));

    SSRMS.inicializar();///cargar modelos
    SSRMS.configurarTH();///Posiciones de las piezas


}

/* ARGSUSED1 */
static void Key(unsigned char key, int x, int y)
{
    float dtheta(3);
    std::cout << (int) key << std::endl;

    double deltaPos = 1;

    switch (key) {
        case 27:

            break;

        case 97 :camera.moveLeft(deltaPos);
            break;
        case 100 :camera.moveRight(deltaPos);
            break;

        case 119:camera.moveForward(deltaPos);

            break;
        case 115:camera.moveBack(deltaPos);

            break;

        case 49:

            SSRMS.theta4 = SSRMS.theta4 + dtheta;
            SSRMS.AplicarTHz(SSRMS.theta4, {0, 0, 1});   //b4
            SSRMS.THList[8] = SSRMS.THz;


            break;

        case 50:

            SSRMS.theta4 = SSRMS.theta4 - dtheta;
            SSRMS.AplicarTHz(SSRMS.theta4, {0, 0, 1});   //b4
            SSRMS.THList[8] = SSRMS.THz;


            break;


        case 51:SSRMS.theta5 = SSRMS.theta5 + dtheta;
            SSRMS.AplicarTHz(SSRMS.theta5, {0, 0, 6});    //b5
            SSRMS.THList[10] = SSRMS.THz;
            break;

        case 52:

            SSRMS.theta5 = SSRMS.theta5 - dtheta;
            SSRMS.AplicarTHz(SSRMS.theta5, {0, 0, 6});     //b5
            SSRMS.THList[10] = SSRMS.THz;


            break;

        case 53:SSRMS.theta6 = SSRMS.theta6 + dtheta;
            SSRMS.AplicarTHz(SSRMS.theta6, {0, 0, 6});     //b6
            SSRMS.THList[12] = SSRMS.THz;
            break;

        case 54:

            SSRMS.theta6 = SSRMS.theta6 - dtheta;
            SSRMS.AplicarTHz(SSRMS.theta6, {0, 0, 6});      //b6
            SSRMS.THList[12] = SSRMS.THz;
            break;

        case 55:SSRMS.theta7 = SSRMS.theta7 - dtheta;
            SSRMS.AplicarTHz(SSRMS.theta7, {0, 0, 0});     //b7, efector final
            SSRMS.THList[14] = SSRMS.THz;
            break;


        case 56:

            SSRMS.theta1 = SSRMS.theta1 - dtheta;
            SSRMS.AplicarTHz(SSRMS.theta1, {0, 0, 2.5});     //b1
            SSRMS.THList[2] = SSRMS.THz;


            break;


        case 57:

            SSRMS.theta2 = SSRMS.theta2 - dtheta;
            SSRMS.AplicarTHz(SSRMS.theta2, {0, 0, 6});     //b2
            SSRMS.THList[4] = SSRMS.THz;


            break;

        case 58:

            SSRMS.theta3 = SSRMS.theta3 + dtheta;
            SSRMS.AplicarTHz(SSRMS.theta3, {0, 0, 6});     //b3
            SSRMS.THList[6] = SSRMS.THz;

            break;
        case 59:

            SSRMS.theta3 = SSRMS.theta3 - dtheta;
            SSRMS.AplicarTHz(SSRMS.theta3, {0, 0, 6});       //b3
            SSRMS.THList[6] = SSRMS.THz;

            break;

    }
    glutPostRedisplay();
}

static void Draw(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    Vector3d center = camera.getCenter();
    Vector3d eye = camera.getEye();
    Vector3d up = camera.getUp();


    gluLookAt(eye(0), eye(1), eye(2),
              center(0), center(1), center(2),
              up(0), up(1), up(2));


    OpenGLWrapper::Drawarrow3D({0, 0, 0}, {100, 0, 0}, {1, 0.0, 0.0}, 0.03, 1);
    OpenGLWrapper::Drawarrow3D({0, 0, 0}, {0, 100, 0}, {0.0, 1, 0.0}, 0.03, 1);
    OpenGLWrapper::Drawarrow3D({0, 0, 0}, {0, 0, 100}, {0.0, 0.0, 1}, 0.03, 1);

/// //////////////////////////// PARTES A AGREGAR
    // SSRMS.renderizar();

    if (doubleBuffer) {
        glutSwapBuffers();
    }
    else {
        glFlush();
    }
}

void Reshape(int width, int height)
{

    glViewport(0, 0, width, height);        // reset the viewport to new dimensions
    glMatrixMode(GL_PROJECTION);            // set projection matrix current matrix
    glLoadIdentity();                        // reset projection matrix
    // calculate aspect ratio of window
    gluPerspective(52.0f, (GLdouble) width / (GLdouble) height, 1.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);                // set modelview matrix
    glLoadIdentity();                        // reset modelview matrix
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
    glutReshapeFunc(Reshape);
    glutPassiveMotionFunc(motionFunc);
    glutTimerFunc(100, glutTimer, 100);
    glutMainLoop();
    return 0;
    /* ANSI C requires main to return int. */
}




