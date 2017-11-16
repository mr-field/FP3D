//
// Created by ccampo on 14/11/17.
//

#include "Camera.h"

Camera::Camera(const Vector3 &position, const Vector3 &lookDirection, int fov, int near, int far) : position(position),
                                                                                                   lookDirection(
                                                                                                           lookDirection),
                                                                                                   fov(fov), near(near),
                                                                                                   far(far) {
    calculatePerspective();
}


Matrix4 Camera::getPerspectiveMatrix() {
    return perspectiveTransform;
}


void Camera::calculatePerspective() {
    Matrix4 translate = Matrix4::buildTranslationMatrix(position.invert());

    Vector3 up = Vector3(0, 1, 0);
    Vector3 right = up.cross(lookDirection);
    Matrix4 rotate = Matrix4::buildGenericMatrix(right, up, lookDirection);

    perspectiveTransform = rotate * translate;
}
