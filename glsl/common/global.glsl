
#ifndef _GLOBAL_GLSL_
#define _GLOBAL_GLSL_

#include <common/light.glsl>

layout (std140) uniform Global
{                                           // base alignment   // aligned offset
    int lightCasterNumber;                  // 4                // 0
    vec3 cameraPosition;                    // 16               // 16
    mat4 projectionView;                    // 16               // 32,48,64,80 for column 0,1,2,3
    Light lights[MAX_LIGHT_CASTER_NUMBER];  // 16               // 96
};                                                              // total size 96 + 80*MAX_LIGHT_CASTER_NUMBER bytes

#endif // _GLOBAL_GLSL_
