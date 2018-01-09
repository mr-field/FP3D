//
// Created by Cosimo Campo on 30/12/2017.
//

#include <Scene.h>
#include "OGLViewer.h"

BEGIN_EVENT_TABLE(OGLViewer, wxGLCanvas)
    EVT_PAINT(OGLViewer::render)
    EVT_SIZE(OGLViewer::onSize)
END_EVENT_TABLE()

OGLViewer::OGLViewer(wxFrame *parent, const wxGLAttributes& canvasAttrs, int width, int height) :
        wxGLCanvas(parent, canvasAttrs, wxID_ANY, wxDefaultPosition, wxSize(width, height)) {

    wxGLContextAttrs attrs;
    attrs.PlatformDefaults().CoreProfile().OGLVersion(4, 0).ForwardCompatible().EndList();
    context = new wxGLContext(this, nullptr, &attrs);
    SetCurrent(*context);
    setupScene();
}

void OGLViewer::setupScene() {
    Vector3 cubeCenter = Vector3(-1, 0.5, 2);
    Vector3 pyramidCenter = Vector3(1, -0.5f, 2);

    Mesh cube = Mesh::createCube(1, cubeCenter);
    cube.material = Material(ColorRGB(0.5, 0.8, 1.0));

    Mesh pyramid = Mesh::createPyramid(1, 1, pyramidCenter);
    pyramid.material = Material(ColorRGB(1.0, 0.8, 0.5));

    Camera camera = Camera(Vector3(0, 0, 0), 100, 0.1, 100, 800, 600);
    std::vector<Mesh> meshes = std::vector<Mesh>({pyramid, cube});

    Scene* scene = new Scene(meshes, camera);
    Light light(Vector3(-10, 0, -5));
    scene->lights.push_back(light);

    renderer = new OGLRenderer(scene);
}

void OGLViewer::onSize(wxSizeEvent &sizeEvent) {
    sizeEvent.Skip();

    if (!IsShownOnScreen()) {
        return;
    }
    PostSizeEvent();
}

void OGLViewer::render(wxPaintEvent& evt) {
    wxPaintDC dc(this);
    renderer->render();
    SwapBuffers();
}
