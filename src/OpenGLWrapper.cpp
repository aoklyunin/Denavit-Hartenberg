//
// Created by alex on 28.03.18.
//

#include <iostream>
#include "../include/OpenGLWrapper.h"


void OpenGLWrapper::Drawarrow3D(Vector3d A, Vector3d B, Vector3d color, double cota1, double R)
{
    if (A(0) == B(0)&& A(1) == B(1)&& A(2) == B(2))
        throw std::runtime_error(std::string("A and B must be different vectors"));

    glColor4f(color(0), color(1), color(2), 0.8);

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

    info_msg(z2);

    Vector3d n2(x2, y2, z2);

    n1.normalize();
    n2.normalize();

    //info_msg(n1);
    //info_msg(n2);

    Vector3d vertex[10], normallight;


    vertex[0] = R * n2;
    vertex[2] = R * n1;

    vertex[1] = R * (0.5) * ((vertex[2] - vertex[0]) + vertex[0]).normalized();
    vertex[4] = R * n1.cross(vertex[2]).normalized();
    vertex[3] = R * (0.5) * ((vertex[4] - vertex[2]) + vertex[2]).normalized();
    vertex[6] = R * n1.cross(vertex[4]).normalized();
    vertex[5] = R * (0.5) * ((vertex[6] - vertex[4]) + vertex[4]).normalized();
    vertex[7] = R * (0.5) * ((vertex[0] - vertex[6]) + vertex[6]).normalized();
    vertex[8] = vertex[0];
    vertex[9] = vertex[1];

    double fraccion = 0.1, radioflecha = R + .7 * R;


    ///tubos
    glBegin(GL_TRIANGLE_STRIP);

    for (int i = 0; i < 9; i++) {

        normallight = n1.cross(vertex[i - 1] - vertex[i + 1]);
        normallight.normalize();
        glNormal3f(normallight(0), normallight(1), normallight(2));

        glVertex3f(vertex[i](0) + A(0), vertex[i](1) + A(1), vertex[i](2) + A(2));

        glVertex3f(vertex[i](0) + B(0) - fraccion * (B(0) - A(0)),
                   vertex[i](1) + B(1) - fraccion * (B(1) - A(1)),
                   vertex[i](2) + B(2) - fraccion * (B(2) - A(2)));

        // top face

    }

    glEnd();



//flecha
    vertex[0] = radioflecha * n2;
    vertex[2] = radioflecha * n1.cross(n2).normalized();
    vertex[1] = radioflecha * ((0.5) * (vertex[2] - vertex[0]) + vertex[0]).normalized();
    vertex[4] = radioflecha * n1.cross(vertex[2]).normalized();
    vertex[3] = radioflecha * ((0.5) * (vertex[4] - vertex[2]) + vertex[2]).normalized();
    vertex[6] = radioflecha * n1.cross(vertex[4]).normalized();
    vertex[5] = radioflecha * ((0.5) * (vertex[6] - vertex[4]) + vertex[4]).normalized();
    vertex[7] = radioflecha * ((0.5) * (vertex[0] - vertex[6]) + vertex[6]).normalized();
    vertex[8] = vertex[0];
    vertex[9] = vertex[1];
    Vector3d Ap(B - fraccion * (B - A));


    glBegin(GL_TRIANGLE_STRIP);  //flecha

    for (int i = 0; i < 9; i++) {

        normallight = n1.cross(vertex[i - 1] - vertex[i + 1]);
        normallight.normalize();
        glNormal3f(normallight(0), normallight(1), normallight(2));
        glVertex3f(vertex[i](0) + Ap(0), vertex[i](1) + Ap(1), vertex[i](2) + Ap(2));


        glNormal3f(n1(0), n1(1), n1(2));
        glVertex3f(Ap(0) + fraccion * (B - A)(0), Ap(1) + fraccion * (B - A)(1), Ap(2) + fraccion * (B - A)(2));

        // top face

    }

    glEnd();

}