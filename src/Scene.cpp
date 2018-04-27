//
// Created by ccampo on 27/04/18.
//

#include <Scene.h>

void Scene::addMesh(Mesh &mesh) {
    meshes.emplace_back(mesh);
}

void Scene::addLight(Light &light) {
    lights.emplace_back(light);
}
