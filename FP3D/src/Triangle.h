//
// Created by ccampo on 28/11/17.
//

#ifndef TESTEXEC_TRIANGLE_H
#define TESTEXEC_TRIANGLE_H


#include "Vertex.h"

class Triangle {
public:
    Vertex a, b, c;

    Triangle(const Vertex &a, const Vertex &b, const Vertex &c);
};


#endif //TESTEXEC_TRIANGLE_H
