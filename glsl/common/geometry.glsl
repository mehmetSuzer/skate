
#ifndef _GEOMETRY_GLSL_
#define _GEOMETRY_GLSL_

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

#endif // _GEOMETRY_GLSL_
