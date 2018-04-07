//
// Created by ccampo on 14/11/17.
//

#include "Camera.h"

Camera::Camera(const Vector3 &position, float fov, float nearPlane, float farPlane, int width,
               int height) : Object3D(position), fov(fov), near(nearPlane), far(farPlane), width(width),
                              height(height) {}


Matrix4 Camera::getPerspectiveMatrix() {
    Matrix4 translate = Matrix4::buildTranslationMatrix(transform.position().invert());

    Vector3 reverseForward = transform.forward().invert();
    Matrix4 rotate = Matrix4::buildGenericMatrix(transform.right(), transform.up(), reverseForward);

    Matrix4 view = rotate * translate;
    Matrix4 perspective = Matrix4::buildPerspectiveMatrix(fov, (float) width / (float) height, near, far);

    return perspective * view;
}
