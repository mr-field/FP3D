//
// Created by ccampo on 15/01/18.
//

#include <Ray.h>
#include "RayCastingRenderer.h"

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

Vector3 getClosestIntersection(Scene* scene, Ray& ray) {
    Matrix4 per = scene->camera.getPerspectiveMatrix();
    Vector3 result = Vector3(0, 0, 0);
    float closest = scene->camera.far;

    for (Mesh &mesh : scene->meshes) {
        for (Triangle &t : mesh.triangles) {
            Vector3 a = per * (mesh.transform * t.a.position);
            Vector3 b = per * (mesh.transform * t.b.position);
            Vector3 c = per * (mesh.transform * t.c.position);

            Vector3 normal = (b - a).cross((c - b)).invert();
            Vector3 ab = (b - a).cross(normal);
            float n = (c - a).dot(ab);
            ab = ab * (1 / n);

            Vector3 ac = (c - a).cross(normal);
            float n2 = (b - a).dot(ac);
            ac = ac * (1 / n2);

            float planeIntersection = ((a - ray.origin).dot(normal)) / (ray.direction.dot(normal));
            if (planeIntersection < 0.0001f) {
                continue;
            }

            Vector3 q = ray.origin + (ray.direction * planeIntersection);
            float gamma = (q - c).dot(ac);
            float beta = (q - b).dot(ab);
            float alpha = 1 - (gamma + beta);

            if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1 && q.z < closest) {
                closest = q.z;
                result = q;
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
            Ray ray = Ray(origin, direction);

            Vector3 surfacePoint = getClosestIntersection(scene, ray);

            if (surfacePoint.x == 0 && surfacePoint.y == 0 && surfacePoint.z == 0) {
                continue;
            }

            Light& light = scene->lights[0];
            Vector3 lightDirection = light.transform.position() - surfacePoint;
            Ray lightRay = Ray(surfacePoint, lightDirection);

            Vector3 obstacle = getClosestIntersection(scene, lightRay);
            Vector3 obstacleDirection = obstacle - surfacePoint;

            int index = ((y*scene->camera.width) + x) * 3;
            if (obstacle.magnitude() != 0 && obstacleDirection.magnitude() < lightDirection.magnitude()) {
                image[index] = 0;
            }
            else if (surfacePoint.z > scene->camera.near && surfacePoint.z < scene->camera.far) {
                image[index] = surfacePoint.z * 100;
            }
            image[index+2] = 0;
        }
    }
}
