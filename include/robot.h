#pragma once

#include <vector>
#include <cstdlib>
#include <Eigen/Dense>
#include <cmath>

#include "modelo3D.h"
#include "openGL_wrapper.h"

#include <json/json.h>


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
    void configurarTH(std::string dh_file_path);
    void rotateLink(int j, double alpha);
    Matrix4d THx, THy, THz, TH;

    std::vector<Matrix4d> THList;
    std::vector<Vector4d> Origenes;
    std::vector<modelo3D *> modelos;

    std::vector<std::vector<double>> dhParams;

private :

};
