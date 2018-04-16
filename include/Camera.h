//
// Created by ccampo on 14/11/17.
//

#ifndef FP3D_CAMERA_H
#define FP3D_CAMERA_H


#include "Vector3.h"
#include "Matrix4.h"
#include "../src/Object3D.h"

class Camera : public Object3D {
public:
    float fov, nearPlane, farPlane;
    int width, height;

    Camera(const Vector3 &position, float fov, float nearPlane, float farPlane, int width, int height);

    Matrix4 getPerspectiveMatrix();

private:
    Matrix4 perspectiveTransform = Matrix4::buildIdentityMatrix();
};


#endif //FP3D_CAMERA_H
