//
// Created by ccampo on 15/01/18.
//

#include "RayCastingRenderer.h"
#include <cmath>

RayCastingRenderer::RayCastingRenderer(Scene *scene) : Renderer(scene) {
    int width = scene->camera.width;
    int height = scene->camera.height;

    image = new unsigned char[width*height*3];
    for (int i = 0; i < width*height; i++) {
        image[i*3] = 0;
        image[i*3+1] = 0;
        image[i*3+2] = 100;
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
            ab = ab * (1 / n);

            Vector3 ac = (c - a).cross(t.normal);
            float n2 = (b - a).dot(ac);
            ac = ac * (1 / n2);

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

void RayCastingRenderer::render() {
    Vector3 origin = scene->camera.transform.position();
    int width = scene->camera.width;
    int height = scene->camera.height;

    std::vector<std::vector<Vector3>> pixels;
    for (float y = 1; y > -1; y=y-(1.0f/height*2.0f)) {
        std::vector<Vector3> row;
        for (float x = -1; x < 1; x=x+(1.0f/width*2.0f)) {
            row.emplace_back(Vector3(x, y, 1));
        }
        pixels.emplace_back(row);
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //Vector3 direction = pixels[y][x] - Vector3(0,0,0);
            Ray eyeRay = Ray(origin, pixels[y][x]);

            RayHit eyeRaySceneCollision = getClosestIntersection(scene, eyeRay);
            Vector3 surfacePoint = eyeRaySceneCollision.intersectionPoint;

            if (surfacePoint.x == 0 && surfacePoint.y == 0 && surfacePoint.z == 0) {
                continue;
            }

            Vector3 lightDirection = scene->lights[0].transform.position() - surfacePoint;
            Ray lightRay = Ray(surfacePoint, lightDirection);

            RayHit lightRayObstacleIntersection = getClosestIntersection(scene, lightRay);
            Vector3 obstacle = lightRayObstacleIntersection.intersectionPoint;
            Vector3 obstacleDirection = obstacle - surfacePoint;

            int index = ((y*scene->camera.width) + x) * 3;
            image[index+2] = 0;
            if (obstacle.magnitude() != 0 && obstacleDirection.magnitude() < lightDirection.magnitude()) {
                image[index] = 0;
            }
            else if (surfacePoint.z > scene->camera.near && surfacePoint.z < scene->camera.far) {
                float cosine = (lightRay.direction.normalise()).dot(eyeRaySceneCollision.triangle->normal);

                ColorRGB attLight = scene->lights[0].color;
                float n = 255.0f * (1/(lightDirection.magnitude() * lightDirection.magnitude())) * std::abs(cosine);
                if (n > 255.0f) n = 255.0f;

                ColorRGB finalColor = (attLight * eyeRaySceneCollision.collider->material.color).normalise() * n;

                image[index] = finalColor.x;
                image[index+1] = finalColor.y;
                image[index+2] = finalColor.z;
            }
        }
    }
}
