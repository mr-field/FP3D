//
// Created by Cosimo Campo on 28/12/2017.
//

#include "MainWindow.h"

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
}

void MainWindow::OnAbout(wxCommandEvent& event) {
    wxMessageBox("A demo program for FP3D", "About", wxOK);
}

void MainWindow::OnExit(wxCommandEvent& event) {
    Close(true);
}
