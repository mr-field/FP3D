//
// Created by ccampo on 15/01/18.
//

#ifndef FP3D_RAYCASTINGRENDERER_H
#define FP3D_RAYCASTINGRENDERER_H


#include <Renderer.h>

class RayCastingRenderer : public Renderer {
public:
    RayCastingRenderer(Scene* scene);
    void render() override;
    unsigned char* image;
};


#endif //FP3D_RAYCASTINGRENDERER_H
