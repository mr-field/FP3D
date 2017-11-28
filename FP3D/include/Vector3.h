//
// Created by ccampo on 28/10/17.
//

#ifndef FP3D_VECTOR3_H
#define FP3D_VECTOR3_H

#include <iostream>

class Vector3 {
public:
    float x, y, z;

    Vector3(float x, float y, float z);
    float magnitude();
    float dot(const Vector3& v);
    Vector3 cross(const Vector3& v);
    Vector3 invert();
    Vector3 normalise();
    Vector3 operator- (const Vector3& v);
    Vector3 operator+ (const Vector3& v);

    friend std::ostream& operator<<(std::ostream& stream, const Vector3& v);
};


#endif //FP3D_VECTOR3_H
