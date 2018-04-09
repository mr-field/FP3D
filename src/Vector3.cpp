//
// Created by ccampo on 29/10/17.
//

#include "Vector3.h"
#include "Matrix4.h"
#include <cmath>

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

float Vector3::magnitude() const {
    return sqrtf(x*x + y*y + z*z);
}

float Vector3::dot(const Vector3& v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3& v) const {
    return {
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
    };
}

Vector3 Vector3::invert() const {
    return {
            -x,
            -y,
            -z
    };
}

Vector3 Vector3::normalise() const {
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

Vector3& Vector3::operator*=(const Matrix4& m) {
    float* result[3] = {&x, &y, &z};
    float vec[3] = {x, y, z};

    for (int i = 0; i < 3; i++) {
        float total = 0;
        for (int j = 0; j < 3; j++) {
            total += vec[j] * m.matrix[j][i];
        }
        *result[i] = total;
    }

    return *this;
}

Vector3 Vector3::operator*(const Matrix4& m) const {
    Vector3 copy = Vector3(*this);
    copy *= m;
    return copy;
}

Vector3& Vector3::operator+=(const Vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3& Vector3::operator*=(const Vector3& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vector3 Vector3::operator+(const Vector3 &v) const {
    Vector3 copy = Vector3(*this);
    copy += v;
    return copy;
}

Vector3 Vector3::operator-(const Vector3 &v) const {
    Vector3 copy = Vector3(*this);
    copy -= v;
    return copy;
}

Vector3 Vector3::operator*(const Vector3 &v) const {
    Vector3 copy = Vector3(*this);
    copy *= v;
    return copy;
}

Vector3& Vector3::operator+=(float n) {
    x += n;
    y += n;
    z += n;
    return *this;
}

Vector3& Vector3::operator*=(float n) {
    x *= n;
    y *= n;
    z *= n;
    return *this;
}

Vector3& Vector3::operator/=(float n) {
    x /= n;
    y /= n;
    z /= n;
    return *this;
}

Vector3 Vector3::operator+(float n) const {
    Vector3 copy = Vector3(*this);
    copy += n;
    return copy;
}

Vector3 Vector3::operator*(float n) const {
    Vector3 copy = Vector3(*this);
    copy *= n;
    return copy;
}

Vector3 Vector3::operator/(float n) const {
    Vector3 copy = Vector3(*this);
    copy /= n;
    return copy;
}

bool Vector3::operator==(const Vector3 &v) const {
    return (x == v.x && y == v.y && z == v.z);
}

std::ostream& operator<<(std::ostream& stream, const Vector3& v) {
    return stream << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}
