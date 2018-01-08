//
// Created by ccampo on 31/10/17.
//

#ifndef TESTEXEC_OGLRENDERER_H
#define TESTEXEC_OGLRENDERER_H

#include "Scene.h"
#include "../src/ShaderProgram.h"

typedef unsigned int uint;

struct RenderInfo {
    uint VAO;
    unsigned long totalVertices;
};

class OGLRenderer {
public:
    OGLRenderer(Scene* scene);
    void render();

private:
    Scene* scene;

    std::vector<RenderInfo> renderInfo;
    ShaderProgram* shaderProgram;
};

#endif //TESTEXEC_OGLRENDERER_H
