#include <GL/gl.h>
#include <GL/glut.h>
#include "../include/ClaseOpenGL.h"

void render(void);

ClaseOpenGL *Miclase = new ClaseOpenGL;

void glutTimer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, glutTimer, 100);
}

void my_render(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    std::cout << "render\n";
}
void init(){
    glClearColor(0.5, 0.5, 0.5, 1.0);
    //Miclase->inicializar();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Simple GLUT application");
    glutTimerFunc(100, glutTimer, 100);
    glutDisplayFunc(my_render);
    init();
    glutMainLoop(); // Says process has finished and can start rendering.

}


