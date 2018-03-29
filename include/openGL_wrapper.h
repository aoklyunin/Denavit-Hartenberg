//
// Created by alex on 28.03.18.
//
#pragma once

#include <GL/gl.h>
#include <GL/glut.h>
#include <Eigen/Dense>
#include <iostream>

#include "camera.h"

using namespace Eigen;

class OpenGL_wrapper
{
    static void getOrtho3(Vector3d A, Vector3d B, Vector3d *n);
    static void getCircleChoords(Vector3d n1, Vector3d n2, Vector3d *choords);
public:
    static void drawArrow3D(Vector3d A, Vector3d B, double *color, double R);
    static Matrix3d getRMatrix(double alpha, Vector3d v);
    static void vectorVertex(Vector3d v);
};

