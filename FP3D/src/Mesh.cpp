//
// Created by ccampo on 29/10/17.
//

#include "Mesh.h"

Mesh::Mesh(const std::vector<Point3> &triangles, const std::vector<uint> &indices) : vertices(triangles),
                                                                                    indices(indices) {}

Mesh Mesh::createCube(double side, const Point3& center) {
    double halfSide = side / 2;

    std::vector<Point3> points = {
            Point3(center.x - halfSide, center.y + halfSide, center.z - halfSide),
            Point3(center.x + halfSide, center.y + halfSide, center.z - halfSide),
            Point3(center.x + halfSide, center.y + halfSide, center.z + halfSide),
            Point3(center.x - halfSide, center.y + halfSide, center.z + halfSide),

            Point3(center.x - halfSide, center.y - halfSide, center.z - halfSide),
            Point3(center.x + halfSide, center.y - halfSide, center.z - halfSide),
            Point3(center.x + halfSide, center.y - halfSide, center.z + halfSide),
            Point3(center.x - halfSide, center.y - halfSide, center.z + halfSide)
    };

    std::vector<uint> indices = {
            0, 1, 3,
            2, 3, 1,

            4, 0, 5,
            1, 0, 5,

            5, 6, 1,
            2, 6, 1,

            6, 7, 2,
            3, 7, 2,

            7, 4, 3,
            0, 4, 3,

            5, 6, 4,
            7, 4, 6
    };

    return Mesh(points, indices);
}

Mesh Mesh::createPyramid(double side, double height, const Point3& center) {
    double halfSide = side / 2;
    double halfHeight = height / 2;

    std::vector<Point3> points = {
            Point3(center.x - halfSide, center.y - halfHeight, center.z - halfSide),
            Point3(center.x + halfSide, center.y - halfHeight, center.z - halfSide),
            Point3(center.x + halfSide, center.y - halfHeight, center.z + halfSide),
            Point3(center.x - halfSide, center.y - halfHeight, center.z + halfSide),
            Point3(center.x, center.y + halfHeight, center.z)
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
