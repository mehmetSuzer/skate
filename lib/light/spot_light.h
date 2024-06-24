
#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include "point_light.h"
#include <gtc/epsilon.hpp>

class SpotLight : public PointLight {
private:
    glm::vec3 direction;
    float cosInnerCutOffRadian;
    float cosOuterCutOffRadian;

    void AssertCutOffRadian(float cutOffRadian) const;
    void AssertInnerLessThanOuter(float innerCutOffRadian, float outerCutOffRadian) const;
    void AssertDirection(const glm::vec3& direction) const;

public:
    SpotLight(const glm::vec3& position_, float linear_, float quadratic_, const glm::vec3& direction_, 
        float innerCutOffRadian, float outerCutOffRadian, float red, float green, float blue);
    SpotLight(const glm::vec3& position_, float linear_, float quadratic_, const glm::vec3& direction_, 
        float innerCutOffRadian, float outerCutOffRadian, const glm::vec3& color_);

    SpotLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, const glm::vec3& direction_, 
        float innerCutOffRadian, float outerCutOffRadian, float red, float green, float blue);
    SpotLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, const glm::vec3& direction_, 
        float innerCutOffRadian, float outerCutOffRadian, const glm::vec3& color_);

    const glm::vec3& GetDirection(void) const {
        return direction;
    }

    void SetDirection(const glm::vec3& direction_) {
    #ifdef __COMPILE_ERROR_HANDLERS__
        AssertDirection(direction_);
    #endif
        direction = direction_;
    }

    void SetCutOffRadians(float innerCutOffRadian, float outerCutOffRadian) {
    #ifdef __COMPILE_ERROR_HANDLERS__
        AssertCutOffRadian(innerCutOffRadian);
        AssertCutOffRadian(outerCutOffRadian);
        AssertInnerLessThanOuter(innerCutOffRadian, outerCutOffRadian);
    #endif
        cosInnerCutOffRadian = glm::cos(innerCutOffRadian);
        cosOuterCutOffRadian = glm::cos(outerCutOffRadian);
    }

    Light GetLight(void) const override {
        return Light {
            .type = SPOT_LIGHT,
            .color = GetColor(),
            .position = GetPosition(),
            .direction = GetDirection(),
            .linear = linear,
            .quadratic = quadratic,
            .cosInnerCutOffRadian = cosInnerCutOffRadian,
            .cosOuterCutOffRadian = cosOuterCutOffRadian,
        };
    }
};

#endif // __SPOT_LIGHT_H__
