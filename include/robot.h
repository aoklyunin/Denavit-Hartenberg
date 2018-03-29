#pragma once

#include <vector>
#include <cstdlib>
#include <Eigen/Dense>
#include <cmath>

#include "models.h"
#include "openGL_wrapper.h"

#include <json/json.h>


using namespace Eigen;


class Robot
{
public:
    Robot();
    ~Robot();
    void inicializar();
    void renderizar();
    void configurarTH(std::string dh_file_path);
    void rotateLink(int j, double alpha);
    Vector3d getPosition();

private :
    Matrix4d TH;
    std::vector<Model3D *> models;

    std::vector<std::vector<double>> dhParams;

    Model3D *base;
    Model3D *b1;
    Model3D *b2;
    Model3D *b3;
    Model3D *b4;
    Model3D *b5;
    Model3D *b6;

    Vector3d position;
    int jointCnt;
};
