
#include "spot_light.h"

namespace skate 
{
    SpotLight::SpotLight(const glm::vec3& position_, const glm::vec3& direction_, float linear_, float quadratic_,
        float innerCutOffRadian, float outerCutOffRadian, float red, float green, float blue)
        : PointLight(position_, linear_, quadratic_, red, green, blue) 
    {
        SetDirection(direction_);
        SetCutOffRadians(innerCutOffRadian, outerCutOffRadian);
    }

    SpotLight::SpotLight(const glm::vec3& position_, const glm::vec3& direction_, float linear_, float quadratic_,
        float innerCutOffRadian, float outerCutOffRadian, const glm::vec3& color_)
        : SpotLight(position_, direction_, linear_, quadratic_, innerCutOffRadian, outerCutOffRadian, color_.r, color_.g, color_.b) {}

    SpotLight::SpotLight(const glm::vec3& position_, const glm::vec3& direction_, float dist1, float atten1, float dist2, float atten2,
        float innerCutOffRadian, float outerCutOffRadian, float red, float green, float blue) 
        : PointLight(position_, dist1, atten1, dist2, atten2, red, green, blue) 
    {
        SetDirection(direction_);
        SetCutOffRadians(innerCutOffRadian, outerCutOffRadian);
    }
        
    SpotLight::SpotLight(const glm::vec3& position_, const glm::vec3& direction_, float dist1, float atten1, float dist2, float atten2,
        float innerCutOffRadian, float outerCutOffRadian, const glm::vec3& color_)
        : SpotLight(position_, direction_, dist1, atten1, dist2, atten2, innerCutOffRadian, outerCutOffRadian, color_.r, color_.g, color_.b) {}
}
