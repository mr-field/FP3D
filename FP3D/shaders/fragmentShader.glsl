#version 400 core

in vec4 cameraSpacePosition;
in vec4 normal;

uniform vec3 lightPosition;
uniform vec3 color;

out vec4 FragColor;

void main() {
    //FragColor = vec4(vec3(1, 1, 1) * cameraSpacePosition.z * 0.1, 1);
    vec4 direction = vec4(lightPosition, 1) - cameraSpacePosition;
    FragColor = vec4(color * dot(normalize(direction), normal), 1);
}