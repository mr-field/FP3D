//
// Created by ccampo on 22/01/18.
//

#include "ControlPanel.h"

BEGIN_EVENT_TABLE(ControlPanel, wxPanel)
    EVT_BUTTON(ID_RENDER, ControlPanel::refreshView)
END_EVENT_TABLE()

ControlPanel::ControlPanel(wxFrame* parent, RayTraceViewer* viewer)
        : wxPanel(parent), viewer(viewer) {
    lightX = new wxTextCtrl(this, wxID_ANY);
    lightY = new wxTextCtrl(this, wxID_ANY);
    lightZ = new wxTextCtrl(this, wxID_ANY);

    wxBoxSizer* textboxSizer = new wxBoxSizer(wxHORIZONTAL);
    textboxSizer->Add(new wxStaticText(this, wxID_ANY, "X"), 0, wxALL, 5);
    textboxSizer->Add(lightX, 0, wxALL, 5);
    textboxSizer->Add(new wxStaticText(this, wxID_ANY, "Y"), 0, wxALL, 5);
    textboxSizer->Add(lightY, 0, wxALL, 5);
    textboxSizer->Add(new wxStaticText(this, wxID_ANY, "Z"), 0, wxALL, 5);
    textboxSizer->Add(lightZ, 0, wxALL, 5);

    wxBoxSizer* cameraSizer = new wxBoxSizer(wxHORIZONTAL);
    cameraSizer->Add(new wxStaticText(this, wxID_ANY, "Image side (px)"), 0, wxALL, 5);
    side = new wxTextCtrl(this, wxID_ANY);
    cameraSizer->Add(side, 0, wxALL, 5);

    wxBoxSizer* itSizer = new wxBoxSizer(wxHORIZONTAL);
    itSizer->Add(new wxStaticText(this, wxID_ANY, "Iterations"), 0, wxALL, 5);
    maxPasses = new wxTextCtrl(this, wxID_ANY);
    itSizer->Add(maxPasses, 0, wxALL, 5);

    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    panelSizer->Add(new wxStaticText(this, wxID_ANY, "Light position:"), 0, wxALL, 5);
    panelSizer->Add(textboxSizer, 0, wxALIGN_CENTER);
    panelSizer->Add(0, 20, 0);
    panelSizer->Add(cameraSizer);
    panelSizer->Add(itSizer);
    panelSizer->Add(0, 20, 0);
    panelSizer->Add(new wxButton(this, ID_RENDER, "Render"), 0, wxALL, 5);

    SetSizerAndFit(panelSizer);
}

void ControlPanel::refreshView(wxCommandEvent& event) {
    double x, y, z;
    lightX->GetValue().ToDouble(&x);
    lightY->GetValue().ToDouble(&y);
    lightZ->GetValue().ToDouble(&z);
    Vector3 position = Vector3(x, y, z);
    viewer->scene->lights[0].setPosition(position);

    long imageSide;
    side->GetValue().ToLong(&imageSide);
    viewer->scene->camera.width = imageSide;
    viewer->scene->camera.height = imageSide;

    long passes;
    maxPasses->GetValue().ToLong(&passes);
    viewer->renderer->maxPasses = passes;

    viewer->render();
    viewer->Refresh();
}