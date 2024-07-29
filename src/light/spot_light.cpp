
#include "spot_light.h"

namespace skate 
{
    SpotLight::SpotLight(const glm::vec3& position, const glm::quat& quaternion, float linear_, float quadratic_,
        float innerCutOffRadian, float outerCutOffRadian, const glm::vec3& color_)
        : PointLight(position, linear_, quadratic_, color_) 
    {
        transform.SetRotation(quaternion);
        SetCutOffRadians(innerCutOffRadian, outerCutOffRadian);
    }

    SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, float linear_, float quadratic_,
        float innerCutOffRadian, float outerCutOffRadian, const glm::vec3& color_)
        : PointLight(position, linear_, quadratic_, color_)
    {
        transform.SetForward(direction);
        SetCutOffRadians(innerCutOffRadian, outerCutOffRadian);
    }

    SpotLight::SpotLight(const glm::vec3& position, const glm::quat& quaternion, float dist1, float atten1, float dist2, float atten2,
        float innerCutOffRadian, float outerCutOffRadian, const glm::vec3& color_) 
        : PointLight(position, dist1, atten1, dist2, atten2, color_) 
    {
        transform.SetRotation(quaternion);
        SetCutOffRadians(innerCutOffRadian, outerCutOffRadian);
    }

    SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, float dist1, float atten1, float dist2, float atten2, 
        float innerCutOffRadian, float outerCutOffRadian, const glm::vec3& color_)
        : PointLight(position, dist1, atten1, dist2, atten2, color_)
    {
        transform.SetForward(direction);
        SetCutOffRadians(innerCutOffRadian, outerCutOffRadian);
    }    
}
