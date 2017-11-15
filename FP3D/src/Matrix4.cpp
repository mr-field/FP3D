//
// Created by ccampo on 14/11/17.
//

#include "Matrix4.h"

Matrix4::Matrix4(array4x4 matrix) : matrix(matrix) {}

Matrix4 Matrix4::operator*(const Matrix4 &otherMatrix) {
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

std::ostream& operator<< (std::ostream& stream, const Matrix4& m) {
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
