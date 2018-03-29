#pragma once

#include<fstream>
#include <iostream>
#include <GL/gl.h>
#include<GL/glu.h>
#include <string>
#include <Eigen/Dense>

#include "traces.h"
#include"triangle.h"


using namespace std;
using namespace Eigen;

class Model3D
{
public:
    int ntriangles;
    Triangle *triangleList;

    Model3D();

    void leer(string nombre);
    virtual ~Model3D();

    Model3D(int ntriangulos);

    fstream modelFStream;

};
