//
// Created by ccampo on 22/01/18.
//

#include "ControlPanel.h"

ControlPanel::ControlPanel(wxFrame* parent)
        : wxPanel(parent) {
    wxButton* button = new wxButton(this, wxID_ANY, "Test");
}