
#ifndef _LIGHT_GLSL_
#define _LIGHT_GLSL_

// WARNING: If you change this variable, recalculate the offset of lightCasters in global.glsl
// and update the allocated memory in the uniform buffer object in the code.
#define MAX_LIGHT_CASTER_NUMBER 8

#define DIRECTIONAL_LIGHT   0
#define POINT_LIGHT         1
#define SPOT_LIGHT          2

// WARNING: If you change the order of the variables, recalculate the offset of lightCasters in global.glsl
// and update the allocated memory in the uniform buffer object in the code.
struct Light 
{                           // usage                    // base alignment   // aligned offset
    int type;               // all                      // 4                // 0
    float intensity;        // directional              // 4                // 4
    float linear;           // point and spot           // 4                // 8
    float quadratic;        // point and spot           // 4                // 12
    float cosInnerCutOff;   // spot                     // 4                // 16
    float cosOuterCutOff;   // spot                     // 4                // 20
    vec3 color;             // all                      // 16               // 32
    vec3 position;          // point and spot           // 16               // 48
    vec3 direction;         // directional and spot     // 16               // 64
};                                                                          // total size = 80 bytes

#endif // _LIGHT_GLSL_
