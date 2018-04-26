R"(
#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

uniform mat4 projection;
uniform mat4 model;

out vec4 position;
out vec4 normal;

void main() {
    position = model * vec4(vertexPosition, 1);
    normal = vec4(normalize(mat3(model) * vertexNormal), 1);
    gl_Position = projection * position;
}
)"