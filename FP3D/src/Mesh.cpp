//
// Created by ccampo on 29/10/17.
//

#include "Mesh.h"
#include "Vertex.h"
#include "Triangle.h"

Mesh::Mesh(const std::vector<Vector3> &points, const std::vector<uint> &indices) {
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

Mesh Mesh::createCube(double side, const Point3& center) {
    double halfSide = side / 2;

    std::vector<Vector3> points = {
            Vector3(center.x - halfSide, center.y + halfSide, center.z - halfSide),
            Vector3(center.x + halfSide, center.y + halfSide, center.z - halfSide),
            Vector3(center.x + halfSide, center.y + halfSide, center.z + halfSide),
            Vector3(center.x - halfSide, center.y + halfSide, center.z + halfSide),

            Vector3(center.x - halfSide, center.y - halfSide, center.z - halfSide),
            Vector3(center.x + halfSide, center.y - halfSide, center.z - halfSide),
            Vector3(center.x + halfSide, center.y - halfSide, center.z + halfSide),
            Vector3(center.x - halfSide, center.y - halfSide, center.z + halfSide)
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

    return Mesh(points, indices);
}

Mesh Mesh::createPyramid(double side, double height, const Point3& center) {
    double halfSide = side / 2;
    double halfHeight = height / 2;

    std::vector<Vector3> points = {
            Vector3(center.x - halfSide, center.y - halfHeight, center.z - halfSide),
            Vector3(center.x + halfSide, center.y - halfHeight, center.z - halfSide),
            Vector3(center.x + halfSide, center.y - halfHeight, center.z + halfSide),
            Vector3(center.x - halfSide, center.y - halfHeight, center.z + halfSide),
            Vector3(center.x, center.y + halfHeight, center.z)
    };

    std::vector<uint> indices = {
            0, 1, 3,
            2, 3, 1,

            4, 1, 0,
            4, 2, 1,
            4, 2, 3,
            4, 3, 1,
    };

    return Mesh(points, indices);
}
