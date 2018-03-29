#pragma once

#include <Eigen/Dense>

#include "openGL_wrapper.h"
#include "traces.h"

using namespace Eigen;

class Camera
{
    Vector3d up;
    Vector3d dir;
    Vector3d pos;

public:

    Camera();
    Camera(Vector3d _pos,Vector3d _dir,Vector3d _up);
    Vector3d getEye();
    Vector3d getUp();
    Vector3d getCenter();
    void rotateX(double alpha);
    void rotateY(double alpha);
    void moveForward(double d);
    void moveBack(double d);
    void moveLeft(double d);
    void moveRight(double d);

};


