
#ifndef __POINT_LIGHT_H__
#define __POINT_LIGHT_H__

#include "light_caster.h"

class PointLight : public LightCaster {
private:
    void AssertAttenuationCoefficients(float linear_, float quadratic_) const;

protected:
    glm::vec3 position;
    float linear;
    float quadratic;

public:
    PointLight(const glm::vec3& position_, float linear_, float quadratic_, float red, float green, float blue);
    PointLight(const glm::vec3& position_, float linear_, float quadratic_, const glm::vec3& color_);

    PointLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, float red, float green, float blue);
    PointLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, const glm::vec3& color_);

    const glm::vec3& GetPosition(void) const {
        return position;
    }

    void SetPosition(const glm::vec3& position_) {
        position = position_;
    }

    void SetAttenuationCoefficients(float linear_, float quadratic_) {
    #ifdef __COMPILE_ERROR_HANDLERS__
        AssertAttenuationCoefficients(linear_, quadratic_);
    #endif
        linear = linear_;
        quadratic = quadratic_;
    }

    LightCasterInfo GetInfo(void) const override {
        return LightCasterInfo {
            .type = POINT_LIGHT,
            .color = GetColor(),
            .position = GetPosition(),
            .linear = linear,
            .quadratic = quadratic,
        };
    }
};

#endif // __POINT_LIGHT_H__
