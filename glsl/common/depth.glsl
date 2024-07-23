
#ifndef __DEPTH_GLSL__
#define __DEPTH_GLSL__

float near = 0.1f; 
float far  = 100.0f; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0f - 1.0f; // back to NDC 
    return (2.0f * near * far) / (far + near - z * (far - near));	
}

#endif // __DEPTH_GLSL__
