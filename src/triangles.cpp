#include "../include/triangles.h"

//Copyright (C) <2017>  <Eliseo Rivera Silva> curso.tareas@gmail.com

triangles::triangles()
{
    //ctor
}

triangles::~triangles()
{
    //dtor
}
Vector3d triangles::normal()
{
    Vector3d d1, d2, n;
    d1 = vertices[1] - vertices[0];
    d2 = vertices[2] - vertices[0];
    n = d1.cross(d2);  ///devuelve el producto vectorial
    n.normalize();
    N = n;  ///se guarda el valor de la normal en el campo N
    return n;
}