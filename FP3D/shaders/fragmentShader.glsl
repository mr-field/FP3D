#version 400 core

in vec4 cameraSpacePosition;
in vec4 normal;

uniform vec3 lightPosition;

out vec4 FragColor;

void main() {
    vec3 baseColor = vec3(0.8, 0.4, 0.2);
    //FragColor = vec4(vec3(1, 1, 1) * cameraSpacePosition.z * 0.1, 1);
    vec4 direction = vec4(lightPosition, 1) - cameraSpacePosition;
    FragColor = vec4(baseColor * dot(normalize(direction), normal), 1);
}