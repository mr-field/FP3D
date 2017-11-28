//
// Created by ccampo on 31/10/17.
//

#include "glad/glad.h"
#include "OGLRenderer.h"
#include "ShaderProgram.h"
#include <iostream>
#include <Matrix4.h>
#include <cmath>

OGLRenderer::OGLRenderer(const Scene &scene) : scene(scene) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(scene.camera.width, scene.camera.height, "OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Could not create GLFW window" << std::endl;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, scene.camera.width, scene.camera.height);
}


void OGLRenderer::render() {
    ShaderProgram shaderProgram = ShaderProgram("FP3D/shaders/vertexShader.glsl", "FP3D/shaders/fragmentShader.glsl");

    std::vector<uint> VAOs;
    for (Mesh mesh : scene.meshes) {
        uint VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        VAOs.push_back(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(double) * mesh.vertices.size() * 3, &mesh.vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh.indices.size(), &mesh.indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Matrix4 perspective = scene.camera.getPerspectiveMatrix();
        shaderProgram.use();
        shaderProgram.setMatrix("projection", perspective);

        for (uint VAO : VAOs) {
            glBindVertexArray(VAO);
            GLint size;
            glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
            glDrawElements(GL_TRIANGLES, size / sizeof(GL_UNSIGNED_INT), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
