R"(
#version 400 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

uniform mat4 projection;

out vec4 cameraSpacePosition;
out vec4 normal;

void main() {
    cameraSpacePosition = projection * vec4(vertexPosition, 1.0);
    normal = vec4(vertexNormal, 1);
    gl_Position = cameraSpacePosition;
}
)"