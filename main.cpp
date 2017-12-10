#include <Scene.h>
#include <OGLRenderer.h>
#include "Mesh.h"
#include <cmath>

int main() {
    Vector3 cubeCenter = Vector3(1, 0, 2);
    Vector3 pyramidCenter = Vector3(-1, 0, 2);

    Mesh cube = Mesh::createCube(1, cubeCenter);
    cube.material = Material(ColorRGB(0.0, 0.1, 0.9));

    Mesh pyramid = Mesh::createPyramid(1, 1, pyramidCenter);
    pyramid.translate(Vector3(-1, 0, 0));
    pyramid.scale(2);
    pyramid.rotateX((180 * M_PI) / 180);
    pyramid.material = Material(ColorRGB(0.1, 0.9, 0.2));

    Mesh obj = Mesh::importObj("sample-obj/alfa147.obj");
    obj.translate(Vector3(-2, -0.5f, 0));
    obj.rotateX(-90 * M_PI / 180);
    obj.scale(0.01);
    obj.material = Material(ColorRGB(0.9, 0.1, 0.0));

    Camera camera = Camera(Vector3(0, 0, 0), 100, 0.1, 100, 800, 600);
    //camera.rotateY((45 * M_PI) / 180);
    std::vector<Mesh> meshes = std::vector<Mesh>({pyramid, cube, obj});

    Scene scene = Scene(meshes, camera);
    Light light(Vector3(10, 0, -5));
    scene.lights.push_back(light);

    OGLRenderer renderer = OGLRenderer(scene);
    renderer.render();
}
