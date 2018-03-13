//
// Created by ccampo on 15/11/17.
//

#ifndef TESTEXEC_SHADER_H
#define TESTEXEC_SHADER_H

#include <string>
#include <Matrix4.h>

typedef unsigned int uint;

class ShaderProgram {
public:
    uint id;

    ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void setFloat(const char* uniformName, float n);
    void setMatrix(const char* uniformName, const Matrix4& matrix);
    void setVector(const char* uniformName, const Vector3& vector);
    void use();

private:
    uint compileShader(const std::string& source, uint type);
    uint linkShaders(uint vertexShader, uint fragmentShader);
};


#endif //TESTEXEC_SHADER_H
