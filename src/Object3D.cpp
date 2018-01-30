//
// Created by ccampo on 02/12/17.
//

#include "Object3D.h"


Object3D::Object3D() {
    transform = Matrix4::buildIdentityMatrix();
}

Object3D::Object3D(const Vector3& center) {
    translate(center);
}

void Object3D::translate(const Vector3 &translation) {
    transform = transform * Matrix4::buildTranslationMatrix(translation);
}

void Object3D::scale(float scale) {
    transform = transform * Matrix4::buildScaleMatrix(scale);
}

void Object3D::scale(float scaleX, float scaleY, float scaleZ) {
    transform = transform * Matrix4::buildScaleMatrix(scaleX, scaleY, scaleZ);
}

void Object3D::rotateX(float angle) {
    transform = transform * Matrix4::buildXRotationMatrix(angle);
}

void Object3D::rotateY(float angle) {
    transform = transform * Matrix4::buildYRotationMatrix(angle);
}

void Object3D::rotateZ(float angle) {
    transform = transform * Matrix4::buildZRotationMatrix(angle);
}

void Object3D::setPosition(const Vector3 &newPosition) {
    transform.matrix[0][3] = newPosition.x;
    transform.matrix[1][3] = newPosition.y;
    transform.matrix[2][3] = newPosition.z;
}
