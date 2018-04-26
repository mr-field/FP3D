//
// Created by ccampo on 15/11/17.
//

#include "ShaderProgram.h"
#include <glad/glad.h>

ShaderProgram::ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    uint vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    uint fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    id = linkShaders(vertexShader, fragmentShader);
}


uint ShaderProgram::compileShader(const std::string& source, uint type) {
    uint shader = glCreateShader(type);
    const char* cstringSource = source.data();
    glShaderSource(shader, 1, &cstringSource, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Error compiling shader:\n" << infoLog << std::endl;
    }

    return shader;
}


uint ShaderProgram::linkShaders(uint vertexShader, uint fragmentShader) {
    uint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "Error linking shader program:\n" << infoLog << std::endl;
    }

    return shaderProgram;
}


void ShaderProgram::use() {
    glUseProgram(id);
}

void ShaderProgram::setFloat(const char* uniformName, float n) {
    int attributeLocation = glGetUniformLocation(id, uniformName);
    glUniform1f(attributeLocation, n);
}

void ShaderProgram::setMatrix(const char* uniformName, const Matrix4& matrix) {
    int attributeLocation = glGetUniformLocation(id, uniformName);
    glUniformMatrix4fv(attributeLocation, 1, GL_TRUE, &matrix.matrix[0][0]);
}

void ShaderProgram::setVector(const char* uniformName, const Vector3 &vector) {
    int attributeLocation = glGetUniformLocation(id, uniformName);
    float values[3] = {vector.x, vector.y, vector.z};
    glUniform3fv(attributeLocation, 1, &values[0]);
}
