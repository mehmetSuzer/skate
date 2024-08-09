
#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

#include <common/geometry.glsl>

// Does nothing, only passes the vertex data unchanged.
void main() 
{
    gl_Position = gl_in[0].gl_Position;
    defaultPassToFragmentShader(0);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    defaultPassToFragmentShader(1);
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    defaultPassToFragmentShader(2);
    EmitVertex();

    EndPrimitive();
}  