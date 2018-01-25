//
// Created by ccampo on 15/01/18.
//

#include <Scene.h>
#include <RayCastingRenderer.h>
#include "RayTraceViewer.h"

BEGIN_EVENT_TABLE(RayTraceViewer, wxPanel)
    EVT_PAINT(RayTraceViewer::showImage)
END_EVENT_TABLE()

RayTraceViewer::RayTraceViewer(wxFrame* parent)
        : wxPanel(parent) {
    Vector3 cubeCenter = Vector3(-1, 0.5, 2);
    Vector3 pyramidCenter = Vector3(1, -0.5f, 2);

    Mesh cube = Mesh::createCube(1, cubeCenter);
    cube.material = Material(ColorRGB(0.5, 0.8, 1.0));

    Mesh pyramid = Mesh::createPyramid(1, 1, pyramidCenter);
    pyramid.material = Material(ColorRGB(1.0, 0.8, 0.5));

    Mesh plane = Mesh::createPlane(1, cubeCenter);

    Camera camera = Camera(Vector3(0, 0, 0), 100, 0.1f, 100, 400, 300);
    std::vector<Mesh> meshes = std::vector<Mesh>({pyramid, cube});

    Scene* scene = new Scene(meshes, camera);
    Light light(Vector3(-1, 2, 2));
    scene->lights.push_back(light);

    RayCastingRenderer renderer = RayCastingRenderer(scene);
    renderer.render();

    img = new wxImage(camera.width, camera.height, renderer.image, false);
    bmp = new wxBitmap(*img, wxBITMAP_SCREEN_DEPTH);
}

void RayTraceViewer::showImage(wxPaintEvent& ev) {
    wxPaintDC dc(this);
    dc.DrawBitmap(*bmp, 0, 0, false);
}