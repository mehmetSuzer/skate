
#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__

#include "light_caster.h"
#include "gtc/epsilon.hpp"

namespace skate 
{
    // A light source that is modeled to be infinitely far away and sends parallel light rays
    class DirectionalLight : public LightCaster 
    {
    private:
        glm::vec3 direction;
        float intensity;

    public:
        DirectionalLight(const glm::vec3& direction_, float intensity_, float red, float green, float blue);
        DirectionalLight(const glm::vec3& direction_, float intensity_ = 0.8f, const glm::vec3& color_ = glm::vec3(1.0f));

        inline void SetDirection(const glm::vec3& direction_) 
        {
            assert(glm::epsilonEqual(glm::length(direction_), 1.0f, 1E-6f));
            direction = direction_;
        }

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
                .direction = direction,
                .intensity = intensity,
            };
        }
    };
}

#endif // __DIRECTIONAL_LIGHT_H__
