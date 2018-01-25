//
// Created by ccampo on 31/10/17.
//

#include "glad/glad.h"
#include "OGLRenderer.h"
#include <iostream>
#include <Matrix4.h>
#include <cmath>

OGLRenderer::OGLRenderer(Scene* scene) : Renderer(scene) {
    gladLoadGL();

    glViewport(0, 0, scene->camera.width, scene->camera.height);

    const std::string vertexShaderSource =
        #include "shaders/vertexShader.glsl"
    ;
    const std::string fragementShaderSource =
        #include "shaders/fragmentShader.glsl"
    ;
    shaderProgram = new ShaderProgram(vertexShaderSource, fragementShaderSource);

    for (const Mesh &mesh : scene->meshes) {
        uint VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        RenderInfo info;
        info.VAO = VAO;
        info.totalVertices = mesh.vertices.size();
        renderInfo.push_back(info);

        std::vector<Vertex> worldSpaceVertices;
        for (const Vertex vertex : mesh.vertices) {
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

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }
}

void OGLRenderer::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Matrix4 perspective = scene->camera.getPerspectiveMatrix();
    shaderProgram->use();
    shaderProgram->setMatrix("projection", perspective);

    shaderProgram->setVector("lightPosition", scene->lights[0].transform.position());

    for (RenderInfo info : renderInfo) {
        shaderProgram->setVector("color", scene->meshes[info.VAO-1].material.color);
        glBindVertexArray(info.VAO);
        glDrawArrays(GL_TRIANGLES, 0, info.totalVertices);
        glBindVertexArray(0);
    }
}
