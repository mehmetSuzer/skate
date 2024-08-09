
#ifndef _GEOMETRY_GLSL_
#define _GEOMETRY_GLSL_

#include <common/global.glsl>

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

void defaultPassToFragmentShader(int index)
{
    gsOut.position = gsIn[index].position;
    gsOut.normal = gsIn[index].normal;
    gsOut.color = gsIn[index].color;
    gsOut.texCoord = gsIn[index].texCoord;
}

#endif // _GEOMETRY_GLSL_
