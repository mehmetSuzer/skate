
#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

#include <common/geometry.glsl>

const float normalMagnitude = 0.4f;

void DrawNormal(int index)
{
    defaultPassToFragmentShader(index);

    gl_Position = projection * gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = projection * (gl_in[index].gl_Position + vec4(gsIn[index].normal, 0.0) * normalMagnitude);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    DrawNormal(0);
    DrawNormal(1);
    DrawNormal(2);
}
