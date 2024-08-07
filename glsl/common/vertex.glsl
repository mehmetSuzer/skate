
#ifndef _VERTEX_GLSL_
#define _VERTEX_GLSL_

out VS_OUT
{
    vec3 position;
    vec3 normal;
    vec4 color;
    vec2 texCoord;
} vsOut;

uniform mat4 model;
uniform mat4 projectionView;
uniform mat3 normalMatrix;

#endif // _VERTEX_GLSL_
