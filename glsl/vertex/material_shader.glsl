
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

out VS_OUT
{
    vec3 position;
    vec3 normal;
    vec4 color;
    vec2 texCoord;
} vsOut;

uniform mat4 model;
uniform mat4 projectionView;
uniform mat3 normalMatrix;

void main() 
{
    vsOut.position = vec3(model * vec4(aPosition, 1.0f));
    vsOut.normal = normalize(normalMatrix * aNormal);
    gl_Position = projectionView * vec4(vsOut.position, 1.0f);
}
