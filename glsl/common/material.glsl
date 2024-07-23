
#ifndef __MATERIAL_GLSL__
#define __MATERIAL_GLSL__

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

uniform Material material;

#endif // __MATERIAL_GLSL__
