//
// Created by ccampo on 15/01/18.
//

#include <RayCastingRenderer.h>
#include "RayTraceViewer.h"

BEGIN_EVENT_TABLE(RayTraceViewer, wxPanel)
    EVT_PAINT(RayTraceViewer::showImage)
END_EVENT_TABLE()

RayTraceViewer::RayTraceViewer(wxFrame* parent, Scene* scene)
        : wxPanel(parent), scene(scene) {
    img = new wxImage(scene->camera.width, scene->camera.height, {}, false);
    bmp = new wxBitmap(*img, wxBITMAP_SCREEN_DEPTH);
}

void RayTraceViewer::render() {
    RayCastingRenderer renderer = RayCastingRenderer(scene, maxPasses);
    renderer.render();

    img = new wxImage(scene->camera.width, scene->camera.height, renderer.image, false);
    bmp = new wxBitmap(*img, wxBITMAP_SCREEN_DEPTH);
    bmp->SaveFile("render.png", wxBITMAP_TYPE_PNG);
}

void RayTraceViewer::showImage(wxPaintEvent& ev) {
    wxPaintDC dc(this);
    dc.DrawBitmap(*bmp, 0, 0, false);
}