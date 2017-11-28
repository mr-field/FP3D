#include <Scene.h>
#include <OGLRenderer.h>
#include "Mesh.h"

int main() {
    Point3 cubeCenter = Point3(1, 0, 2);
    Point3 pyramidCenter = Point3(-1, 0, 2);

    Mesh cube = Mesh::createCube(1, cubeCenter);
    Mesh pyramid = Mesh::createPyramid(1, 1, pyramidCenter);

    Camera camera = Camera(Vector3(0, 0, 0), Vector3(0, 0, 2), 100, 0.1, 100, 800, 600);
    std::vector<Mesh> meshes = std::vector<Mesh>({cube, pyramid});
    Scene scene = Scene(meshes, camera);

    OGLRenderer renderer = OGLRenderer(scene);
    renderer.render();
}
