
#version 330 core

out vec4 FragColor;

in vec4 lightingColor;

uniform vec4 color;

void main() {
    FragColor = color * lightingColor;
}
