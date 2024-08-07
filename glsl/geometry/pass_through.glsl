
#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT
{
    vec3 position;
    vec3 normal;
    vec4 color;
    vec2 texCoord;
} gsIn[];

out VS_OUT
{
    vec3 position;
    vec3 normal;
    vec4 color;
    vec2 texCoord;
} gsOut;

void main() 
{
    gl_Position = gl_in[0].gl_Position;
    gsOut.position = gsIn[0].position;
    gsOut.normal = gsIn[0].normal;
    gsOut.color = gsIn[0].color;
    gsOut.texCoord = gsIn[0].texCoord;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    gsOut.position = gsIn[1].position;
    gsOut.normal = gsIn[1].normal;
    gsOut.color = gsIn[1].color;
    gsOut.texCoord = gsIn[1].texCoord;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    gsOut.position = gsIn[2].position;
    gsOut.normal = gsIn[2].normal;
    gsOut.color = gsIn[2].color;
    gsOut.texCoord = gsIn[2].texCoord;
    EmitVertex();

    EndPrimitive();
}  