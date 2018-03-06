//
// Created by ccampo on 15/01/18.
//

#ifndef FP3D_RAYTRACEVIEWER_H
#define FP3D_RAYTRACEVIEWER_H

#include <wx/wx.h>
#include <Scene.h>

class RayTraceViewer : public wxPanel {
public:
    wxImage* img;
    wxBitmap* bmp;
    Scene* scene;

    RayTraceViewer(wxFrame* parent, Scene* scene);
    void render();

    DECLARE_EVENT_TABLE();

private:
    void showImage(wxPaintEvent& ev);
};

#endif //FP3D_RAYTRACEVIEWER_H
