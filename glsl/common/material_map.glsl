
#ifndef _MATERIAL_MAP_GLSL_
#define _MATERIAL_MAP_GLSL_

struct MaterialMap 
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

uniform MaterialMap materialMap;

#endif // _MATERIAL_MAP_GLSL_
