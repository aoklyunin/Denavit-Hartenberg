#pragma once

#include <vector>
#include <cstdlib>
#include <Eigen/Dense>
#include <cmath>

#include "models.h"
#include "openGL_wrapper.h"

#include <json/json.h>


using namespace Eigen;

///Copyright (C) <2017>  <Eliseo Rivera> curso.tareas@gmail.com
class Robot
{
public:
    Robot();
    ~Robot();

    Model3D *base;
    Model3D *b1;
    Model3D *b2;
    Model3D *b3;
    Model3D *b4;
    Model3D *b5;
    Model3D *b6;
    Model3D *gripe;

    void inicializar();
    void renderizar();
    void configurarTH(std::string dh_file_path);
    void rotateLink(int j, double alpha);
    Matrix4d THx, THy, THz, TH;

    std::vector<Matrix4d> THList;
    std::vector<Vector4d> Origenes;
    std::vector<Model3D *> modelos;

    std::vector<std::vector<double>> dhParams;

private :

};
