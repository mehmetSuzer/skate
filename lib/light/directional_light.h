
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
    DirectionalLight(const glm::vec3& direction_, float red, float green, float blue, float intensity_) 
        : Light(red, green, blue) {
        SetDirection(direction_);
        SetIntensity(intensity_);
    }

    DirectionalLight(const glm::vec3& direction_, const glm::vec3& color_, float intensity_)
        : DirectionalLight(direction_, color_.r, color_.g, color_.b, intensity_) {}

    const glm::vec3& GetDirection(void) const {
        return direction;
    }

    void SetDirection(const glm::vec3& direction_) {
        AssertDirection(direction_);
        direction = direction_;
    }
    
    float GetIntensity(float distance) const override {
        return intensity;
    }

    float SetIntensity(float intensity_) {
        AssertIntensity(intensity_);
        intensity = intensity_;
    }
    
    LightInfo Shine(const glm::vec3& point) const override;
};

#endif // __DIRECTIONAL_LIGHT_H__
