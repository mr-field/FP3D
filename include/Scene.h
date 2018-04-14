//
// Created by ccampo on 31/10/17.
//

#ifndef FP3D_SCENE_H
#define FP3D_SCENE_H

#include "Mesh.h"
#include "Camera.h"
#include "Light.h"

class Scene {
public:
    Scene(const std::vector<Mesh> &meshes, const Camera &camera) : meshes(meshes), camera(camera) {}

    Camera camera;
    std::vector<Mesh> meshes;
    std::vector<Light> lights;
};

#endif //FP3D_SCENE_H
