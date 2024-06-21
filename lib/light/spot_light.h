
#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include "point_light.h"
#include <gtc/epsilon.hpp>

class SpotLight : public PointLight {
private:
    glm::vec3 direction;
    float cosHalfFOVradian;

    void AssertFOVradian(float FOVradian) const;
    void AssertDirection(const glm::vec3& direction) const;

public:
    SpotLight(const glm::vec3& position_, float red, float green, float blue, float a_, float b_, const glm::vec3& direction_, float FOVradian);
    SpotLight(const glm::vec3& position_, const glm::vec3& color_, float a_, float b_, const glm::vec3& direction_, float FOVradian);

    const glm::vec3& GetDirection(void) const {
        return direction;
    }

    void SetDirection(const glm::vec3& direction_) {
        AssertDirection(direction_);
        direction = direction_;
    }

    void SetFOVradian(float FOVradian) {
        AssertFOVradian(FOVradian);
        cosHalfFOVradian = cosf(FOVradian / 2.0f);
    }

    LightInfo Shine(const glm::vec3& point) const override;
};

#endif // __SPOT_LIGHT_H__
