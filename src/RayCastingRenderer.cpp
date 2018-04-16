//
// Created by ccampo on 15/01/18.
//

#include "RayCastingRenderer.h"
#include <functional>
#include <thread>

RayCastingRenderer::RayCastingRenderer(Scene *scene, int maxPasses) : Renderer(scene), maxPasses(maxPasses) {
    width = scene->camera.width;
    height = scene->camera.height;
    origin = scene->camera.transform.position();

    image = new unsigned char[width*height*3];
    for (int i = 0; i < width*height; i++) {
        image[i*3] = 0;
        image[i*3+1] = 0;
        image[i*3+2] = 0;
    }
}


RayHit RayCastingRenderer::getClosestIntersection(Scene* scene, Ray& ray) {
    RayHit result;
    float closest = scene->camera.farPlane;

    for (Mesh &mesh : scene->meshes) {
        Matrix4 inverseTransform = mesh.transform.invert();
        Vector3 rayOrigin = inverseTransform * ray.origin;
        Vector3 rayDirection = inverseTransform.multiply3x3(ray.direction);

        for (Triangle &t : mesh.triangles) {
            float planeIntersection = ((t.a.position - rayOrigin).dot(t.normal)) / (rayDirection.dot(t.normal));
            if (planeIntersection < 0.0001f || planeIntersection > closest) {
                continue;
            }

            Vector3& a = t.a.position;
            Vector3& b = t.b.position;
            Vector3& c = t.c.position;

            Vector3 ab = (b - a).cross(t.normal);
            float n = (c - a).dot(ab);
            ab /= n;

            Vector3 ac = (c - a).cross(t.normal);
            float n2 = (b - a).dot(ac);
            ac /= n2;

            Vector3 q = rayOrigin + (rayDirection * planeIntersection);
            float gamma = (q - c).dot(ac);
            float beta = (q - b).dot(ab);
            float alpha = 1 - (gamma + beta);

            if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1) {
                closest = planeIntersection;
                Vector3 shadingNormal = mesh.transform.multiply3x3(t.a.normal * alpha + t.b.normal * gamma + t.c.normal * beta).normalise();
                result = RayHit(planeIntersection, mesh.transform * q, shadingNormal, &t, &mesh);
            }
        }
    }

    return result;
}


float clamp(float n, float max) {
    if (n > max) {
        n = max;
    }
    return n;
}


ColorRGB RayCastingRenderer::sampleDirectLight(SurfaceElement& surfaceElement) {
    ColorRGB directLight(0, 0, 0);

    for (Light& light : scene->lights) {
        Vector3 lightDirection = light.transform.position() - surfaceElement.position;
        Ray lightRay = Ray(surfaceElement.position, lightDirection);

        RayHit lightRayObstacleIntersection = getClosestIntersection(scene, lightRay);
        Vector3& obstacle = lightRayObstacleIntersection.intersectionPoint;
        Vector3 obstacleDirection = obstacle - surfaceElement.position;

        if (obstacle.magnitude() == 0 || obstacleDirection.magnitude() > lightDirection.magnitude()) {
            float cosine = (lightRay.direction.normalise()).dot(surfaceElement.normal);
            float attLight = std::max(0.0f, cosine) / (lightDirection.magnitude() * lightDirection.magnitude());
            directLight = light.color * surfaceElement.material->color * light.intensity * attLight;
        }
    }
    return directLight;
}


ColorRGB RayCastingRenderer::sampleRay(Ray& ray, int count) {
    ColorRGB pixelColor = ColorRGB(0, 0, 0);

    RayHit eyeRaySceneCollision = getClosestIntersection(scene, ray);
    Vector3& surfacePoint = eyeRaySceneCollision.intersectionPoint;

    if (surfacePoint.x == 0 && surfacePoint.y == 0 && surfacePoint.z == 0) {
        return pixelColor;
    }

    Vector3& surfaceNormal = eyeRaySceneCollision.shadingNormal;
    SurfaceElement surfaceElement(surfacePoint, surfaceNormal, &eyeRaySceneCollision.collider->material);

    pixelColor += sampleDirectLight(surfaceElement);

    Vector3 pointless(0, 1, 1);
    if (surfaceNormal == pointless) {
        pointless = Vector3(1, 0, 0);
    }
    Vector3 localX = surfaceNormal.cross(pointless);
    Vector3 localZ = surfaceNormal.cross(localX);
    Matrix4 frame = Matrix4::buildGenericMatrix(localX, surfaceNormal, localZ);

    ColorRGB indirectLight(0, 0, 0);
    int indirectRays = 3;
    if (count < indirectRays) {
        float theta = distribution2PI(generator);
        float s = distribution(generator);
        float y = sqrtf(s);
        float r = sqrtf(1.0f - y * y);

        Vector3 sample = Vector3(r * cosf(theta), y, r * sinf(theta));
        sample *= frame;
        Vector3 dispPoint = surfacePoint + surfaceNormal * 0.001f;
        Ray bounceRay(dispPoint, sample);

        float density = y / M_PI;
        float cosine = (sample.normalise()).dot(surfaceElement.normal);
        indirectLight += (sampleRay(bounceRay, ++count) * std::max(0.0f, cosine)) / density;
    }
    indirectLight /= indirectRays;
    pixelColor += surfaceElement.material->color * indirectLight;

    return pixelColor;
}


void RayCastingRenderer::doPasses(int passes, PixelColors* threadImage, std::vector<std::vector<Vector3>>* eyeRayDirections) {
    for (int pass = 0; pass < passes; pass++) {
        //std::cout << pass << std::endl;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                //Vector3 direction = eyeRayDirections[y][x] - Vector3(0,0,0);
                Ray eyeRay = Ray(origin, (*eyeRayDirections)[y][x]);
                (*threadImage)[y][x] += sampleRay(eyeRay, 0);
            }
        }
    }
}

void RayCastingRenderer::render() {
    std::vector<std::vector<Vector3>> eyeRayDirections;
    PixelColors pixelColors;
    for (float y = 1; y > -1; y=y-(1.0f/height*2.0f)) {
        std::vector<Vector3> row;
        std::vector<ColorRGB> pixelRow;
        for (float x = -1; x < 1; x=x+(1.0f/width*2.0f)) {
            row.emplace_back(Vector3(x, y, 1));
            pixelRow.emplace_back(ColorRGB(0, 0, 0));
        }
        eyeRayDirections.emplace_back(row);
        pixelColors.emplace_back(pixelRow);
    }

    int max_threads = std::thread::hardware_concurrency();
    int passes_per_thread = maxPasses / max_threads;
    std::vector<std::thread> threads;
    std::vector<PixelColors> threadImages;

    for (int i = 0; i < max_threads; i++) {
        threadImages.emplace_back(PixelColors(pixelColors));
    }
    for (int i = 0; i < max_threads; i++) {
        threads.emplace_back(std::thread(&RayCastingRenderer::doPasses, this, passes_per_thread, &threadImages[i], &eyeRayDirections));
    }
    for (int i = 0; i < max_threads; i++) {
        threads[i].join();
    }

    for (PixelColors& threadImage : threadImages) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                pixelColors[y][x] += threadImage[y][x];
            }
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = ((y * scene->camera.width) + x) * 3;
            ColorRGB& pixelColor = pixelColors[y][x];
            image[index] = clamp(pixelColor.x / maxPasses, 255);
            image[index + 1] = clamp(pixelColor.y / maxPasses, 255);
            image[index + 2] = clamp(pixelColor.z / maxPasses, 255);
        }
    }
}
