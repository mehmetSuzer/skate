
#ifndef __MATERIAL_MAP_GLSL__
#define __MATERIAL_MAP_GLSL__

struct MaterialMap 
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

uniform MaterialMap materialMap;

#endif // __MATERIAL_MAP_GLSL__
