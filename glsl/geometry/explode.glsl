
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
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 normal = normalize(cross(a, b));
    
    float magnitude = 0.02f;
    vec4 shift = vec4(normal * magnitude, 0.0f);

    gl_Position = gl_in[0].gl_Position + shift;
    position = gsIn[0].position;
    normal = gsIn[0].normal;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + shift;
    position = gsIn[1].position;
    normal = gsIn[1].normal;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position + shift;
    position = gsIn[2].position;
    normal = gsIn[2].normal;
    EmitVertex();

    EndPrimitive();
}  