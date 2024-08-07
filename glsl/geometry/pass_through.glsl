
#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT 
{
    vec3 position;
    vec3 normal;
} gsIn[];

out vec3 position;
out vec3 normal;

void main() 
{
    gl_Position = gl_in[0].gl_Position;
    position = gsIn[0].position;
    normal = gsIn[0].normal;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    position = gsIn[1].position;
    normal = gsIn[1].normal;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    position = gsIn[2].position;
    normal = gsIn[2].normal;
    EmitVertex();

    EndPrimitive();
}  