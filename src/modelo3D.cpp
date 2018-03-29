

#include "../include/modelo3D.h"


//Copyright (C) <2017>  <Eliseo Rivera Silva> curso.tareas@gmail.com


modelo3D::modelo3D()
{
    ntriangles = 0;


    BFRx = Matrix<double, 3, 3>::Identity();
    BFRy = Matrix<double, 3, 3>::Identity();
    BFRz = Matrix<double, 3, 3>::Identity();
    LARx = Matrix<double, 3, 3>::Identity();
    LARy = Matrix<double, 3, 3>::Identity();
    LARz = Matrix<double, 3, 3>::Identity();
    R = Matrix<double, 3, 3>::Identity();  //accumulated rotations
    Rz = Matrix<double, 3, 3>::Identity();
    Rx = Matrix<double, 3, 3>::Identity();
    Ry = Matrix<double, 3, 3>::Identity();
    ///***************
    //IRx.identity(3);
    //IRy.identity(3);
    //IRz.identity(3);
    ///***************
}

modelo3D::~modelo3D()
{
    delete triangulos;

}
modelo3D::modelo3D(int ntriangulos)
{
    triangulos = new triangles[ntriangulos];
    ntriangles = ntriangulos;
}
void modelo3D::leer(std::string nombre)
{

    char head[80] = "";
///************
    //std::cout<<nombre.c_str()<<std::endl;

    //archivo.open(nombre.c_str(), std::ios::in | std::ios::binary);
    archivo.open("../models/b1.stl", std::ios::in | std::ios::binary);

    if (archivo) {
        archivo.read(head, 80);

        int32_t size;
        archivo.read(reinterpret_cast<char *> (&size), sizeof(int32_t));
        ntriangles = size;
        triangulos = new triangles[size];
        triangles triangle;
        Vector3d P0, P1, P2;
        Vector3d normal;
        float p0[3], p1[3], p2[3], n[3];
        char attribute[2] = "0";
        for (int i = 0; i < size; i++) {

            archivo.read(reinterpret_cast<char *> (&n[0]), 4);
            archivo.read(reinterpret_cast<char *> (&n[1]), 4);
            archivo.read(reinterpret_cast<char *> (&n[2]), 4);
            //  cout<<n[0]<<" , "<<n[1]<<" , "<<n[2]<<endl;
            triangulos[i].N = {n[0], n[1], n[2]};
            archivo.read(reinterpret_cast<char *> (&p0[0]), 4);
            archivo.read(reinterpret_cast<char *> (&p0[1]), 4);
            archivo.read(reinterpret_cast<char *> (&p0[2]), 4);
            //	   cout<<p0[0]<<" , "<<p0[1]<<" , "<<p0[2]<<endl;
            triangulos[i].vertices[0] = {p0[0], p0[1], p0[2]};


            archivo.read(reinterpret_cast<char *> (&p1[0]), 4);
            archivo.read(reinterpret_cast<char *> (&p1[1]), 4);
            archivo.read(reinterpret_cast<char *> (&p1[2]), 4);
            //	   cout<<p1[0]<<" , "<<p1[1]<<" , "<<p1[2]<<endl;
            triangulos[i].vertices[1] = {p1[0], p1[1], p1[2]};

            archivo.read(reinterpret_cast<char *> (&p2[0]), 4);
            archivo.read(reinterpret_cast<char *> (&p2[1]), 4);
            archivo.read(reinterpret_cast<char *> (&p2[2]), 4);
            //	   cout<<p2[0]<<" , "<<p2[1]<<" , "<<p2[2]<<endl;

            triangulos[i].vertices[2] = {p2[0], p2[1], p2[2]};
            archivo.read(attribute, 2);
        }


        archivo.close();
    }
    else {
        ntriangles = 0;
        std::cout << "el archivo no se encuentra" << std::endl;
    }
}
void modelo3D::definirRx(float dtheta)
{

    Rx << 1, 0, 0,
        0, cos(dtheta), -sin(dtheta),
        0, sin(dtheta), cos(dtheta);

}
void modelo3D::definirRy(float dtheta)
{


    Ry << cos(dtheta), 0, sin(dtheta),
        0, 1, 0,
        -sin(dtheta), 0, cos(dtheta);

}
void modelo3D::definirRz(float dtheta)
{

    Rz << cos(dtheta), -sin(dtheta), 0,
        sin(dtheta), cos(dtheta), 0,
        0, 0, 1;

}

void modelo3D::dibujar()
{
    glBegin(GL_TRIANGLES);
    glFrontFace(GL_FRONT_AND_BACK);

    for (int i = 0; i < ntriangles; i++) {

        Vector3d v1 = triangulos[i].vertices[0];   //locales son locales
        Vector3d v2 = triangulos[i].vertices[1];
        Vector3d v3 = triangulos[i].vertices[2];
        Vector3d V1, V2, V3;

        V1 = ux * v1(0) + uy * v1(1) + uz * v1(2);  // se dibuja en base local en origen de modelo local

        V2 = v2(0) * ux + v2(1) * uy + v2(2) * uz;
        V3 = v3(0) * ux + v3(1) * uy + v3(2) * uz;

        V1 = O + V1;
        V2 = O + V2;
        V3 = O + V3;

        Vector3d d1, d2, n;
        d1 = V2 - V1;
        d2 = V3 - V1;
        n = d1.cross(d2);  ///devuelve el producto vectorial
        n.normalize();

        glNormal3f(n(0), n(1), n(2));
        glVertex3f(V1(0), V1(1), V1(2));
        glVertex3f(V2(0), V2(1), V2(2));
        glVertex3f(V3(0), V3(1), V3(2));
    }

    glEnd();
};

void modelo3D::rotarZ()
{  //global rotation of only model
    for (int i = 0; i < ntriangles; i++) {
        Vector3d v1, v2, v3;
        v1 = triangulos[i].vertices[0];
        v2 = triangulos[i].vertices[1];
        v3 = triangulos[i].vertices[2];
        v1 = Rz * v1;
        v2 = Rz * v2;
        v3 = Rz * v3;

        triangulos[i].vertices[0] = v1;
        triangulos[i].vertices[1] = v2;
        triangulos[i].vertices[2] = v3;
    }
    R = Rz * R;
}
void modelo3D::rotarY()
{ //global rotation  of only model
    for (int i = 0; i < ntriangles; i++) {
        Vector3d v1, v2, v3;
        v1 = triangulos[i].vertices[0];
        v2 = triangulos[i].vertices[1];
        v3 = triangulos[i].vertices[2];
        v1 = Ry * v1;
        v2 = Ry * v2;
        v3 = Ry * v3;

        triangulos[i].vertices[0] = v1;
        triangulos[i].vertices[1] = v2;
        triangulos[i].vertices[2] = v3;
    }
    R = Ry * R;
}
void modelo3D::rotarX()
{//global rotation  of only model
    for (int i = 0; i < ntriangles; i++) {
        Vector3d v1, v2, v3;
        v1 = triangulos[i].vertices[0];
        v2 = triangulos[i].vertices[1];
        v3 = triangulos[i].vertices[2];
        v1 = Rx * v1;
        v2 = Rx * v2;
        v3 = Rx * v3;

        triangulos[i].vertices[0] = v1;
        triangulos[i].vertices[1] = v2;
        triangulos[i].vertices[2] = v3;
    }
    R = Rx * R;
}

void modelo3D::trasladar(Vector3d A)
{  //local traslation
    for (int i = 0; i < ntriangles; i++) {
        Vector3d v1, v2, v3;
        v1 = triangulos[i].vertices[0];
        v2 = triangulos[i].vertices[1];
        v3 = triangulos[i].vertices[2];


        triangulos[i].vertices[0] = v1 + A;
        triangulos[i].vertices[1] = v2 + A;
        triangulos[i].vertices[2] = v3 + A;
    }

}
void modelo3D::BodyFramerotarX()
{
    R = BFRx * R;
    ux = BFRx * ux;
    uy = BFRx * uy;
    uz = BFRx * uz;

};
void modelo3D::BodyFramerotarY()
{
    R = BFRy * R;
    ux = BFRy * ux;
    uy = BFRy * uy;
    uz = BFRy * uz;
};
void modelo3D::BodyFramerotarZ()
{
    R = BFRz * R;
    ux = BFRz * ux;
    uy = BFRz * uy;
    uz = BFRz * uz;
};
/*
void modelo3D::IRx(){
    Matrix::inversa(IRx());

}*/

Vector3d modelo3D::LocalMassCenter() const
{
    Vector3d center;
    for (int i = 0; i < ntriangles; i++) {
        Vector3d v1, v2, v3;
        v1 = triangulos[i].vertices[0];
        v2 = triangulos[i].vertices[1];
        v3 = triangulos[i].vertices[2];
        center = center + (1.0 / 3.0) * (v1 + v2 + v3);

    }
    center = (1.0 / ntriangles) * center;
    std::cout << " Local center mass is :" << std::endl;
    std::cout << center << std::endl;
    return center;

}
Vector3d modelo3D::GlobalCenterMass() const
{
    Vector3d L = LocalMassCenter();

    Vector3d C = O + L(0) * ux + L(1) * uy + L(2) * uz;
    std::cout << " Global center mass is: " << std::endl;
    std::cout << C << std::endl;
    return C;

}
