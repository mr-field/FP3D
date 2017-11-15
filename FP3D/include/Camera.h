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
    Vector3 lookDirection;
    int fov, near, far;

    Camera(const Vector3 &position, const Vector3 &lookDirection, int fov, int near, int far);
    Matrix4 getPerspectiveMatrix();

private:
    Matrix4 perspectiveTransform = Matrix4::buildIdentityMatrix();

    void calculatePerspective();
};


#endif //TESTEXEC_CAMERA_H
