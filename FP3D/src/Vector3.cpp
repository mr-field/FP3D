//
// Created by ccampo on 29/10/17.
//

#include "Vector3.h"
#include <cmath>

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

float Vector3::magnitude() {
    return sqrtf(x*x + y*y + z*z);
}

float Vector3::dot(const Vector3& v) {
    return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3& v) {
    return {
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
    };
}

Vector3 Vector3::invert() {
    return {
            -x,
            -y,
            -z
    };
}

Vector3 Vector3::normalise() {
    float m = magnitude();
    if (m == 0) {
        m = 1;
    }
    return {
            x / m,
            y / m,
            z / m
    };
}

Vector3 Vector3::operator-(const Vector3 &v) {
    return {
            x - v.x,
            y - v.y,
            z - v.z
    };
}

Vector3 Vector3::operator+(const Vector3 &v) {
    return {
            x + v.x,
            y + v.y,
            z + v.z
    };
}

std::ostream& operator<<(std::ostream& stream, const Vector3& v) {
    return stream << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}
