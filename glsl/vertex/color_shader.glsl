
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 aColor;

#include <common/vertex.glsl>

void main() 
{
    vsOut.position = vec3(model * vec4(aPosition, 1.0f));
    vsOut.normal = normalize(normalMatrix * aNormal);
    gl_Position = projection * view * vec4(vsOut.position, 1.0f);
    vsOut.color = aColor;
}
