//
// Created by ccampo on 14/11/17.
//

#ifndef TESTEXEC_MATRIX4_H
#define TESTEXEC_MATRIX4_H


#include "Vector3.h"
#include <array>

typedef std::array<std::array<float, 4>, 4> array4x4;

class Matrix4 {
public:
    array4x4 matrix;

    Matrix4 operator* (const Matrix4& otherMatrix) const;
    Vector3 operator* (const Vector3& vector) const;

    static Matrix4 buildIdentityMatrix();
    static Matrix4 buildTranslationMatrix(const Vector3& translation);
    static Matrix4 buildScaleMatrix(float scale);
    static Matrix4 buildScaleMatrix(float scaleX, float scaleY, float scaleZ);
    static Matrix4 buildXRotationMatrix(float radians);
    static Matrix4 buildYRotationMatrix(float radians);
    static Matrix4 buildZRotationMatrix(float radians);
    static Matrix4 buildGenericMatrix(const Vector3& row1, const Vector3& row2, const Vector3& row3);
    static Matrix4 buildPerspectiveMatrix(float fov, float aspectRatio, float near, float far);

    void setPosition(Vector3& position);
    Vector3 position();
    Vector3 forward();
    Vector3 up();
    Vector3 right();

    friend std::ostream& operator<< (std::ostream& stream, const Matrix4& m);

private:
    Matrix4(array4x4 matrix);
};


#endif //TESTEXEC_MATRIX4_H
