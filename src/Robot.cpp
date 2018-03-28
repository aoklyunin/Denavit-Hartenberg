
#include "../include/Robot.h"


///Copyright (C) <2017>  <Eliseo Rivera> curso.tareas@gmail.com
Robot::Robot()
{
    THx = Matrix<double, 4, 4>::Identity();
    THy = Matrix<double, 4, 4>::Identity();
    THz = Matrix<double, 4, 4>::Identity();
    TH = Matrix<double, 4, 4>::Identity();

}

Robot::~Robot()
{

    delete base;
    delete b1;
    delete b2;
    delete b3;
    delete b4;
    delete b5;
    delete b6;

    //dtor
}

void Robot::inicializar()
{
    base = new modelo3D();
    b1 = new modelo3D();
    b2 = new modelo3D();
    b3 = new modelo3D();
    b4 = new modelo3D();
    b5 = new modelo3D();
    b6 = new modelo3D();


    base->leer("models/base.STL");
    b1->leer("models/b1.STL");
    b2->leer("models/b1.STL");
    b3->leer("models/b1.STL");
    b4->leer("models/b1.STL");
    b5->leer("models/b1.STL");
    b6->leer("models/b1.STL");


    modelos.push_back(base);
    modelos.push_back(b1);
    modelos.push_back(b2);
    modelos.push_back(b3);
    modelos.push_back(b4);
    modelos.push_back(b5);
    modelos.push_back(b6);

}

void Robot::rotateLink(int j, double alpha)
{
    dhParams.at(j).at(4) += alpha;
    info_msg(dhParams.at(j));
}

void Robot::configurarTH()
{
    double pi = 3.14;
    // theta, a, d, alpha
    vector<double> dhParam{0, 40, 2.5, -pi / 2, 0};
    dhParams.push_back(dhParam);
    dhParam = vector<double>{0, 0, 31.5, 0, 0};
    dhParams.push_back(dhParam);
    dhParam = vector<double>{-pi / 2, 0, 30.5, -pi / 2, 0};
    dhParams.push_back(dhParam);
    dhParam = vector<double>{0, 36.5 + 18, 0, pi / 2, 0};
    dhParams.push_back(dhParam);
    dhParam = vector<double>{0, 0, 0, -pi / 2, 0};
    dhParams.push_back(dhParam);
    dhParam = vector<double>{0, 14.8, 0, 0, 0};
    dhParams.push_back(dhParam);
}

Matrix4d getDHMatrix(vector<double> dh)
{
    double theta = dh.at(0) + dh.at(4);
    double d = dh.at(1);
    double a = dh.at(2);
    double alpha = dh.at(3);

    Matrix4d m;
    m << cos(theta), -sin(theta) * cos(alpha), sin(theta) * sin(alpha), a * cos(theta),
        sin(theta), cos(theta) * cos(alpha), -cos(theta) * sin(alpha), a * sin(theta),
        0, sin(alpha), cos(alpha), d,
        0, 0, 0, 1;
    return m;
}
void Robot::renderizar()
{

    TH = Matrix<double, 4, 4>::Identity();

    modelo3D *model;

    for (auto &dhParam : dhParams) {
        Matrix4d DH = getDHMatrix(dhParam);
        //info_msg("test");
        // info_msg(DH);
        TH = TH * DH;

        Vector3d nx(TH(0, 0), TH(1, 0), TH(2, 0));
        Vector3d ny(TH(0, 1), TH(1, 1), TH(2, 1));
        Vector3d nz(TH(0, 2), TH(1, 2), TH(2, 2));

        Vector3d pos(TH(0, 3), TH(1, 3), TH(2, 3));

        // info_msg(pos);

        OpenGLWrapper::Drawarrow3D(pos, pos + 4 * nx, new double[3]{1, 0.1, 0.2}, 0.3);
        OpenGLWrapper::Drawarrow3D(pos, pos + 4 * ny, new double[3]{.1, 1, 0.2}, 0.3);
        OpenGLWrapper::Drawarrow3D(pos, pos + 4 * nz, new double[3]{0.1, 0.2, 1}, 0.3);

//      model = modelos[m];
//        //  }
//        glColor4f(fabs(cos(m * PI / modelos.size())), fabs(sin(20 * (m - 5) * PI / modelos.size())), 0.2, 0.5);
//
//        glEnable(GL_BLEND);
//        glBegin(GL_TRIANGLES);
//
//        glFrontFace(GL_FRONT_AND_BACK);
//        for (int i = 0; i < model->ntriangles; i++) {
//
//            Vector3d v1 = model->triangulos[i].vertices[0];   //posiciones locales
//            Vector3d v2 = model->triangulos[i].vertices[1];
//            Vector3d v3 = model->triangulos[i].vertices[2];
//            Vector4d v14(v1(0), v1(1), v1(2), 1), v24(v2(0), v2(1), v2(2), 1), v34(v2(0), v2(1), v2(2), 1);
//
//            v14 = TH * v14;
//            v24 = TH * v24;
//            v34 = TH * v34;
//            v1 = {v14(0, 0), v14(1, 0), v14(2, 0)};
//            v2 = {v24(0, 0), v24(1, 0), v24(2, 0)};
//            v3 = {v34(0, 0), v34(1, 0), v34(2, 0)};
//
//
//            Vector4d N, d14, d24;
//            d14 = v24 - v14;
//            d24 = v34 - v14;
//            Vector3d d1, d2, n;
//            d1 = {d14(0, 0), d14(1, 0), d14(2, 0)};
//            d2 = {d24(0, 0), d24(1, 0), d24(2, 0)};
//            n = d1.cross(d2);  ///devuelve el producto vectorial
//            n.normalize();
//
//
//            glNormal3f(n(0), n(1), n(2));
//            glVertex3f(v1(0), v1(1), v1(2));
//            glVertex3f(v2(0), v2(1), v2(2));
//            glVertex3f(v3(0), v3(1), v3(2));
//        }
//        glEnd();
//// }
//        glDisable(GL_BLEND);
//

///DIBUJAR EJES


//}
    }

}
