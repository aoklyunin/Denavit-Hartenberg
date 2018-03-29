#include <GL/gl.h>
#include <GL/glut.h>

#include <string.h>
#include <stdio.h>
#include "../include/openGL_wrapper.h"
#include "../include/robot.h"


Camera camera;

Robot robot;

int clientWidth = 1600;

int clientHeight = 1080;

std::string dh_file_path;

int prevPosX = 10000;

int prevPosY = 10000;

void glutTimer(int value)
{
    // glutPostRedisplay();
    glutTimerFunc(100, glutTimer, 100);
}

void motionFunc(int x, int y)
{
    if (prevPosX == 10000) {
        prevPosX = x;
    }
    if (prevPosY == 10000) {
        prevPosY = y;
    }

    double dX = x - prevPosX;
    double dY = y - prevPosY;

    prevPosX = x;
    prevPosY = y;

    camera.rotateX(-dX / 50);
    camera.rotateY(-dY / 50);


    //glutWarpPointer(clientWidth / 2, clientHeight / 2);

    info_msg(dX, " ", dY, " ");


    glutPostRedisplay();

}

GLenum doubleBuffer;

static void Init(std::string dh_file_path)
{
    srand(time(NULL));

    glClearColor(1, 1, 1, 1);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);                    // hidden surface removal
    glShadeModel(GL_SMOOTH);                    // use smooth shading
    //glEnable(GL_LIGHTING);


    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DITHER);

    camera = Camera(Vector3d(100, 100.0, 12.0),
                    Vector3d(0.5, 0.5, 0).normalized(),
                    Vector3d(0, 0, 1));

    robot.inicializar();
    robot.configurarTH(dh_file_path);

}
static void Key(unsigned char key, int x, int y)
{

    double deltaPos = 1;
    double deltaAlpha = 0.1;

    //info_msg((int)key);

    switch (key) {
        case 27:exit(0);
            break;

        case 97 :camera.moveLeft(deltaPos);
            break;
        case 100 :camera.moveRight(deltaPos);
            break;

        case 119:camera.moveForward(deltaPos);

            break;
        case 115:camera.moveBack(deltaPos);

            break;

        case 49:robot.rotateLink(0, deltaAlpha);

            break;

        case 50:robot.rotateLink(0, -deltaAlpha);

            break;


        case 51:robot.rotateLink(1, deltaAlpha);

            break;

        case 52:robot.rotateLink(1, -deltaAlpha);

            break;

        case 53:robot.rotateLink(2, deltaAlpha);

            break;

        case 54:robot.rotateLink(2, -deltaAlpha);

            break;

        case 55:robot.rotateLink(3, deltaAlpha);

            break;

        case 56:robot.rotateLink(3, -deltaAlpha);

            break;

        case 57:robot.rotateLink(4, deltaAlpha);

            break;

        case 48:robot.rotateLink(4, -deltaAlpha);

            break;

        case 45:robot.rotateLink(5, deltaAlpha);

            break;

        case 61:robot.rotateLink(5, -deltaAlpha);

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


    OpenGL_wrapper::drawArrow3D({0, 0, 0}, {100, 0, 0}, new double[3]{1, 0.0, 0.0}, 1);
    OpenGL_wrapper::drawArrow3D({0, 0, 0}, {0, 100, 0}, new double[3]{0.0, 1, 0.0}, 1);
    OpenGL_wrapper::drawArrow3D({0, 0, 0}, {0, 0, 100}, new double[3]{0.0, 0.0, 1}, 1);

    glPushMatrix();
    glTranslated(30, 30, 0);
    robot.renderizar();
    glPopMatrix();


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

int main(int argc, char **argv)
{
    GLenum type;

    glutInit(&argc, argv);


    type = GLUT_RGB;
    type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
    glutInitDisplayMode(type);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(clientWidth, clientHeight);
    glutCreateWindow("ABGR extension");
    if (!glutExtensionSupported("GL_EXT_abgr")) {
        printf("Couldn't find abgr extension.\n");
        exit(0);
    }
#if !GL_EXT_abgr
    printf("WARNING: client-side OpenGL has no ABGR extension support!\n");
    printf("         Drawing only RGBA (and not ABGR) images and textures.\n");
#endif
    if (argc > 1) {
        dh_file_path = argv[1];
    }
    else {
        dh_file_path = "../dh_params/kr10.json";
    }


    Init(dh_file_path);
    glutKeyboardFunc(Key);
    glutDisplayFunc(Draw);
    glutReshapeFunc(Reshape);
    glutPassiveMotionFunc(motionFunc);
    glutTimerFunc(100, glutTimer, 100);
    glutMainLoop();
    return 0;
    /* ANSI C requires main to return int. */
}




