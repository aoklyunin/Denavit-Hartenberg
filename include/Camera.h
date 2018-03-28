//
// Created by alex on 28.03.18.
//

#ifndef DENAVIT_HARTENBERG_VISUALIZATION_CAMERA_H
#define DENAVIT_HARTENBERG_VISUALIZATION_CAMERA_H


#include "vector3d.h"
#include <Eigen/Dense>

using namespace Eigen;

class Camera
{
    Vector3d up;
    Vector3d dir;
    Vector3d pos;

public:

    Camera();
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


#endif //DENAVIT_HARTENBERG_VISUALIZATION_CAMERA_H
