R"(
#version 330 core

in vec4 position;
in vec4 normal;

uniform vec3 lightPosition;
uniform float lightPower;
uniform vec3 color;

out vec4 FragColor;

void main() {
    vec4 direction = vec4(lightPosition, 1) - position;
    float cosine = max(0.0f, dot(normalize(direction), normal));
    FragColor = vec4((color * cosine * lightPower), 1);
}
)"