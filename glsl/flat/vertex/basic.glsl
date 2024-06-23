
#version 330 core

layout (location = 0) in vec3 aPosition;

uniform mat4 model;
uniform mat4 projectionView;

void main() {
    gl_Position = projectionView * model * vec4(aPosition, 1.0f);
}
