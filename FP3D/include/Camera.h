//
// Created by ccampo on 14/11/17.
//

#ifndef TESTEXEC_CAMERA_H
#define TESTEXEC_CAMERA_H


#include "Point3.h"
#include "Vector3.h"
#include "Matrix4.h"

class Camera {
public:
    Vector3 position;
    Vector3 lookAt;
    float fov, near, far;
    int width, height;

    Camera(const Vector3 &position, const Vector3 &lookAt, float fov, float near, float far, int width, int height);

    Matrix4 getPerspectiveMatrix();

private:
    Matrix4 perspectiveTransform = Matrix4::buildIdentityMatrix();

    void calculatePerspective();
};


#endif //TESTEXEC_CAMERA_H
