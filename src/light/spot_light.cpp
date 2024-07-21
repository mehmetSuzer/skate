
#include "spot_light.h"

namespace skate 
{
    void SpotLight::AssertCutOffRadian(float cutOffRadian) const 
    {
        if (cutOffRadian <= 0.0f || cutOffRadian >= M_PIf) 
            throw Exception("Cut-Off Radian Must Be In (0, pi)! Given: " + std::to_string(cutOffRadian));
    }

    void SpotLight::AssertInnerLessThanOuter(float innerCutOffRadian, float outerCutOffRadian) const 
    {
        if (innerCutOffRadian >= outerCutOffRadian) 
            throw Exception("Inner Cut-Off Radian Must Be Less Than Outer Cut-Off Radian! Given Values --> Inner: " 
                + std::to_string(innerCutOffRadian) + ", Outer: " + std::to_string(outerCutOffRadian));
    }

    void SpotLight::AssertDirection(const glm::vec3& direction) const 
    {
        const float length = glm::length(direction);
        if (glm::epsilonNotEqual(length, 1.0f, 1E-6f)) 
            throw Exception("Direction Vector Is Not a Unit Vector!");
    }

    SpotLight::SpotLight(const glm::vec3& position_, float linear_, float quadratic_, const glm::vec3& direction_, 
        float innerCutOffRadian, float outerCutOffRadian, float red, float green, float blue)
        : PointLight(position_, linear_, quadratic_, red, green, blue) 
    {
        SetDirection(direction_);
        SetCutOffRadians(innerCutOffRadian, outerCutOffRadian);
    }

    SpotLight::SpotLight(const glm::vec3& position_, float linear_, float quadratic_, const glm::vec3& direction_, 
        float innerCutOffRadian, float outerCutOffRadian, const glm::vec3& color_)
        : SpotLight(position_, linear_, quadratic_, direction_, innerCutOffRadian, outerCutOffRadian, color_.r, color_.g, color_.b) {}

    SpotLight::SpotLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, const glm::vec3& direction_, 
        float innerCutOffRadian, float outerCutOffRadian, float red, float green, float blue) 
        : PointLight(position_, dist1, atten1, dist2, atten2, red, green, blue) 
    {
        SetDirection(direction_);
        SetCutOffRadians(innerCutOffRadian, outerCutOffRadian);
    }
        
    SpotLight::SpotLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, const glm::vec3& direction_, 
        float innerCutOffRadian, float outerCutOffRadian, const glm::vec3& color_)
        : SpotLight(position_, dist1, atten1, dist2, atten2, direction_, innerCutOffRadian, outerCutOffRadian, color_.r, color_.g, color_.b) {}
}
