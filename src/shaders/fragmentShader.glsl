R"(
#version 330 core

in vec4 cameraSpacePosition;
in vec4 normal;

uniform vec3 lightPosition;
uniform float lightPower;
uniform vec3 color;

out vec4 FragColor;

void main() {
    //FragColor = vec4(vec3(1, 1, 1) * cameraSpacePosition.z * 0.1, 1);
    vec4 direction = vec4(lightPosition, 1) - cameraSpacePosition;
    float att = length(direction) * length(direction);
    float cosine = max(0.0f, dot(normalize(direction), normal));
    FragColor = vec4((color * cosine * lightPower) / att, 1);
}
)"