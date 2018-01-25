#include <iostream>
#include "App.h"
#include "MainWindow.h"
#include "OGLViewer.h"
#include "RayTraceViewer.h"
#include "ControlPanel.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_MENU(wxID_EXIT, MainWindow::OnExit)
    EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainWindow* mainWindow = new MainWindow("FP3D demo", wxPoint(50, 50), wxSize(800, 600));
    mainWindow->Show(true);

    wxGLAttributes attrs;
    attrs.PlatformDefaults().Defaults().EndList();

    //OGLViewer* ogl = new OGLViewer(mainWindow, attrs, 800, 600);
    //ogl->Show(true);

    ControlPanel* controlPanel = new ControlPanel(mainWindow);
    controlPanel->SetSize(100, 100);

    RayTraceViewer* rayTraceViewer = new RayTraceViewer(mainWindow);
    rayTraceViewer->SetSize(100, 0, 400, 300);

    return true;
}