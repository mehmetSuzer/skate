
#ifndef _DEPTH_GLSL_
#define _DEPTH_GLSL_

const float near = 0.1f; 
const float far  = 100.0f; 
  
vec4 LinearizeDepth(float depth) 
{
    float z = depth * 2.0f - 1.0f; // back to NDC 
    float linearDepth = (2.0f * near * far) / (far + near - z * (far - near));	
    float normalizedDepth = linearDepth / far;
    return vec4(vec3(normalizedDepth), 1.0f);
}

#endif // _DEPTH_GLSL_
