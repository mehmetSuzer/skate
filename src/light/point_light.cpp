
#include "point_light.h"

namespace skate 
{
    PointLight::PointLight(const glm::vec3& position,float linear_, float quadratic_, const glm::vec3& color_)
        : LightCaster(color_)
    {
        transform.SetPosition(position);
        SetAttenuationCoefficients(linear_, quadratic_);
    }

    PointLight::PointLight(const glm::vec3& position, float dist1, float atten1, float dist2, float atten2, const glm::vec3& color_) 
        : LightCaster(color_)
    {
        const float d1_minus_d2 = dist1 - dist2;
        const float a1_d1 = atten1 * dist1;
        const float a2_d2 = atten2 * dist2;
        const float d1_d2 = dist1 * dist2;

        const float quadratic_ = 1.0f / (a1_d1 * d1_minus_d2) - 1.0f / (a2_d2 * d1_minus_d2) + 1.0f / d1_d2;
        const float linear_ = (1.0f - atten1 - a1_d1 * dist1 * quadratic_) / a1_d1;
        transform.SetPosition(position);
        SetAttenuationCoefficients(linear_, quadratic_);
    }
}
