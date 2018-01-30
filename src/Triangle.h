//
// Created by ccampo on 28/11/17.
//

#ifndef TESTEXEC_TRIANGLE_H
#define TESTEXEC_TRIANGLE_H


#include "Vertex.h"

class Triangle {
public:
    Vertex a, b, c;
    Vector3 normal = Vector3(0,0,0);
    Vector3 ab = Vector3(0,0,0);
    Vector3 ac = Vector3(0,0,0);

    Triangle(Vertex &a, Vertex &b, Vertex &c);
};


#endif //TESTEXEC_TRIANGLE_H
