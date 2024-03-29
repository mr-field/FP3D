#include <iostream>
#include "App.h"
#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_MENU(wxID_EXIT, MainWindow::OnExit)
    EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainWindow* mainWindow = new MainWindow("FP3D demo", wxPoint(50, 50), wxSize(800, 600));
    mainWindow->Show(true);

    return true;
}