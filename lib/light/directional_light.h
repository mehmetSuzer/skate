
#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__

#include "light_caster.h"
#include <gtc/epsilon.hpp>

class DirectionalLight : public LightCaster {
private:
    glm::vec3 direction;
    float intensity;

    void AssertDirection(const glm::vec3& direction) const;
    void AssertIntensity(float intensity) const;

public:
    DirectionalLight(const glm::vec3& direction_, float intensity_, float red, float green, float blue);
    DirectionalLight(const glm::vec3& direction_, float intensity_, const glm::vec3& color_);

    const glm::vec3& GetDirection(void) const {
        return direction;
    }
;
    void SetDirection(const glm::vec3& direction_) {
    #ifdef __COMPILE_ERROR_HANDLERS__
        AssertDirection(direction_);
    #endif
        direction = direction_;
    }

    float GetIntensity(void) const {
        return intensity;
    }

    void SetIntensity(float intensity_) {
    #ifdef __COMPILE_ERROR_HANDLERS__
        AssertIntensity(intensity_);
    #endif
        intensity = intensity_;
    }

    Light GetLight(void) const override {
        return Light {
            .type = DIRECTIONAL_LIGHT,
            .color = GetColor(),
            .direction = GetDirection(),
            .intensity = GetIntensity(),
        };
    }
};

#endif // __DIRECTIONAL_LIGHT_H__
