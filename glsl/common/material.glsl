
#ifndef _MATERIAL_GLSL_
#define _MATERIAL_GLSL_

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

uniform Material material;

#endif // _MATERIAL_GLSL_
