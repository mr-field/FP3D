//
// Created by ccampo on 29/10/17.
//

#include "Mesh.h"
#include "Vertex.h"
#include "Triangle.h"

Mesh::Mesh(const std::vector<Vector3> &points, const std::vector<uint> &indices, const Vector3& center) : Object3D(center) {
    for (unsigned int i = 0; i < indices.size(); i += 3) {
        Vertex a = Vertex(points[indices[i]], Vector3(0, 0, 0));
        Vertex b = Vertex(points[indices[i+1]], Vector3(0, 0, 0));
        Vertex c = Vertex(points[indices[i+2]], Vector3(0, 0, 0));

        Vector3 ba = a.position - b.position;
        Vector3 bc = c.position - b.position;
        Vector3 normal = bc.cross(ba);

        a.normal = normal;
        b.normal = normal;
        c.normal = normal;

        Triangle t(a, b, c);
        triangles.push_back(t);
        vertices.push_back(a);
        vertices.push_back(b);
        vertices.push_back(c);
    }
}

Mesh Mesh::createCube(float side, const Vector3& center) {
    float halfSide = side / 2;

    std::vector<Vector3> points = {
            Vector3(-halfSide, halfSide, -halfSide),
            Vector3(halfSide, halfSide, -halfSide),
            Vector3(halfSide, halfSide, halfSide),
            Vector3(-halfSide, halfSide, halfSide),

            Vector3(-halfSide, -halfSide, -halfSide),
            Vector3(halfSide, -halfSide, -halfSide),
            Vector3(halfSide, -halfSide, halfSide),
            Vector3(-halfSide, -halfSide, halfSide)
    };

    std::vector<uint> indices = {
            1, 0, 2,
            3, 2, 0,

            5, 4, 1,
            0, 1, 4,

            6, 5, 2,
            1, 2, 5,

            7, 6, 3,
            2, 3, 6,

            4, 7, 0,
            3, 0, 7,

            5, 6, 4,
            7, 5, 6
    };

    return Mesh(points, indices, center);
}

Mesh Mesh::createPyramid(float side, float height, const Vector3& center) {
    float halfSide = side / 2;
    float halfHeight = height / 2;

    std::vector<Vector3> points = {
            Vector3(-halfSide, -halfHeight, -halfSide),
            Vector3(halfSide, -halfHeight, -halfSide),
            Vector3(halfSide, -halfHeight, halfSide),
            Vector3(-halfSide, -halfHeight, halfSide),
            Vector3(0, halfHeight, 0)
    };

    std::vector<uint> indices = {
            0, 1, 3,
            2, 3, 1,

            4, 1, 0,
            4, 2, 1,
            4, 2, 3,
            4, 3, 1,
    };

    Mesh m = Mesh(points, indices, center);
    return m;
}
