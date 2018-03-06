//
// Created by Cosimo Campo on 30/12/2017.
//

#include <Scene.h>
#include "OGLViewer.h"

BEGIN_EVENT_TABLE(OGLViewer, wxGLCanvas)
    EVT_PAINT(OGLViewer::render)
    EVT_SIZE(OGLViewer::onSize)
END_EVENT_TABLE()

OGLViewer::OGLViewer(wxFrame *parent, const wxGLAttributes& canvasAttrs, Scene* scene) :
        wxGLCanvas(parent, canvasAttrs, wxID_ANY, wxDefaultPosition, wxSize(scene->camera.width, scene->camera.height)), scene(scene) {
    renderer = nullptr;
    panelHeight = 0;

    wxGLContextAttrs attrs;
    attrs.PlatformDefaults().CoreProfile().OGLVersion(4, 0).ForwardCompatible().EndList();
    context = new wxGLContext(this, nullptr, &attrs);
}

bool OGLViewer::setupScene() {
    if ( !context )
        return false;
    SetCurrent(*context);
    renderer = new OGLRenderer(scene);
    return true;
}

void OGLViewer::onSize(wxSizeEvent &sizeEvent) {
    sizeEvent.Skip();

    if (!IsShownOnScreen()) {
        return;
    }

    if (!renderer) {
        if (!setupScene()) {
            return;
        }
        PostSizeEvent();
    }

    panelHeight = sizeEvent.GetSize().y;
    Refresh(false);
}

void OGLViewer::render(wxPaintEvent& evt) {
    wxPaintDC dc(this);

    if (panelHeight < 1 || !renderer) {
        return;
    }

    renderer->render();
    SwapBuffers();
}
