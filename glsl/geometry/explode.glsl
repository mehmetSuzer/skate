
#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

#include <common/geometry.glsl>

void main() 
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 normal = normalize(cross(a, b));
    
    float magnitude = 0.06f;
    vec4 shift = vec4(normal * magnitude, 0.0f);

    gl_Position = gl_in[0].gl_Position + shift;
    gsOut.position = gsIn[0].position;
    gsOut.normal = gsIn[0].normal;
    gsOut.color = gsIn[0].color;
    gsOut.texCoord = gsIn[0].texCoord;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + shift;
    gsOut.position = gsIn[1].position;
    gsOut.normal = gsIn[1].normal;
    gsOut.color = gsIn[1].color;
    gsOut.texCoord = gsIn[1].texCoord;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position + shift;
    gsOut.position = gsIn[2].position;
    gsOut.normal = gsIn[2].normal;
    gsOut.color = gsIn[2].color;
    gsOut.texCoord = gsIn[2].texCoord;
    EmitVertex();

    EndPrimitive();
}  