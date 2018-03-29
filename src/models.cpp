#include "../include/models.h"



Model3D::Model3D()
{
    ntriangles = 0;

}

Model3D::~Model3D()
{
    delete triangleList;
}

Model3D::Model3D(int ntriangulos)
{
    triangleList = new Triangle[ntriangulos];
    ntriangles = ntriangulos;
}

void Model3D::leer(std::string nombre)
{

    char head[80] = "";

    modelFStream.open("../models/b1.stl", std::ios::in | std::ios::binary);

    if (modelFStream) {
        modelFStream.read(head, 80);

        int32_t size;
        modelFStream.read(reinterpret_cast<char *> (&size), sizeof(int32_t));
        ntriangles = size;
        triangleList = new Triangle[size];
        Triangle triangle;
        Vector3d P0, P1, P2;
        Vector3d normal;
        float p0[3], p1[3], p2[3], n[3];
        char attribute[2] = "0";
        for (int i = 0; i < size; i++) {

            modelFStream.read(reinterpret_cast<char *> (&n[0]), 4);
            modelFStream.read(reinterpret_cast<char *> (&n[1]), 4);
            modelFStream.read(reinterpret_cast<char *> (&n[2]), 4);

            modelFStream.read(reinterpret_cast<char *> (&p0[0]), 4);
            modelFStream.read(reinterpret_cast<char *> (&p0[1]), 4);
            modelFStream.read(reinterpret_cast<char *> (&p0[2]), 4);
            triangleList[i].vertices[0] = {p0[0], p0[1], p0[2]};


            modelFStream.read(reinterpret_cast<char *> (&p1[0]), 4);
            modelFStream.read(reinterpret_cast<char *> (&p1[1]), 4);
            modelFStream.read(reinterpret_cast<char *> (&p1[2]), 4);
            triangleList[i].vertices[1] = {p1[0], p1[1], p1[2]};

            modelFStream.read(reinterpret_cast<char *> (&p2[0]), 4);
            modelFStream.read(reinterpret_cast<char *> (&p2[1]), 4);
            modelFStream.read(reinterpret_cast<char *> (&p2[2]), 4);

            triangleList[i].vertices[2] = {p2[0], p2[1], p2[2]};
            modelFStream.read(attribute, 2);
        }


        modelFStream.close();
    }
    else {
        ntriangles = 0;
        err_msg("File not found");
    }
}

