#include "../include/models.h"


Model3D::Model3D()
{
    ntriangles = 0;

}

Model3D::~Model3D()
{
    delete triangulos;
}

Model3D::Model3D(int ntriangulos)
{
    triangulos = new triangles[ntriangulos];
    ntriangles = ntriangulos;
}

void Model3D::leer(std::string nombre)
{

    char head[80] = "";

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
        std::cout << "File not found" << std::endl;
    }
}

