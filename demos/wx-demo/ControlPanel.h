//
// Created by ccampo on 22/01/18.
//

#ifndef FP3D_CONTROLPANEL_H
#define FP3D_CONTROLPANEL_H

#include <wx/wx.h>
#include "RayTraceViewer.h"

class ControlPanel : public wxPanel {
public:
    ControlPanel(wxFrame* parent, RayTraceViewer* viewer);

    wxDECLARE_EVENT_TABLE();
    enum {ID_RENDER = 101};

private:
    RayTraceViewer* viewer;
    wxTextCtrl* lightX;
    wxTextCtrl* lightY;
    wxTextCtrl* lightZ;
    wxTextCtrl* maxPasses;
    wxTextCtrl* side;

    void refreshView(wxCommandEvent& event);
};


#endif //FP3D_CONTROLPANEL_H
