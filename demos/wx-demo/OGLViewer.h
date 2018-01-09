//
// Created by Cosimo Campo on 30/12/2017.
//

#ifndef WXTEST_OGLVIEWER_H
#define WXTEST_OGLVIEWER_H

#include <wx/wx.h>
#include <OGLRenderer.h>
#include <wx/glcanvas.h>


class OGLViewer : public wxGLCanvas {
public:
    OGLViewer(wxFrame* parent, const wxGLAttributes& canvasAttrs, int width, int height);
    void render(wxPaintEvent& evt);
    void onSize(wxSizeEvent& sizeEvent);

    DECLARE_EVENT_TABLE();
private:
    void setupScene();

    wxGLContext* context;
    OGLRenderer* renderer;
};


#endif //WXTEST_OGLVIEWER_H
