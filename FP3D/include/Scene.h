//
// Created by ccampo on 31/10/17.
//

#ifndef TESTEXEC_SCENE_H
#define TESTEXEC_SCENE_H

#include "Mesh.h"
#include "Camera.h"

class Scene {
public:
    Scene(const std::vector<Mesh> &meshes, const Camera &camera) : meshes(meshes), camera(camera) {}

    std::vector<Mesh> meshes;
    Camera camera;
};

#endif //TESTEXEC_SCENE_H
