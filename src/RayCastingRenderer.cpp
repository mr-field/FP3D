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
            Vector3 a = (mesh.transform * t.a.position);
            Vector3 b = (mesh.transform * t.b.position);
            Vector3 c = (mesh.transform * t.c.position);

            float planeIntersection = ((a - ray.origin).dot(t.normal)) / (ray.direction.dot(t.normal));
            if (planeIntersection < 0.0001f) {
                continue;
            }

            Vector3 q = ray.origin + (ray.direction * planeIntersection);
            float gamma = (q - c).dot(t.ac);
            float beta = (q - b).dot(t.ab);
            float alpha = 1 - (gamma + beta);

            if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1 && q.z < closest) {
                closest = q.z;
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
    float nearPlane = scene->camera.near;

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
            Vector3 direction = pixels[y][x] - origin;
            Ray eyeRay = Ray(origin, direction);

            RayHit eyeRaySceneCollision = getClosestIntersection(scene, eyeRay);
            Vector3 surfacePoint = eyeRaySceneCollision.intersectionPoint;

            if (surfacePoint.x == 0 && surfacePoint.y == 0 && surfacePoint.z == 0) {
                continue;
            }

            Light& light = scene->lights[0];
            Vector3 lightDirection = light.transform.position() - surfacePoint;
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
                float n = 255.0f * std::abs(cosine);

                image[index] = eyeRaySceneCollision.collider->material.color.x * n;
                image[index+1] = eyeRaySceneCollision.collider->material.color.y * n;
                image[index+2] = eyeRaySceneCollision.collider->material.color.z * n ;
            }
        }
    }
}
