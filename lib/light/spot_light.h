
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
    SpotLight(const glm::vec3& position_, float linear_, float quadratic_, 
        const glm::vec3& direction_, float FOVradian, float red, float green, float blue);
    SpotLight(const glm::vec3& position_, float linear_, float quadratic_, 
        const glm::vec3& direction_, float FOVradian, const glm::vec3& color_);

    SpotLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, 
        const glm::vec3& direction_, float FOVradian, float red, float green, float blue);
    SpotLight(const glm::vec3& position_, float dist1, float atten1, float dist2, float atten2, 
        const glm::vec3& direction_, float FOVradian, const glm::vec3& color_);

    const glm::vec3& GetDirection(void) const {
        return direction;
    }

    void SetDirection(const glm::vec3& direction_) {
    #ifdef __COMPILE_ERROR_HANDLERS__
        AssertDirection(direction_);
    #endif
        direction = direction_;
    }

    void SetFOVradian(float FOVradian) {
    #ifdef __COMPILE_ERROR_HANDLERS__
        AssertFOVradian(FOVradian);
    #endif
        cosHalfFOVradian = cosf(FOVradian / 2.0f);
    }
};

#endif // __SPOT_LIGHT_H__
