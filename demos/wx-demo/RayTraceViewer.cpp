//
// Created by ccampo on 15/01/18.
//

#include <RayCastingRenderer.h>
#include "RayTraceViewer.h"

BEGIN_EVENT_TABLE(RayTraceViewer, wxPanel)
    EVT_PAINT(RayTraceViewer::showImage)
END_EVENT_TABLE()

RayTraceViewer::RayTraceViewer(wxFrame* parent)
        : wxPanel(parent) {
    //Vector3 cubeCenter = Vector3(-2.8f, 0, 2);
    //Mesh cube = Mesh::createCube(6, cubeCenter);
    //cube.material = Material(ColorRGB(1, 0, 0));

    Vector3 cube1Center = Vector3(-1, 0, 2);
    Mesh cube1 = Mesh::createCube(1, cube1Center);
    cube1.material = Material(ColorRGB(0, 0, 1));

    Vector3 cube2Center = Vector3(1, 0, 2);
    Mesh cube2 = Mesh::createCube(1, cube2Center);
    cube2.material = Material(ColorRGB(1, 0, 0));

    Vector3 planeCenter = Vector3(0, -0.5f, 2);
    Mesh plane = Mesh::createPlane(10, planeCenter);
    plane.material = Material(ColorRGB(0.5f, 0.5f, 0.5f));

    Camera camera = Camera(Vector3(0, 0, 0), 100, 0.1f, 100, 400, 300);
    std::vector<Mesh> meshes = std::vector<Mesh>({plane, cube1, cube2});

    scene = new Scene(meshes, camera);

    Light light(Vector3(-1, 1, 2));
    light.color = ColorRGB(1, 1, 1);
    light.intensity = 300;

    Light light2(Vector3(0, 0, 0));
    light2.color = ColorRGB(1, 1, 1);

    scene->lights.push_back(light);
    //scene->lights.push_back(light2);

    render();
}

void RayTraceViewer::render() {
    RayCastingRenderer renderer = RayCastingRenderer(scene);
    renderer.render();

    img = new wxImage(scene->camera.width, scene->camera.height, renderer.image, false);
    bmp = new wxBitmap(*img, wxBITMAP_SCREEN_DEPTH);
}

void RayTraceViewer::showImage(wxPaintEvent& ev) {
    wxPaintDC dc(this);
    dc.DrawBitmap(*bmp, 0, 0, false);
}