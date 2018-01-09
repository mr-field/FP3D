//
// Created by ccampo on 14/11/17.
//

#include <cmath>
#include "Matrix4.h"

Matrix4::Matrix4(array4x4 matrix) : matrix(matrix) {}


Matrix4 Matrix4::operator*(const Matrix4 &otherMatrix) const {
    array4x4 result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float total = 0;
            for (int k = 0; k < 4; k++) {
                total += matrix[i][k] * otherMatrix.matrix[k][j];
            }
            result[i][j] = total;
        }
    }

    return Matrix4(result);
}


Vector3 Matrix4::operator*(const Vector3 &vector) const {
    float result[4];
    float vec[4] = {vector.x, vector.y, vector.z, 1};

    for (int i = 0; i < 4; i++) {
        float total = 0;
        for (int j = 0; j < 4; j++) {
            total += matrix[i][j] * vec[j];
        }
        result[i] = total;
    }

    return Vector3(result[0], result[1], result[2]);
}


Vector3 Matrix4::position() {
    return Vector3(matrix[0][3], matrix[1][3], matrix[2][3]);
}

Vector3 Matrix4::forward() {
    return Vector3(matrix[2][0], matrix[2][1], matrix[2][2]);
}

Vector3 Matrix4::up() {
    return Vector3(matrix[1][0], matrix[1][1], matrix[1][2]);
}


std::ostream& operator<<(std::ostream& stream, const Matrix4& m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            stream << m.matrix[i][j] << " ";
        }
        stream << std::endl;
    }
    return stream;
}


Matrix4 Matrix4::buildIdentityMatrix() {
    array4x4 matrix = {{
                            {1, 0, 0, 0},
                            {0, 1, 0, 0},
                            {0, 0, 1, 0},
                            {0, 0, 0, 1}
                    }};

    return Matrix4(matrix);
}


Matrix4 Matrix4::buildTranslationMatrix(const Vector3 &translation) {
    array4x4 matrix = {{
                             {1, 0, 0, (float) translation.x},
                             {0, 1, 0, (float) translation.y},
                             {0, 0, 1, (float) translation.z},
                             {0, 0, 0, 1}
                     }};

    return Matrix4(matrix);
}


Matrix4 Matrix4::buildScaleMatrix(float scale) {
    array4x4 matrix = {{
                             {scale, 0, 0, 0},
                             {0, scale, 0, 0},
                             {0, 0, scale, 0},
                             {0, 0, 0, 1}
                     }};

    return Matrix4(matrix);
}


Matrix4 Matrix4::buildScaleMatrix(float scaleX, float scaleY, float scaleZ) {
    array4x4 matrix = {{
                             {scaleX, 0, 0, 0},
                             {0, scaleY, 0, 0},
                             {0, 0, scaleZ, 0},
                             {0, 0, 0, 1}
                     }};

    return Matrix4(matrix);
}

Matrix4 Matrix4::buildGenericMatrix(const Vector3 &row1, const Vector3 &row2, const Vector3 &row3) {
    array4x4 matrix = {{
                               {(float) row1.x, (float) row1.y, (float) row1.z, 0},
                               {(float) row2.x, (float) row2.y, (float) row2.z, 0},
                               {(float) row3.x, (float) row3.y, (float) row3.z, 0},
                               {0, 0, 0, 1}
                       }};

    return Matrix4(matrix);
}

Matrix4 Matrix4::buildXRotationMatrix(float radians) {
    array4x4 matrix = {{
                               {1, 0, 0, 0},
                               {0, cosf(radians), -sinf(radians), 0},
                               {0, sinf(radians), cosf(radians), 0},
                               {0, 0, 0, 1}
                       }};
    return Matrix4(matrix);
}

Matrix4 Matrix4::buildYRotationMatrix(float radians) {
    array4x4 matrix = {{
                               {cosf(radians), 0, sinf(radians), 0},
                               {0, 1, 0, 0},
                               {-sinf(radians), 0, cosf(radians), 0},
                               {0, 0, 0, 1}
                       }};
    return Matrix4(matrix);
}

Matrix4 Matrix4::buildZRotationMatrix(float radians) {
    array4x4 matrix = {{
                               {cosf(radians), -sinf(radians), 0, 0},
                               {sinf(radians), cosf(radians), 0, 0},
                               {0, 0, 1, 0},
                               {0, 0, 0, 1}
                       }};
    return Matrix4(matrix);
}

Matrix4 Matrix4::buildPerspectiveMatrix(float fov, float aspectRatio, float near, float far) {
    float rad = (fov * M_PI) / 180.0;

    float b = cosf(rad/2) / sinf(rad/2);
    float a = b / aspectRatio;
    float c = (near + far) / (near - far);
    float d = (2.0f * near * far) / (near - far);

    array4x4 matrix = {{
                               {a, 0, 0, 0},
                               {0, b, 0, 0},
                               {0, 0, c, d},
                               {0, 0, -1, 0}
                       }};
    return Matrix4(matrix);
}