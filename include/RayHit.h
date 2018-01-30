//
// Created by ccampo on 26/01/18.
//

#ifndef FP3D_COLLISIONINFO_H
#define FP3D_COLLISIONINFO_H


#include "Vector3.h"
#include "Triangle.h"
#include "Mesh.h"

struct RayHit {
public:
    float distance;
    Vector3 intersectionPoint;
    Mesh* collider;
    Triangle* triangle;

    RayHit() : intersectionPoint(Vector3(0,0,0)) {};

    RayHit(float distance, const Vector3 &intersectionPoint, Triangle* triangle, Mesh* collider) : distance(distance),
                                                                               intersectionPoint(intersectionPoint),
                                                                               triangle(triangle), collider(collider) {}
};


#endif //FP3D_COLLISIONINFO_H
