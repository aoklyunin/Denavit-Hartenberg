//
// Created by alex on 28.03.18.
//
#pragma once

#include <GL/gl.h>
#include <GL/glut.h>
#include <Eigen/Dense>
#include <iostream>

#include "Camera.h"

using namespace Eigen;

class OpenGLWrapper
{
    static void vectorVertex(Vector3d v);

    static void getOrtho3(Vector3d A, Vector3d B, Vector3d *n);
public:
    static void Drawarrow3D(Vector3d A, Vector3d B, Vector3d color, double cota1, double R);
    static Matrix3d getRMatrix(double alpha, Vector3d v);
};

