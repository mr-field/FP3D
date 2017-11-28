//
// Created by ccampo on 15/11/17.
//

#ifndef TESTEXEC_SHADER_H
#define TESTEXEC_SHADER_H

#include <glad/glad.h>
#include <string>
#include <Matrix4.h>

typedef unsigned int uint;

class ShaderProgram {
public:
    uint id;

    ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
    void setMatrix(const char* uniformName, const Matrix4& matrix);
    void setVector(const char* uniformName, const Vector3& vector);
    void use();

private:
    const char* vertexShaderPath;
    const char* fragmentShaderPath;

    uint compileShader(std::string& source, GLenum type);
    uint linkShaders(uint vertexShader, uint fragmentShader);
    std::string readFile(const char* filePath);
};


#endif //TESTEXEC_SHADER_H
