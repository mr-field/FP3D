#version 400 core

layout (location = 0) in vec3 worldPosition;

uniform mat4 projection;

void main() {
    vec4 cameraPosition = projection * vec4(worldPosition, 1.0);

    gl_Position = vec4(
        cameraPosition.x/cameraPosition.z,
        cameraPosition.y/cameraPosition.z,
        cameraPosition.z/cameraPosition.z,
        1.0);
}