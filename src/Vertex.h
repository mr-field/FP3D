//
// Created by ccampo on 28/11/17.
//

#ifndef TESTEXEC_VERTEX_H
#define TESTEXEC_VERTEX_H


#include <Vector3.h>

class Vertex {
public:
    Vector3 position;
    Vector3 normal;

    Vertex(Vector3 position, Vector3 normal);
};


#endif //TESTEXEC_VERTEX_H
