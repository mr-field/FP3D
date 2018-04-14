//
// Created by ccampo on 02/12/17.
//

#ifndef FP3D_OBJECT3D_H
#define FP3D_OBJECT3D_H


#include <Matrix4.h>

class Object3D {
public:
    Matrix4 transform = Matrix4::buildIdentityMatrix();

    Object3D(const Vector3& center);
    Object3D();

    void translate(const Vector3& translation);
    void scale(float scale);
    void scale(float scaleX, float scaleY, float scaleZ);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void setPosition(const Vector3& newPosition);
};


#endif //FP3D_OBJECT3D_H
