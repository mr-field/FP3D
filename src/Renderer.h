//
// Created by ccampo on 15/01/18.
//

#ifndef FP3D_RENDERER_H
#define FP3D_RENDERER_H

#include <Scene.h>

class Renderer {
public:
    virtual void render() = 0;

protected:
    Renderer(Scene* scene) : scene(scene) {};
    Scene* scene;
};

#endif //FP3D_RENDERER_H
