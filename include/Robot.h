#ifndef ROBOT_H
#define ROBOT_H
#include "modelo3D.h"
#include <vector>
#include <cstdlib>
#include <Eigen/Dense>
#include "OpenGLWrapper.h"

using namespace Eigen;

///Copyright (C) <2017>  <Eliseo Rivera> curso.tareas@gmail.com
class Robot
{
    public:
        Robot();
        ~Robot();

        modelo3D *base;
           modelo3D *b1;
              modelo3D *b2;
                 modelo3D *b3;
                    modelo3D *b4;
                       modelo3D *b5;
                          modelo3D *b6;
                               modelo3D *gripe;

void inicializar();
void renderizar();
void configurarTH();

void AplicarTHx(float theta, Vector3d d);
void AplicarTHy(float theta, Vector3d d);
void AplicarTHz(float theta, Vector3d d);

    Matrix4d THx,THy,THz,TH;

std::vector<Matrix4d> THList;
std::vector<Vector4d> Origenes;
std::vector<modelo3D*> modelos;


float theta1, theta2, theta3,theta4, theta5, theta6,theta7;
Vector3d d1,d2,d3,d4,d5,d6,d7;
private :
void DefinirTHx(float theta, Vector3d d);
void DefinirTHy(float theta, Vector3d d);
void DefinirTHz(float theta, Vector3d d);

};

#endif // ROBOT_H
