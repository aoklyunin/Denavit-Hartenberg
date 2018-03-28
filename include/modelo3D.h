#ifndef MODELO3D_H
#define MODELO3D_H
#include"Triangle3D.h"
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

class modelo3D
{
public:
    int ntriangles;
    Triangle3D *triangulos;
    Matrix3d Rx, Ry, Rz;  //local
    modelo3D();

    void leer(string nombre);
    virtual ~modelo3D();
    modelo3D(int ntriangulos);
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

#endif // MODELO3D_H
