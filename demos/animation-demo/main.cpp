//
// Created by ccampo on 14/03/18.
//


#include <Scene.h>
#include <RayCastingRenderer.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <sstream>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

Scene* createScene() {
    Vector3 cube1Center = Vector3(-1, 0, 2);
    Mesh cube1 = Mesh::createCube(1, cube1Center);
    cube1.material = Material(ColorRGB(0, 0, 1));

    Vector3 cube2Center = Vector3(1, 0, 2);
    Mesh cube2 = Mesh::createCube(1, cube2Center);
    cube2.material = Material(ColorRGB(1, 0, 0));

    Vector3 cube3Center = Vector3(0, 0, 2);
    Mesh cube3 = Mesh::createCube(5, cube3Center);
    cube3.flipNormals();
    cube3.material = Material(ColorRGB(1, 1, 1));

    Vector3 planeCenter = Vector3(0, -0.5f, 2);
    Mesh plane = Mesh::createPlane(10, planeCenter);
    plane.material = Material(ColorRGB(1, 1, 1));

    Camera camera = Camera(Vector3(0, 0, 0), 75, 0.1f, 100, 500, 500);
    std::vector<Mesh> meshes = std::vector<Mesh>({cube1, cube3, cube2, plane});

    Scene* scene = new Scene(meshes, camera);

    Light light(Vector3(1, 1, 0));
    light.color = ColorRGB(1, 1, 1);
    light.intensity = 300;
    scene->lights.push_back(light);

    return scene;
}

int main() {
    Scene* scene = createScene();
    Light& light = scene->lights[0];

    RayCastingRenderer renderer = RayCastingRenderer(scene, 240);
    wxImage img = wxImage(scene->camera.width, scene->camera.height, renderer.image, false);
    wxPNGHandler handler = wxPNGHandler();
    img.AddHandler(&handler);

    for (int i = 100; i <= 300; i++) {
        std::cout << i << std::endl;
        light.setPosition(Vector3((i-200.0f)/100.0f, 1.1f, 2));
        renderer.render();
        std::stringstream s;
        s << "frame_" << i << ".png";
        img.SaveFile(s.str(), wxBITMAP_TYPE_PNG);
    }
}