
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

#include <common/vertex.glsl>

void main() 
{
    gl_Position = model * vec4(aPosition, 1.0f);
    vsOut.normal = normalize(normalMatrix * aNormal);
}
