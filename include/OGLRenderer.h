//
// Created by ccampo on 31/10/17.
//

#ifndef FP3D_OGLRENDERER_H
#define FP3D_OGLRENDERER_H

#include <Renderer.h>
#include "Scene.h"
#include "../src/ShaderProgram.h"

typedef unsigned int uint;

struct RenderInfo {
    uint VAO;
    int totalVertices;
    const ColorRGB* color;
    const Matrix4* model;
};

class OGLRenderer : public Renderer {
public:
    OGLRenderer(Scene* scene);
    void render() override;

private:
    std::vector<RenderInfo> renderInfo;
    ShaderProgram* shaderProgram;
};

#endif //FP3D_OGLRENDERER_H
