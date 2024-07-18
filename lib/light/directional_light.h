
#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__

#include "light_caster.h"
#include "gtc/epsilon.hpp"

class DirectionalLight : public LightCaster {
private:
    glm::vec3 direction;
    float intensity;

    void AssertDirection(const glm::vec3& direction) const;
    void AssertIntensity(float intensity) const;

public:
    DirectionalLight(const glm::vec3& direction_, float intensity_, float red, float green, float blue);
    DirectionalLight(const glm::vec3& direction_, float intensity_, const glm::vec3& color_);

    inline void SetDirection(const glm::vec3& direction_) {
        AssertDirection(direction_);
        direction = direction_;
    }

    inline void SetIntensity(float intensity_) {
        AssertIntensity(intensity_);
        intensity = intensity_;
    }

    inline Light GetLight(void) const override {
        return Light {
            .type = DIRECTIONAL_LIGHT,
            .color = GetColor(),
            .direction = direction,
            .intensity = intensity,
        };
    }
};

#endif // __DIRECTIONAL_LIGHT_H__
