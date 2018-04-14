//
// Created by ccampo on 28/11/17.
//

#ifndef FP3D_TRIANGLE_H
#define FP3D_TRIANGLE_H


#include "Vertex.h"

class Triangle {
public:
    Vertex a, b, c;
    Vector3 normal = Vector3(0,0,0);

    Triangle(Vertex &a, Vertex &b, Vertex &c);
};


#endif //FP3D_TRIANGLE_H
