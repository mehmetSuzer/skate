
#include "directional_light.h"

namespace skate 
{
    DirectionalLight::DirectionalLight(const glm::quat& quaternion, float intensity_, const glm::vec3& color_)
        : LightCaster(color_) 
    {
        transform.SetRotation(quaternion);
        SetIntensity(intensity_);
    }

    DirectionalLight::DirectionalLight(const glm::vec3& direction, float intensity_, const glm::vec3& color_)
        : LightCaster(color_)
    {
        transform.SetForward(direction);
        SetIntensity(intensity_);
    }
}
