//
// Created by Cosimo Campo on 28/12/2017.
//

#ifndef WXTEST_MAINWINDOW_H
#define WXTEST_MAINWINDOW_H

#include <wx/wx.h>
#include <Scene.h>

class MainWindow : public wxFrame {
public:
    MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    Scene* createScene();

    wxDECLARE_EVENT_TABLE();
};

#endif //WXTEST_MAINWINDOW_H
