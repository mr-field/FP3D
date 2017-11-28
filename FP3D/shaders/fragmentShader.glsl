#version 400 core

in vec4 cameraSpacePosition;
out vec4 FragColor;

void main() {
    FragColor = vec4(vec3(1, 1, 1) * cameraSpacePosition.z * 0.1, 1);
}