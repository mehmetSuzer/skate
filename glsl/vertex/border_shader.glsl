
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

#include <common/vertex.glsl>

void main() 
{
    vec3 position = vec3(model * vec4(aPosition, 1.0f));
    vec3 normal = normalize(normalMatrix * aNormal);
    position += 0.02f * normal;
    gl_Position = projectionView * vec4(position, 1.0f);
}
