
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

#include <common/stencil.glsl>

out vec3 position;
out vec3 normal;

uniform mat4 model;
uniform mat4 projectionView;
uniform mat3 normalMatrix;

void main() 
{
    position = vec3(model * vec4(aPosition, 1.0f));
    normal = normalize(normalMatrix * aNormal);
    position = PositionWithBorder(position, normal);
    gl_Position = projectionView * vec4(position, 1.0f);
}
