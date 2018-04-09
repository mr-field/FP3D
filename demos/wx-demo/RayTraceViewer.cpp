//
// Created by ccampo on 15/01/18.
//

#include "RayTraceViewer.h"

BEGIN_EVENT_TABLE(RayTraceViewer, wxPanel)
    EVT_PAINT(RayTraceViewer::showImage)
END_EVENT_TABLE()

RayTraceViewer::RayTraceViewer(wxFrame* parent, Scene* scene)
        : wxPanel(parent), scene(scene) {
    renderer = new RayCastingRenderer(scene, 1);
    img = new wxImage(scene->camera.width, scene->camera.height, renderer->image, false);
    img->AddHandler(new wxPNGHandler());
    bmp = new wxBitmap(*img, wxBITMAP_SCREEN_DEPTH);
}

void RayTraceViewer::render() {
    renderer->render();

    img->SaveFile("render.png", wxBITMAP_TYPE_PNG);
    bmp = new wxBitmap(*img, wxBITMAP_SCREEN_DEPTH);
}

void RayTraceViewer::showImage(wxPaintEvent& ev) {
    wxPaintDC dc(this);
    dc.DrawBitmap(*bmp, 0, 0, false);
}