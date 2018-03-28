//
// Created by alex on 28.03.18.
//

#ifndef DENAVIT_HARTENBERG_VISUALIZATION_OPENGLWRAPPER_H
#define DENAVIT_HARTENBERG_VISUALIZATION_OPENGLWRAPPER_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <Eigen/Dense>

#include "traces.h"

using namespace Eigen;

class OpenGLWrapper
{
public:
    static void Drawarrow3D(Vector3d A, Vector3d B, Vector3d color, double cota1, double R);
};


#endif //DENAVIT_HARTENBERG_VISUALIZATION_OPENGLWRAPPER_H
