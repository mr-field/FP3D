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
    std::vector<uint> sizes;
    for (Mesh mesh : scene.meshes) {
        uint VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        VAOs.push_back(VAO);
        sizes.push_back(mesh.vertices.size());

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh.vertices.size(), &mesh.vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vertex)/2));
        glEnableVertexAttribArray(1);

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

        shaderProgram.setVector("lightPosition", scene.lights[0].position);

        for (int i = 0; i < VAOs.size(); i++) {
            glBindVertexArray(VAOs[i]);
            glDrawArrays(GL_TRIANGLES, 0, sizes[i]);
            glBindVertexArray(0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
