//
// Created by ccampo on 29/10/17.
//

#include "Mesh.h"
#include "Vertex.h"
#include "Triangle.h"
#include <string>
#include <sstream>
#include <fstream>

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

void Mesh::flipNormals() {
    for (Triangle& t : triangles) {
        t.a.normal *= -1.0f;
        t.b.normal *= -1.0f;
        t.c.normal *= -1.0f;
        t.normal = t.normal * -1.0f;
    }

    for(Vertex& v : vertices) {
        v.normal *= -1.0f;
    }
}

Mesh::Mesh(std::vector<Triangle> &triangles) : triangles(triangles) {
    for (Triangle& t : triangles) {
        vertices.push_back(t.a);
        vertices.push_back(t.b);
        vertices.push_back(t.c);
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
            7, 4, 6
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
            4, 3, 2,
            4, 0, 3,
    };

    return Mesh(points, indices, center);
}

Mesh Mesh::createPlane(float side, const Vector3 &center) {
    float halfSide = side / 2;

    std::vector<Vector3> points = {
            Vector3(-halfSide, 0, -halfSide),
            Vector3(halfSide, 0, -halfSide),
            Vector3(halfSide, 0, halfSide),
            Vector3(-halfSide, 0, halfSide),
    };

    std::vector<uint> indices = {
            1, 0, 2,
            3, 2, 0
    };

    return Mesh(points, indices, center);
}

Mesh Mesh::importObj(const char *filePath) {
    std::vector<Vector3> points;
    std::vector<Vector3> normals;
    std::vector<Triangle> triangles;

    std::ifstream inFile(filePath);
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream lineStream(line);
        std::string word;
        std::vector<std::string> words;

        while (std::getline(lineStream, word, ' ')) {
            words.push_back(word);
            while (isblank(lineStream.peek())) {
                lineStream.get();
            }
        }

        if (words.empty()) {
            continue;
        }

        if (words[0] == "v") {
            Vector3 position = Vector3(std::stof(words[1]), std::stof(words[2]), std::stof(words[3]));
            points.push_back(position);
        }
        else if (words[0] == "vn") {
            Vector3 normal = Vector3(std::stof(words[1]), std::stof(words[2]), std::stof(words[3]));
            normals.push_back(normal.normalise());
        }
        else if (words[0] == "f") {
            std::vector<Vertex> faceVertices;
            Vertex* vertex;
            for (int i = 1; i < 4; i++) {
                bool isComposite = words[i].find('/') == std::string::npos;
                if (isComposite) {
                    int index = std::stoi(words[i]) - 1;
                    Vector3 normal = (normals.empty()) ? Vector3(0, 0, 0) : normals[index];
                    vertex = new Vertex(points[index], normal);
                } else {
                    std::stringstream indicesStream(words[i]);
                    std::string index;
                    std::vector<int> indices;

                    while (std::getline(indicesStream, index, '/')) {
                        indices.push_back(stoi(index));
                    }

                    vertex = new Vertex(points[indices[0] - 1], normals[indices[2] - 1]);
                }
                faceVertices.push_back(*vertex);
                delete vertex;
            }

            triangles.emplace_back(Triangle(faceVertices[0], faceVertices[1], faceVertices[2]));
        }
    }

    return Mesh(triangles);
}
