//
// Created by ccampo on 15/01/18.
//

#ifndef FP3D_RAYTRACINGRENDERER_H
#define FP3D_RAYTRACINGRENDERER_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <Renderer.h>
#include <random>
#include <chrono>
#include "RayHit.h"
#include "Ray.h"

typedef std::vector<std::vector<ColorRGB>> PixelColors;

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

class RayTracingRenderer : public Renderer {
public:
    RayTracingRenderer(Scene* scene, int maxPasses);
    void render() override;
    unsigned char* image;
    int maxPasses;

    static const int MAX_INDIRECT_RAYS = 3;

private:
    int width, height;
    Vector3 origin =  Vector3(0, 0, 0);
    std::default_random_engine generator = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> distribution = std::uniform_real_distribution<float> (0.0f, 1.0f);
    std::uniform_real_distribution<float> distribution2PI = std::uniform_real_distribution<float> (0.0f, 2 * M_PI);

    ColorRGB sampleDirectLight(SurfaceElement& surfaceElement);
    ColorRGB sampleRay(Ray& ray, int count);
    void doPasses(int passes, PixelColors* threadImage, std::vector<std::vector<Vector3>>* eyeRayDirections);
    RayHit getClosestIntersection(Scene* scene, Ray& ray);
};


#endif //FP3D_RAYTRACINGRENDERER_H
