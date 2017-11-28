//
// Created by ccampo on 14/11/17.
//

#include "Camera.h"

Camera::Camera(const Vector3 &position, const Vector3 &lookAt, float fov, float near, float far, int width,
               int height) : position(position), lookAt(lookAt), fov(fov), near(near), far(far), width(width),
                              height(height) {
    calculatePerspective();
}


Matrix4 Camera::getPerspectiveMatrix() {
    return perspectiveTransform;
}


void Camera::calculatePerspective() {
    Matrix4 translate = Matrix4::buildTranslationMatrix(position.invert());

    Vector3 forward = (position - lookAt).normalise();
    Vector3 up = Vector3(0.0, 1.0, 0.0);
    Vector3 right = forward.cross(up).normalise();
    Matrix4 rotate = Matrix4::buildGenericMatrix(right, up, forward);

    Matrix4 view = rotate * translate;
    Matrix4 perspective = Matrix4::buildPerspectiveMatrix(fov, (float) width / (float) height, near, far);

    perspectiveTransform = perspective * view;
}
