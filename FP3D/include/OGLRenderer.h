//
// Created by ccampo on 31/10/17.
//

#ifndef TESTEXEC_OGLRENDERER_H
#define TESTEXEC_OGLRENDERER_H

#include "Scene.h"
#include "GLFW/glfw3.h"

typedef unsigned int uint;

class OGLRenderer {
public:
    OGLRenderer(const Scene &scene);
    void render();

private:
    Scene scene;
    GLFWwindow* window;

    uint compileShader(const char* shaderSource, GLenum type);
    uint compileProgram(const std::vector<uint>& shaders);
};

#endif //TESTEXEC_OGLRENDERER_H
