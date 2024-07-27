
#include "directional_light.h"

namespace skate 
{
    DirectionalLight::DirectionalLight(const glm::vec3& direction_, float intensity_, float red, float green, float blue) 
        : LightCaster(red, green, blue) 
    {
        SetDirection(direction_);
        SetIntensity(intensity_);
    }

    DirectionalLight::DirectionalLight(const glm::vec3& direction_, float intensity_, const glm::vec3& color_)
        : DirectionalLight(direction_, intensity_, color_.r, color_.g, color_.b) {}
}
