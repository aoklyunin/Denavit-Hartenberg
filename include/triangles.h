#pragma once

#include <Eigen/Dense>

using namespace Eigen;

class triangles
{
public:
    triangles();
    ~triangles();
    Vector3d vertices[3];
    Vector3d N;
    Vector3d normal();
    void definirRz(float dtheta);
    void dibujar();
    void rotar(float dtheta);
};
