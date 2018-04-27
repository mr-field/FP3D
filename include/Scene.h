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
    Scene(Camera& camera) : camera(camera) {}

    void addMesh(Mesh& mesh);
    void addLight(Light& light);

    Camera camera;
    std::vector<Mesh> meshes;
    std::vector<Light> lights;
};

#endif //FP3D_SCENE_H
