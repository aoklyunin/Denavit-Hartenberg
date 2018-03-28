#pragma once

#include <Eigen/Dense>

using namespace Eigen;

class Triangle3D
{
public:
Triangle3D();
~Triangle3D();
Vector3d vertices[3];
Vector3d N;
Vector3d normal();
void definirRz(float dtheta);
void dibujar();
void rotar(float dtheta);
};
