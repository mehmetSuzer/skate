
#include "point_light.h"

namespace skate 
{
    void PointLight::AssertAttenuationCoefficients(float linear_, float quadratic_) const 
    {
        if (linear_ < 0.0f || quadratic_ < 0.0f) 
            throw Exception("Attenuation Coefficients Cannot Be Negative. Given: " + std::to_string(linear_) + " " + std::to_string(quadratic_));
    }

    PointLight::PointLight(const glm::vec3& position_, float linear_, float quadratic_, float red, float green, float blue)
        : LightCaster(red, green, blue), position(position_) 
    {
        SetAttenuationCoefficients(linear_, quadratic_);
    }

    PointLight::PointLight(const glm::vec3& position_, float linear_, float quadratic_, const glm::vec3& color_)
        : PointLight(position_, linear_, quadratic_, color_.r, color_.g, color_.b) {}

    PointLight::PointLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, float red, float green, float blue) 
        : LightCaster(red, green, blue), position(position_) 
    {
        const float d1_minus_d2 = dist1 - dist2;
        const float a1_d1 = atten1 * dist1;
        const float a2_d2 = atten2 * dist2;
        const float d1_d2 = dist1 * dist2;

        const float quadratic_ = 1.0f / (a1_d1 * d1_minus_d2) - 1.0f / (a2_d2 * d1_minus_d2) + 1.0f / d1_d2;
        const float linear_ = (1.0f - atten1 - a1_d1 * dist1 * quadratic_) / a1_d1;
        SetAttenuationCoefficients(linear_, quadratic_);
    }
        
    PointLight::PointLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, const glm::vec3& color_)
        : PointLight(position_, dist1, atten1, dist2, atten2, color_.r, color_.g, color_.b) {}
}
