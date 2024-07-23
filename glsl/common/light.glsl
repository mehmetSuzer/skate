
#ifndef __LIGHT_GLSL__
#define __LIGHT_GLSL__

#define MAX_LIGHT_CASTER_NUMBER 8

#define DIRECTIONAL_LIGHT   0
#define POINT_LIGHT         1
#define SPOT_LIGHT          2

struct Light 
{
    int type;
    vec3 color;             // all
    vec3 position;          // point and spot
    vec3 direction;         // directional and spot
    float intensity;        // directional
    float linear;           // point and spot
    float quadratic;        // point and spot
    float cosInnerCutOff;   // spot
    float cosOuterCutOff;   // spot
};

uniform int lightCasterNumber;
uniform Light lights[MAX_LIGHT_CASTER_NUMBER];

#endif // __LIGHT_GLSL__
