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


void OGLRenderer::updateCamera() {
    if (glfwGetKey(window, GLFW_KEY_W)) {
        scene.camera.translate(Vector3(0, 0, 0.01f));
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        scene.camera.translate(Vector3(0, 0, -0.01f));
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        scene.camera.translate(Vector3(-0.01f, 0, 0));
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        scene.camera.translate(Vector3(0.01f, 0, 0));
    }
    if (glfwGetKey(window, GLFW_KEY_E)) {
        scene.camera.rotateY(-0.5 * M_PI / 180);
    }
    if (glfwGetKey(window, GLFW_KEY_Q)) {
        scene.camera.rotateY(0.5 * M_PI / 180);
    }
}


void OGLRenderer::render() {
    ShaderProgram shaderProgram = ShaderProgram("FP3D/shaders/vertexShader.glsl", "FP3D/shaders/fragmentShader.glsl");

    struct RenderInfo {
        uint VAO;
        unsigned long totalVertices;
        Material* material;
    };
    std::vector<RenderInfo> renderInfo;

    for (Mesh &mesh : scene.meshes) {
        uint VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        RenderInfo info;
        info.VAO = VAO;
        info.totalVertices = mesh.vertices.size();
        info.material = &mesh.material;
        renderInfo.push_back(info);

        std::vector<Vertex> worldSpaceVertices;
        for (Vertex vertex : mesh.vertices) {
            Vector3 worldPosition = mesh.transform * vertex.position;
            Vertex worldSpaceVertex = Vertex(worldPosition, vertex.normal);
            worldSpaceVertices.push_back(worldSpaceVertex);
        }

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh.vertices.size(), &worldSpaceVertices[0], GL_STATIC_DRAW);

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

        shaderProgram.setVector("lightPosition", scene.lights[0].transform.position());

        for (RenderInfo info : renderInfo) {
            shaderProgram.setVector("color", info.material->color);
            glBindVertexArray(info.VAO);
            glDrawArrays(GL_TRIANGLES, 0, info.totalVertices);
            glBindVertexArray(0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        updateCamera();
    }
}
