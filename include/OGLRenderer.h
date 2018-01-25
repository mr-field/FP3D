//
// Created by ccampo on 31/10/17.
//

#ifndef TESTEXEC_OGLRENDERER_H
#define TESTEXEC_OGLRENDERER_H

#include <Renderer.h>
#include "Scene.h"
#include "../src/ShaderProgram.h"

typedef unsigned int uint;

struct RenderInfo {
    uint VAO;
    unsigned long totalVertices;
};

class OGLRenderer : public Renderer {
public:
    OGLRenderer(Scene* scene);
    void render() override;

private:
    std::vector<RenderInfo> renderInfo;
    ShaderProgram* shaderProgram;
};

#endif //TESTEXEC_OGLRENDERER_H
