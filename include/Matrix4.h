//
// Created by ccampo on 14/11/17.
//

#ifndef FP3D_MATRIX4_H
#define FP3D_MATRIX4_H


#include "Vector3.h"
#include <array>

typedef std::array<std::array<float, 4>, 4> array4x4;
typedef std::array<std::array<float, 8>, 4> array4x8;

class Matrix4 {
public:
    array4x4 matrix;

    Matrix4 operator* (const Matrix4& otherMatrix) const;
    Vector3 operator* (const Vector3& vector) const;
    Vector3 multiply3x3 (const Vector3& vector) const;

    static Matrix4 buildIdentityMatrix();
    static Matrix4 buildTranslationMatrix(const Vector3& translation);
    static Matrix4 buildScaleMatrix(float scale);
    static Matrix4 buildScaleMatrix(float scaleX, float scaleY, float scaleZ);
    static Matrix4 buildXRotationMatrix(float radians);
    static Matrix4 buildYRotationMatrix(float radians);
    static Matrix4 buildZRotationMatrix(float radians);
    static Matrix4 buildGenericMatrix(const Vector3& row1, const Vector3& row2, const Vector3& row3);
    static Matrix4 buildPerspectiveMatrix(float fov, float aspectRatio, float near, float far);

    void setPosition(const Vector3& position);

    Vector3 position() const;
    Vector3 forward() const;
    Vector3 up() const;
    Vector3 right() const;
    Matrix4 invert() const;

    friend std::ostream& operator<< (std::ostream& stream, const Matrix4& m);

private:
    Matrix4(array4x4 matrix);
};


#endif //FP3D_MATRIX4_H
