//
// Created by ccampo on 28/11/17.
//

#ifndef FP3D_VERTEX_H
#define FP3D_VERTEX_H


#include <Vector3.h>

class Vertex {
public:
    Vector3 position;
    Vector3 normal;

    Vertex(Vector3 position, Vector3 normal) : position(position), normal(normal) {};
};


#endif //FP3D_VERTEX_H
