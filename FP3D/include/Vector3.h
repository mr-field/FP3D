//
// Created by ccampo on 28/10/17.
//

#ifndef FP3D_VECTOR3_H
#define FP3D_VECTOR3_H

#include <iostream>

class Vector3 {
public:
    const double x, y, z;

    Vector3(double x, double y, double z);
    double magnitude();
    double dot(const Vector3& v);
    Vector3 cross(const Vector3& v);
    Vector3 invert();
    Vector3 normalise();

    friend std::ostream& operator<<(std::ostream& stream, const Vector3& v);
};


#endif //FP3D_VECTOR3_H
