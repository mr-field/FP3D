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

    wxGridSizer* sizer = new wxGridSizer(2);

    Scene* scene = createScene();

    RayTraceViewer* rayTraceViewer = new RayTraceViewer(this, scene);
    ControlPanel* controlPanel = new ControlPanel(this, rayTraceViewer);

    sizer->Add(controlPanel, 1, wxEXPAND);
    sizer->Add(rayTraceViewer, 1, wxEXPAND);

    SetSizer(sizer);
}

Scene* MainWindow::createScene() {
    Camera camera = Camera(Vector3(0, 0, 0), 75, 0.1f, 100, 250, 250);
    Scene* scene = new Scene(camera);
    
    Vector3 cube1Center = Vector3(-1, 0, 2);
    Mesh cube1 = Mesh::createCube(1, cube1Center);
    cube1.material = Material(ColorRGB(0, 0, 1));
    scene->addMesh(cube1);

    Vector3 cube2Center = Vector3(1, 0, 2);
    Mesh cube2 = Mesh::createCube(1, cube2Center);
    cube2.material = Material(ColorRGB(1, 0, 0));
    scene->addMesh(cube2);

    Vector3 cube3Center = Vector3(0, 0, 2);
    Mesh cube3 = Mesh::createCube(5, cube3Center);
    cube3.flipNormals();
    cube3.material = Material(ColorRGB(1, 1, 1));
    scene->addMesh(cube3);

    Vector3 planeCenter = Vector3(0, -0.5f, 2);
    Mesh plane = Mesh::createPlane(10, planeCenter);
    plane.material = Material(ColorRGB(1, 1, 1));
    scene->addMesh(plane);

    Mesh obj = Mesh::importObj("sample-obj/teapot.obj");
    obj.translate(Vector3(0.8f, -0.1f, 2));
    obj.scale(0.01);
    obj.material = Material(ColorRGB(0.9, 0.1, 0.0));
    //scene->addMesh(obj);

    Light light(Vector3(1, 1, 0));
    light.color = ColorRGB(1, 1, 1);
    light.intensity = 300;
    scene->lights.push_back(light);

    return scene;
}

void MainWindow::OnAbout(wxCommandEvent& event) {
    wxMessageBox("A demo program for FP3D", "About", wxOK);
}

void MainWindow::OnExit(wxCommandEvent& event) {
    Close(true);
}
