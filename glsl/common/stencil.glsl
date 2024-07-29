
#ifndef __STENCIL_GLSL__
#define __STENCIL_GLSL__

#define BORDER_THICKNESS    0.02f
#define BORDER_COLOR        vec4(0.0f, 1.0f, 0.0f, 1.0f)

uniform bool drawBorder;

vec3 PositionWithBorder(vec3 position, vec3 normal)
{
    if (drawBorder)
        return position + BORDER_THICKNESS * normal;
    else
        return position;
}

#endif // __STENCIL_GLSL__
