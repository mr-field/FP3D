//
// Created by ccampo on 28/10/17.
//

#ifndef FP3D_VECTOR3_H
#define FP3D_VECTOR3_H

#include <iostream>

// Trick to avoid include cycle. Real header is included in .cpp file
class Matrix4;

class Vector3 {
public:
    float x, y, z;

    Vector3(float x, float y, float z);
    float magnitude();
    float dot(const Vector3& v);
    Vector3 cross(const Vector3& v);
    Vector3 invert();
    Vector3 normalise();

    Vector3& operator*= (const Matrix4& m);
    Vector3 operator* (const Matrix4& m);

    Vector3& operator+= (const Vector3& v);
    Vector3& operator-= (const Vector3& v);
    Vector3& operator*= (const Vector3& v);
    Vector3 operator+ (const Vector3& v);
    Vector3 operator- (const Vector3& v);
    Vector3 operator* (const Vector3& v);

    Vector3& operator+= (float n);
    Vector3& operator*= (float n);
    Vector3& operator/= (float n);
    Vector3 operator+ (float n);
    Vector3 operator* (float n);
    Vector3 operator/ (float n);

    bool operator== (const Vector3& v);

    friend std::ostream& operator<<(std::ostream& stream, const Vector3& v);
};


#endif //FP3D_VECTOR3_H
