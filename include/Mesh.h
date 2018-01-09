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
#include "Material.h"

typedef unsigned int uint;

class Mesh : public Object3D {
public:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
    Material material = Material(ColorRGB(0.1, 0.1, 0.1));

    Mesh(const std::vector<Vector3> &points, const std::vector<uint> &indices, const Vector3& center);
    Mesh(std::vector<Triangle> &triangles);

    static Mesh createCube(float side, const Vector3& center);
    static Mesh createPyramid(float side, float height, const Vector3& center);
    static Mesh importObj(const char* filePath);
};


#endif //FP3D_MESH_H
