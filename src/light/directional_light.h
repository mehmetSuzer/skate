
#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__

#include "light_caster.h"

namespace skate 
{
    // A light source that is modeled to be infinitely far away and sends parallel light rays
    class DirectionalLight : public LightCaster 
    {
    private:
        float intensity;

    public:
        DirectionalLight(const glm::quat& quaternion, float intensity_ = 0.8f, const glm::vec3& color_ = glm::vec3(1.0f));
        DirectionalLight(const glm::vec3& direction, float intensity_ = 0.8f, const glm::vec3& color_ = glm::vec3(1.0f));

        inline void SetIntensity(float intensity_) 
        {
            assert(0.0f < intensity_ && intensity_ <= 1.0f);
            intensity = intensity_;
        }

        inline Light GetLight(void) const noexcept override 
        {
            return Light 
            {
                .type = DIRECTIONAL_LIGHT,
                .color = GetColor(),
                .direction = transform.GetForward(),
                .intensity = intensity,
            };
        }
    };
}

#endif // __DIRECTIONAL_LIGHT_H__
