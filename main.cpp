#include "Vector3.h"
#include "Mesh.h"

int main() {
    Vector3 v = Vector3(0, 0, 1);
    Vector3 v2 = Vector3(1, 0, 0);

    std::cout << v.cross(v2) << std::endl;

    Point3 center = Point3(0, 0, 0);
    Mesh mesh = Mesh::createCube(10, center);
    std::cout << mesh.vertices[0].x << std::endl;
}
