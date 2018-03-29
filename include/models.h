#pragma once

#include"triangles.h"
#include<fstream>
#include <iostream>

#include <GL/gl.h>
#include<GL/glu.h>
#define PI 3.14159265
#include <string>
#include <Eigen/Dense>
//Copyright (C) <2017>  <Eliseo Rivera Silva> curso.tareas@gmail.com

using namespace std;
using namespace Eigen;

class Model3D
{
public:
    int ntriangles;
    triangles *triangulos;
    Matrix3d Rx, Ry, Rz;  //local
    Model3D();

    void leer(string nombre);
    virtual ~Model3D();
    Model3D(int ntriangulos);
    void dibujar();
    void rotarX();  //local x axis rotation
    void rotarY();  //local y axis rotation
    void rotarZ();  //local z axis rotation
    void definirRz(float theta);
    void definirRy(float theta);
    void definirRx(float theta);

    Matrix3d LARx, LARy, LARz;

    void trasladar(Vector3d A);
    fstream archivo;

    Vector3d ux, uy, uz, O; //local axis nad Origin

    void BodyFramerotarX();
    void BodyFramerotarY();
    void BodyFramerotarZ();
    Matrix3d BFRx, BFRy, BFRz, R;
    Vector3d LocalMassCenter() const;
    Vector3d GlobalCenterMass() const;

};
