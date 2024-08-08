
#ifndef _FRAGMENT_GLSL_
#define _FRAGMENT_GLSL_

#include <common/global.glsl>

in VS_OUT
{
    vec3 position;
    vec3 normal;
    vec4 color;
    vec2 texCoord;
} fsIn;

out vec4 FragColor;

#endif // _FRAGMENT_GLSL_
