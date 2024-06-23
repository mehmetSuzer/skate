
#version 330 core

out vec4 FragColor;

in vec4 lightingColor;
in vec2 tex;

uniform sampler2D textureImage;

void main() {
    FragColor = texture(textureImage, tex) * lightingColor;
}
