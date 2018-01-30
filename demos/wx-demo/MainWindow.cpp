//
// Created by Cosimo Campo on 28/12/2017.
//

#include <wx/glcanvas.h>
#include "MainWindow.h"
#include "RayTraceViewer.h"
#include "ControlPanel.h"

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );

    wxGLAttributes attrs;
    attrs.PlatformDefaults().Defaults().EndList();

    //OGLViewer* ogl = new OGLViewer(mainWindow, attrs, 800, 600);
    //ogl->Show(true);

    wxGridSizer* sizer = new wxGridSizer(2);

    RayTraceViewer* rayTraceViewer = new RayTraceViewer(this);
    ControlPanel* controlPanel = new ControlPanel(this, rayTraceViewer);

    sizer->Add(controlPanel, 1, wxEXPAND);
    sizer->Add(rayTraceViewer, 1, wxEXPAND);

    SetSizer(sizer);
}

void MainWindow::OnAbout(wxCommandEvent& event) {
    wxMessageBox("A demo program for FP3D", "About", wxOK);
}

void MainWindow::OnExit(wxCommandEvent& event) {
    Close(true);
}
