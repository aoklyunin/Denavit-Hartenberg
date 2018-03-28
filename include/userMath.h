//
// Created by alex on 28.03.18.
//

#ifndef DENAVIT_HARTENBERG_VISUALIZATION_USERMATH_H
#define DENAVIT_HARTENBERG_VISUALIZATION_USERMATH_H

#include <tgmath.h>
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

Matrix3d getRMatrix(double alpha, Vector3d v)
{
    double x = v(0);
    double y = v(1);
    double z = v(2);

    Matrix3d R;
    R << cos(alpha) + (1 - cos(alpha)) * x * x,
        (1 - cos(alpha)) * x * y - (sin(alpha)) * z,
        (1 - cos(alpha)) * x * z + (sin(alpha)) * y,

        (1 - cos(alpha)) * y * x + (sin(alpha)) * z,
        cos(alpha) + (1 - cos(alpha)) * y * y,
        (1 - cos(alpha)) * y * z - (sin(alpha)) * x,

        (1 - cos(alpha)) * z * x - (sin(alpha)) * y,
        (1 - cos(alpha)) * z * y + (sin(alpha)) * x,
        cos(alpha) + (1 - cos(alpha)) * z * z;

    return R;
}


#endif //DENAVIT_HARTENBERG_VISUALIZATION_USERMATH_H
