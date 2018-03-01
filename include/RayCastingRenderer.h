//
// Created by ccampo on 15/01/18.
//

#ifndef FP3D_RAYCASTINGRENDERER_H
#define FP3D_RAYCASTINGRENDERER_H


#include <Renderer.h>
#include <random>
#include <chrono>
#include "RayHit.h"
#include "Ray.h"

struct SurfaceElement {
    Vector3 position;
    Vector3 normal;
    Material* material;

    SurfaceElement(Vector3& position, Vector3& normal, Material* material) :
            position(position),
            normal(normal),
            material(material)
    {};
};

class RayCastingRenderer : public Renderer {
public:
    RayCastingRenderer(Scene* scene);
    void render() override;
    unsigned char* image;

private:
    std::default_random_engine generator = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> distribution = std::uniform_real_distribution<float> (0.0f, 1.0f);
    std::uniform_real_distribution<float> distribution2PI = std::uniform_real_distribution<float> (0.0f, 2 * M_PI);

    ColorRGB sampleDirectLight(SurfaceElement& surfaceElement);
    ColorRGB sampleIndirectLight(SurfaceElement& surfaceElement);
    ColorRGB sampleRay(Ray& ray, int count);
    RayHit getClosestIntersection(Scene* scene, Ray& ray);
};


#endif //FP3D_RAYCASTINGRENDERER_H
