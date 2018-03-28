//
// Created by alex on 28.03.18.
//

#include "../include/Camera.h"
#include "../include/userMath.h"
#include "../include/traces.h"


Camera::Camera()
{
    dir << 1, 0, 0;
    pos << 0, 0, 0;
    up << 0, 0, 1;
}
Vector3d Camera::getEye()
{
    return dir + pos;
}
Vector3d Camera::getUp()
{
    return up;
}
Vector3d Camera::getCenter()
{
    return pos;
}
void Camera::rotateX(double alpha)
{

    Matrix3d R = getRMatrix(alpha, up);
    dir = R * dir;

}

void Camera::rotateY(double alpha)
{
    Vector3d r = up.cross(dir).normalized();
    Matrix3d R = getRMatrix(alpha, r);

    up = R * up;
    dir = R * dir;

}
void Camera::moveRight(double d)
{
    Vector3d r = up.cross(dir).normalized();
    pos += r * d;
}
void Camera::moveLeft(double d)
{
    Vector3d r = up.cross(dir).normalized();
    pos -= r * d;
}
void Camera::moveForward(double d)
{
    pos = pos - dir * d;
}
void Camera::moveBack(double d)
{
    pos = pos + dir * d;
}
