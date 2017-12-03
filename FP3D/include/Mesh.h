//
// Created by ccampo on 28/10/17.
//

#ifndef FP3D_MESH_H
#define FP3D_MESH_H

#include <vector>
#include "../src/Vertex.h"
#include "../src/Triangle.h"
#include "Matrix4.h"
#include "../src/Object3D.h"

typedef unsigned int uint;

class Mesh : public Object3D {
public:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;

    Mesh(const std::vector<Vector3> &points, const std::vector<uint> &indices, const Vector3& center);
    static Mesh createCube(float side, const Vector3& center);
    static Mesh createPyramid(float side, float height, const Vector3& center);
};


#endif //FP3D_MESH_H
