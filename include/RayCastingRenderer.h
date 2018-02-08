//
// Created by ccampo on 15/01/18.
//

#ifndef FP3D_RAYCASTINGRENDERER_H
#define FP3D_RAYCASTINGRENDERER_H


#include <Renderer.h>
#include "RayHit.h"
#include "Ray.h"

class RayCastingRenderer : public Renderer {
public:
    RayCastingRenderer(Scene* scene);
    void render() override;
    unsigned char* image;

private:
    ColorRGB sampleRay(Ray& ray, int count);
    RayHit getClosestIntersection(Scene* scene, Ray& ray);
};


#endif //FP3D_RAYCASTINGRENDERER_H
