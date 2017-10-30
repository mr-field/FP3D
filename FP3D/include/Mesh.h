//
// Created by ccampo on 28/10/17.
//

#ifndef FP3D_MESH_H
#define FP3D_MESH_H

#include <vector>
#include "Point3.h"

class Mesh {
public:
    std::vector<Point3> vertices;
    std::vector<int> indices;

    Mesh(const std::vector<Point3> &triangles, const std::vector<int> &indices);
    static Mesh createCube(double side, const Point3& center);
};


#endif //FP3D_MESH_H
