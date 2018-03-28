//
// Created by alex on 28.03.18.
//

#include "../include/OpenGLWrapper.h"


Matrix3d OpenGLWrapper::getRMatrix(double alpha, Vector3d v)
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

void OpenGLWrapper::getOrtho3(Vector3d A, Vector3d B, Vector3d *n)
{

    if (A(0) == B(0) && A(1) == B(1) && A(2) == B(2))
        throw std::runtime_error(std::string("A and B must be different vectors"));

    Vector3d n1 = B - A;

    double x1 = n1(0);
    double y1 = n1(1);
    double z1 = n1(2);

    double ax = A(0);
    double ay = A(1);
    double az = A(2);

    double x2;
    double y2;
    double z2;

    if (x1 != 0) {
        x2 = (-z1 * (z2 - az) - y1 * (y2 - ay)) / x1 - ax;
        y2 = 0.5;
        z2 = 0.5;
    }
    else if (y1 != 0) {
        x2 = 0.5;
        y2 = (-x1 * (x2 - ax) - z1 * (z2 - az)) / y1 - ay;
        z2 = 0.5;
    }
    else {
        x2 = 0.5;
        y2 = 0.5;
        z2 = (-x1 * (x2 - ax) - y1 * (y2 - ay)) / z1 - az;
    }

    Vector3d n2(x2, y2, z2);

    n1.normalize();
    n2.normalize();
    Vector3d n3 = n1.cross(n2);
    n[0] = n1;
    n[1] = n2;
    n[2] = n3;

}



void OpenGLWrapper::vectorVertex(Vector3d v)
{
    glVertex3d(v(0), v(1), v(2));
}

void OpenGLWrapper::Drawarrow3D(Vector3d A, Vector3d B, Vector3d color, double cota1, double R)
{
    Vector3d n[3];

    getOrtho3(A, B, n);
    glColor4d(color(0), color(1), color(2), 0.8);

    //info_msg(n2);
    //info_msg(n3);
    Vector3d n2 = n[1];
    Vector3d n3 = n[2];

    info_msg(n2.dot(n3));


    ///tubos
    glBegin(GL_QUAD_STRIP);
    vectorVertex(A + n3 * R);
    vectorVertex(B + n3 * R);
    vectorVertex(A + (n3 + n2) * R / sqrt(2));
    vectorVertex(B + (n3 + n2) * R / sqrt(2));
    vectorVertex(A + n2 * R);
    vectorVertex(B + n2 * R);
    vectorVertex(A + (n2 - n3) * R / sqrt(2));
    vectorVertex(B + (n2 - n3) * R / sqrt(2));
    vectorVertex(A + (-n3) * R);
    vectorVertex(B + (-n3) * R);
    vectorVertex(A + (-n3 - n2) * R / sqrt(2));
    vectorVertex(B + (-n3 - n2) * R / sqrt(2));
    vectorVertex(A + (-n2) * R);
    vectorVertex(B + (-n2) * R);
    vectorVertex(A + (-n2 + n3) * R / sqrt(2));
    vectorVertex(B + (-n2 + n3) * R / sqrt(2));
    vectorVertex(A + n3 * R);
    vectorVertex(B + n3 * R);
    glEnd();


//    Vector3d vertex[10], normallight;
//    double fraccion = 0.1, radioflecha = R + .7 * R;




//
//////flecha
//    vertex[0] = radioflecha * n2;
//    vertex[2] = radioflecha * n1.cross(n2).normalized();
//    vertex[1] = radioflecha * ((0.5) * (vertex[2] - vertex[0]) + vertex[0]).normalized();
//    vertex[4] = radioflecha * n1.cross(vertex[2]).normalized();
//    vertex[3] = radioflecha * ((0.5) * (vertex[4] - vertex[2]) + vertex[2]).normalized();
//    vertex[6] = radioflecha * n1.cross(vertex[4]).normalized();
//    vertex[5] = radioflecha * ((0.5) * (vertex[6] - vertex[4]) + vertex[4]).normalized();
//    vertex[7] = radioflecha * ((0.5) * (vertex[0] - vertex[6]) + vertex[6]).normalized();
//    vertex[8] = vertex[0];
//    vertex[9] = vertex[1];
//
//    Vector3d Ap(B - fraccion * (B - A));
//
//
//    glBegin(GL_TRIANGLE_STRIP);  //flecha
//
//    for (int i = 0; i < 9; i++) {
//
//        normallight = n1.cross(vertex[i - 1] - vertex[i + 1]);
//        normallight.normalize();
//        glNormal3f(normallight(0), normallight(1), normallight(2));
//        glVertex3f(vertex[i](0) + Ap(0), vertex[i](1) + Ap(1), vertex[i](2) + Ap(2));
//
//
//        glNormal3f(n1(0), n1(1), n1(2));
//        glVertex3f(Ap(0) + fraccion * (B - A)(0), Ap(1) + fraccion * (B - A)(1), Ap(2) + fraccion * (B - A)(2));
//
//        // top face
//
//    }
//
//    glEnd();

}