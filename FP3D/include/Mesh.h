//
// Created by ccampo on 28/10/17.
//

#ifndef FP3D_MESH_H
#define FP3D_MESH_H

#include <vector>
#include "Point3.h"
#include "../src/Vertex.h"
#include "../src/Triangle.h"

typedef unsigned int uint;

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;

    Mesh(const std::vector<Vector3> &points, const std::vector<uint> &indices);
    static Mesh createCube(double side, const Point3& center);
    static Mesh createPyramid(double side, double height, const Point3& center);
};


#endif //FP3D_MESH_H
