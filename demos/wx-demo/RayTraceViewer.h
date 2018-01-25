//
// Created by ccampo on 15/01/18.
//

#ifndef FP3D_RAYTRACEVIEWER_H
#define FP3D_RAYTRACEVIEWER_H

#include <wx/wx.h>

class RayTraceViewer : public wxPanel {
public:
    RayTraceViewer(wxFrame* parent);
    void showImage(wxPaintEvent& ev);

    wxImage* img;
    wxBitmap* bmp;

    DECLARE_EVENT_TABLE();
};

#endif //FP3D_RAYTRACEVIEWER_H
