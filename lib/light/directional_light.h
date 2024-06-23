
#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__

#include "light.h"
#include <gtc/epsilon.hpp>

class DirectionalLight : public Light {
private:
    glm::vec3 direction;
    float intensity;

    void AssertDirection(const glm::vec3& direction) const;
    void AssertIntensity(float intensity) const;

public:
    DirectionalLight(const glm::vec3& direction_, float red, float green, float blue, float alpha, float intensity_);
    DirectionalLight(const glm::vec3& direction_, const glm::vec4& color_, float intensity_);

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
    
    float GetIntensity(float distance) const override {
        return intensity;
    }

    void SetIntensity(float intensity_) {
    #ifdef __COMPILE_ERROR_HANDLERS__
        AssertIntensity(intensity_);
    #endif
        intensity = intensity_;
    }
    
    LightInfo Shine(const glm::vec3& point) const override;
};

#endif // __DIRECTIONAL_LIGHT_H__
