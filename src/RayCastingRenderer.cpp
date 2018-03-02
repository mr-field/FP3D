//
// Created by ccampo on 15/01/18.
//

#include "RayCastingRenderer.h"
#include <functional>

RayCastingRenderer::RayCastingRenderer(Scene *scene) : Renderer(scene) {
    int width = scene->camera.width;
    int height = scene->camera.height;

    image = new unsigned char[width*height*3];
    for (int i = 0; i < width*height; i++) {
        image[i*3] = 0;
        image[i*3+1] = 0;
        image[i*3+2] = 0;
    }
}


RayHit RayCastingRenderer::getClosestIntersection(Scene* scene, Ray& ray) {
    RayHit result;
    float closest = scene->camera.far;

    for (Mesh &mesh : scene->meshes) {
        for (Triangle &t : mesh.triangles) {
            Vector3 a = mesh.transform * t.a.position;

            float planeIntersection = ((a - ray.origin).dot(t.normal)) / (ray.direction.dot(t.normal));
            if (planeIntersection < 0.0001f || planeIntersection > closest) {
                continue;
            }

            Vector3 b = mesh.transform * t.b.position;
            Vector3 c = mesh.transform * t.c.position;

            Vector3 ab = (b - a).cross(t.normal);
            float n = (c - a).dot(ab);
            ab *= (1 / n);

            Vector3 ac = (c - a).cross(t.normal);
            float n2 = (b - a).dot(ac);
            ac *= (1 / n2);

            Vector3 q = ray.origin + (ray.direction * planeIntersection);
            float gamma = (q - c).dot(ac);
            float beta = (q - b).dot(ab);
            float alpha = 1 - (gamma + beta);

            if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1) {
                closest = planeIntersection;
                result = RayHit(planeIntersection, q, &t, &mesh);
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

    Vector3& surfaceNormal = eyeRaySceneCollision.triangle->normal;
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


void RayCastingRenderer::render() {
    Vector3 origin = scene->camera.transform.position();
    int width = scene->camera.width;
    int height = scene->camera.height;

    std::vector<std::vector<Vector3>> eyeRayDirections;
    std::vector<std::vector<ColorRGB>> pixelColors;
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

    int max_pass = 5;
    for (int pass = 0; pass < max_pass; pass++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                //Vector3 direction = eyeRayDirections[y][x] - Vector3(0,0,0);
                Ray eyeRay = Ray(origin, eyeRayDirections[y][x]);
                pixelColors[y][x] += sampleRay(eyeRay, 0);
            }
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = ((y * scene->camera.width) + x) * 3;
            ColorRGB& pixelColor = pixelColors[y][x];
            image[index] = clamp(pixelColor.x / max_pass, 255);
            image[index + 1] = clamp(pixelColor.y / max_pass, 255);
            image[index + 2] = clamp(pixelColor.z / max_pass, 255);
        }
    }
}
