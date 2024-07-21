
#include "directional_light.h"

namespace skate 
{
    void DirectionalLight::AssertDirection(const glm::vec3& direction) const 
    {
        const float length = glm::length(direction);
        if (glm::epsilonNotEqual(length, 1.0f, 1E-6f)) 
            throw Exception("Direction Vector Is Not a Unit Vector!");
    }
        
    void DirectionalLight::AssertIntensity(float intensity) const 
    {
        if (intensity <= 0.0f || intensity > 1.0f) 
            throw Exception("Intensity Must Be In (0,1]!");
    }

    DirectionalLight::DirectionalLight(const glm::vec3& direction_, float intensity_, float red, float green, float blue) 
        : LightCaster(red, green, blue) 
    {
        SetDirection(direction_);
        SetIntensity(intensity_);
    }

    DirectionalLight::DirectionalLight(const glm::vec3& direction_, float intensity_, const glm::vec3& color_)
        : DirectionalLight(direction_, intensity_, color_.r, color_.g, color_.b) {}
}
