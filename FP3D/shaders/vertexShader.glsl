#version 400 core

layout (location = 0) in vec3 worldPosition;
out vec4 cameraSpacePosition;

uniform mat4 projection;

void main() {
    cameraSpacePosition = projection * vec4(worldPosition, 1.0);
    gl_Position = cameraSpacePosition;
}