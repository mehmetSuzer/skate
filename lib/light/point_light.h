
#ifndef __POINT_LIGHT_H__
#define __POINT_LIGHT_H__

#include "light.h"

class PointLight : public Light {
private:
    void AssertIntensityCoefficients(float a_, float b_) const;

protected:
    glm::vec3 position;
    float a;
    float b;

public:
    PointLight(const glm::vec3& position_, float red, float green, float blue, float a_, float b_);
    PointLight(const glm::vec3& position_, const glm::vec3& color_, float a_, float b_);

    const glm::vec3& GetPosition(void) const {
        return position;
    }

    void SetPosition(const glm::vec3& position_) {
        position = position_;
    }

    float GetIntensity(float distance) const override {
        return 1.0f / ((a * distance + b) * distance + 1.0f);
    }

    void SetIntensityCoefficients(float a_, float b_) {
        AssertIntensityCoefficients(a_, b_);
        a = a_;
        b = b_;
    }

    void SetIntensityCoefficients(const glm::vec2& coefs) {
        SetIntensityCoefficients(coefs.x, coefs.y);
    }

    LightInfo Shine(const glm::vec3& point) const override;
};

#endif // __POINT_LIGHT_H__
