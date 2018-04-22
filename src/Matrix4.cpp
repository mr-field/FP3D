//
// Created by ccampo on 14/11/17.
//

#define _USE_MATH_DEFINES
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

Vector3 Matrix4::multiply3x3(const Vector3 &vector) const {
    float result[3];
    float vec[3] = {vector.x, vector.y, vector.z};

    for (int i = 0; i < 3; i++) {
        float total = 0;
        for (int j = 0; j < 3; j++) {
            total += matrix[i][j] * vec[j];
        }
        result[i] = total;
    }

    return Vector3(result[0], result[1], result[2]);
}

Matrix4 Matrix4::invert() const {
    array4x8 monster = {{
            {matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3], 1, 0, 0, 0},
            {matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3], 0, 1, 0, 0},
            {matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3], 0, 0, 1, 0},
            {matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3], 0, 0, 0, 1}
    }};

    for (int i = 0; i < 4; i++) {
        float max = monster[i][i];
        int max_row = i;
        for (int j = i + 1; j < 4; j++) {
            if (abs(monster[j][i]) > abs(max)) {
                max = monster[j][i];
                max_row = j;
            }
        }

        if (max_row != i) {
            auto temp = monster[i];
            monster[i] = monster[max_row];
            monster[max_row] = temp;
        }

        for (int c = 0; c < 8; c++) {
            monster[i][c] /= max;
        }

        for (int r = 0; r < 4; r++) {
            if (r == i) {
                continue;
            }

            std::array<float, 8> rowToAdd;
            for (int c = 0; c < 8; c++) {
                rowToAdd[c] = -monster[r][i] * monster[i][c];
            }
            for (int c = 0; c < 8; c++) {
                monster[r][c] += rowToAdd[c];
            }
        }
    }

    array4x4 inverse = {{
            {monster[0][4], monster[0][5], monster[0][6], monster[0][7]},
            {monster[1][4], monster[1][5], monster[1][6], monster[1][7]},
            {monster[2][4], monster[2][5], monster[2][6], monster[2][7]},
            {monster[3][4], monster[3][5], monster[3][6], monster[3][7]}
    }};

    return Matrix4(inverse);
}

void Matrix4::setPosition(const Vector3& position) {
    matrix[0][3] = position.x;
    matrix[1][3] = position.y;
    matrix[2][3] = position.z;
}

Vector3 Matrix4::position() const {
    return Vector3(matrix[0][3], matrix[1][3], matrix[2][3]);
}

Vector3 Matrix4::forward() const {
    return Vector3(matrix[2][0], matrix[2][1], matrix[2][2]);
}

Vector3 Matrix4::up() const {
    return Vector3(matrix[1][0], matrix[1][1], matrix[1][2]);
}

Vector3 Matrix4::right() const {
    return Vector3(matrix[0][0], matrix[0][1], matrix[0][2]);
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
                             {1, 0, 0, translation.x},
                             {0, 1, 0, translation.y},
                             {0, 0, 1, translation.z},
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
                               {row1.x, row1.y, row1.z, 0},
                               {row2.x, row2.y, row2.z, 0},
                               {row3.x, row3.y, row3.z, 0},
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

    float b = tanf(rad/2);
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
