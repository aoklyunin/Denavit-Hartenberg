#include "../include/openGL_wrapper.h"

// получаем матрицу поворота
Matrix3d OpenGL_wrapper::getRMatrix(double alpha, Vector3d v)
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

// по двум точкам получаем три ортогональных базисных вектора, первый сонаправлен с AB
void OpenGL_wrapper::getOrtho3(Vector3d A, Vector3d B, Vector3d *n)
{

    if (A(0) == B(0) && A(1) == B(1) && A(2) == B(2))
        throw std::runtime_error(std::string("A and B must be different vectors"));

    Vector3d n1 = B - A;

    double x2;
    double y2;
    double z2;

    if (n1(0) != 0) {
        y2 = 0.5;
        z2 = 0.5;
        x2 = (-n1(2) * (z2 - A(2)) - n1(1) * (y2 - A(1))) / n1(0) - A(0);
    }
    else if (n1(1) != 0) {
        x2 = 0.5;
        z2 = 0.5;
        y2 = (-n1(0) * (x2 - A(0)) - n1(2) * (z2 - A(2))) / n1(1) - A(1);
    }
    else {
        x2 = 0.5;
        y2 = 0.5;
        z2 = (-n1(0) * (x2 - A(0)) - n1(1) * (y2 - A(1))) / n1(2) - A(2);
    }

    n[0] = n1.normalized();
    n[1] = Vector3d(x2, y2, z2).normalized();
    n[2] = n[0].cross(n[1]).normalized();

}

void OpenGL_wrapper::vectorVertex(Vector3d v)
{
    glVertex3d(v(0), v(1), v(2));
}

// получить набор координат, образующий окружность в базисе переданны векторов
void OpenGL_wrapper::getCircleChoords(Vector3d n1, Vector3d n2, Vector3d *choords)
{
    choords[0] = n1;
    choords[1] = (n1 + n2) / sqrt(2);
    choords[2] = n2;
    choords[3] = (n2 - n1) / sqrt(2);
    choords[4] = -n1;
    choords[5] = (-n1 - n2) / sqrt(2);
    choords[6] = -n2;
    choords[7] = (-n2 + n1) / sqrt(2);
    choords[8] = n1;
}

// Нарисовать координатную ось
void OpenGL_wrapper::drawArrow3D(Vector3d A, Vector3d B, double *color, double R)
{
    Vector3d n[3];

    getOrtho3(A, B, n);
    glColor4d(color[0], color[1], color[2], 0.8);

    Vector3d circleChoords[9];
    getCircleChoords(n[1], n[2], circleChoords);


    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < 9; i++) {
        vectorVertex(A + circleChoords[i] * R);
        vectorVertex(B + circleChoords[i] * R);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    vectorVertex(B + n[0] * 4 * R);
    for (int i = 0; i < 9; i++) {
        vectorVertex(B + circleChoords[i] * 2 * R);
    }
    glEnd();

}