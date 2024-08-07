
#ifndef __DEPTH_GLSL__
#define __DEPTH_GLSL__

const float near = 0.1f; 
const float far  = 100.0f; 
  
vec4 LinearizeDepth(float depth) 
{
    float z = depth * 2.0f - 1.0f; // back to NDC 
    float linearDepth = (2.0f * near * far) / (far + near - z * (far - near));	
    float normalizedDepth = linearDepth / far;
    return vec4(vec3(normalizedDepth), 1.0f);
}

#endif // __DEPTH_GLSL__
